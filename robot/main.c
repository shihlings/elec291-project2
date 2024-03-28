#include "lpc824.h"
#include "serial.h"
#include "serial1.h"

// LPC824 pinout:
//                             --------
//     PIO0_23/ADC_3/ACMP_I4 -|1     20|- PIO0_14/ADC_2/ACMP_I3
//             PIO0_17/ADC_9 -|2     19|- PIO0_0/ACMP_I1/TDO
//            PIO0_13/ADC_10 -|3     18|- VREFP
//                   PIO0_12 -|4     17|- VREFN
//              RESET/PIO0_5 -|5     16|- VSS
// PIO0_4/ADC_11/WAKEUP/TRST -|6     15|- VDD
//          SWCLK/PIO0_3/TCK -|7     14|- PIO0_8/XTALIN
//          SWDIO/PIO0_2/TMS -|8     13|- PIO0_9/XTALOUT
//          PIO0_11/I2C0_SDA -|9     12|- PIO0_1/ACMP_I2/CLKIN/TDI
//          PIO0_10/I2C0_SCL -|10    11|- PIO0_15
//                             --------
// WARNING pins 9 and 10 are OPEN DRAIN.  They need external pull-up resistors to VDD if used
// as outputs. 1kohm seems to work.
//
// Reserved pins:
// Pin 4:  BOOT button
// Pin 5:  Reset
// Pin 6:  TXD
// Pin 19: RXD

#define F_CPU 60000000L
#define SYSTEM_CLK 30000000L
#define DEFAULT_F 100000L // For a 10us servo resolution
#define PI 3.14159
#define MOTOR_CONTROL_LEFT GPIO_B1
#define MOTOR_DIRECTION_LEFT GPIO_B15
#define MOTOR_CONTROL_RIGHT GPIO_B9
#define MOTOR_DIRECTION_RIGHT GPIO_B10
#define JOYSTICK_DEADZONE 1000

enum Direction {
  FORWARD = 0,
  BACKWARD = 1
};

volatile int ISR_pwm1=150, ISR_pwm2=150, ISR_cnt=0;

char parse_buffer (char *buff, int *num1, int *num2) {
  int num1s[5], num2s[5], num3s[5];
  int num3;
  for (int i = 0; i<5; i++){
    num1s[i]=buff[i] - 48;
  }
  int j=0;
  for (int i = 6; i < 11; i++){
    num2s[j]=buff[i] - 48;
    j++;	
  }
      
  int k=0;

  for (int i = 12; i<17; i++){
    num3s[k] = buff[i] - 48;
    k++;
  }
  *num1 = num1s[0]*10000 + num1s[1]*1000 + num1s[2]*100 + num1s[3]*10 + num1s[4];
  *num2 = num2s[0]*10000 + num2s[1]*1000 + num2s[2]*100 + num2s[3]*10 + num2s[4];
  num3 = num3s[0]*10000 + num3s[1]*1000 + num3s[2]*100 + num3s[3]*10 + num3s[4];
  if ((*num1 + *num2) != num3) {
    return 1; // Transmission error
  }
  return 0;
}

int pow(int base, int exponent) {
  if (exponent > 0) {
    return base*pow(base, exponent-1);
  } else {
    return 1;
  }
}

void InitTimer(void)
{
  SCTIMER_CTRL |= BIT2; // halt SCTimer

  // Assign a pin to the timer. So we can check the frequency.  (It should be 100kHz)
  // Assign GPIO_14 to SCT_OUT0_O
  SWM_PINASSIGN7 &= 0x00ffffff;
  SWM_PINASSIGN7 |= (14 << 24); 
	
  SYSCON_SYSAHBCLKCTRL |= BIT8; // Turn on SCTimer 
  SYSCON_PRESETCTRL |=  BIT8; // Clear the reset SCT control
	
  SCTIMER_CONFIG |= BIT0; // Unified 32 bit counter
  SCTIMER_MATCH0 = SYSTEM_CLK/DEFAULT_F; // Set delay period 
  SCTIMER_MATCHREL0 = SYSTEM_CLK/DEFAULT_F;
  SCTIMER_EV0_STATE = BIT0;  // Event 0 pushes us into state 0
  // Event 0 configuration:
  // Event occurs on match of MATCH0, new state is 1	
  SCTIMER_EV0_CTRL =  BIT12 + BIT14 + BIT15;
  // State 1 configuration
  SCTIMER_EV1_STATE = BIT1;  // Event 1 pushes us into state 1
  // Event 1 configuration
  // Event occurs on MATCH0, new state is 0
  SCTIMER_EV1_CTRL =  BIT12 + BIT14;
  // OUT0 is set by event 0
  SCTIMER_OUT0_SET = BIT0;
  // OUT1 is cleared by event 1
  SCTIMER_OUT0_CLR = BIT1;
  // Processing events 0 and 1
  SCTIMER_LIMIT_L = BIT0 + BIT1;
  // Remove halt on SCTimer
  SCTIMER_CTRL &= ~BIT2;		
		
  SCTIMER_EVEN = 0x01; //Interrupt on event 0
  NVIC_ISER0|=BIT9; // Enable SCT interrupts in NVIC
}

void Reload_SCTIMER (unsigned long Dly)
{
  SCTIMER_CTRL |= BIT2; // halt SCTimer
  SCTIMER_MATCH0 = Dly; // Set delay period 
  SCTIMER_MATCHREL0 = Dly;
  SCTIMER_COUNT = 0;
  SCTIMER_CTRL &= ~BIT2;	// Remove halt on SCTimer	
}

void STC_IRQ_Handler(void)
{
  SCTIMER_EVFLAG = 0x01; // Clear interrupt flag
  ISR_cnt++;

  int ISR_pwm1_abs = ISR_pwm1;
  enum Direction direction_left = FORWARD;
  int ISR_pwm2_abs = ISR_pwm2;
  enum Direction direction_right = FORWARD;
	
  if (ISR_pwm1_abs < 0) {
    ISR_pwm1_abs *= -1;
    direction_left = BACKWARD;
  }
  if (ISR_pwm2_abs < 0) {
    ISR_pwm2_abs *= -1;
    direction_right = BACKWARD;
  }
  //MOTOR_CONTROL_LEFT = !direction_left;
  MOTOR_DIRECTION_LEFT = direction_left;
  //MOTOR_CONTROL_RIGHT = !direction_right;
  MOTOR_DIRECTION_RIGHT = direction_right;
	
  if(ISR_cnt==ISR_pwm1_abs)
    {
      MOTOR_CONTROL_LEFT=direction_left;
    }
  if(ISR_cnt==ISR_pwm2_abs)
    {
      MOTOR_CONTROL_RIGHT=direction_right;
    }
  if(ISR_cnt>=2000)
    {
      ISR_cnt=0; // 2000 * 10us=20ms
      MOTOR_CONTROL_LEFT=!direction_left;
      MOTOR_CONTROL_RIGHT=!direction_right;
    }
}

void Delay_us(unsigned char us)
{
  // For SysTick info check the LPC824 manual page 317 in chapter 20.
  SYST_RVR = (SYSTEM_CLK/(1000000L/us)) - 1;  // set reload register, counter rolls over from zero, hence -1
  SYST_CVR = 0; // load the SysTick counter
  SYST_CSR = 0x05; // Bit 0: ENABLE, BIT 1: TICKINT, BIT 2:CLKSOURCE
  while((SYST_CSR & BIT16)==0); // Bit 16 is the COUNTFLAG.  True when counter rolls over from zero.
  SYST_CSR = 0x00; // Disable Systick counter
}

void waitms (unsigned int ms)
{
  unsigned int j;
  unsigned char k;
  for(j=0; j<ms; j++)
    for (k=0; k<4; k++) Delay_us(250);
}

void wait_and_RX (unsigned int ms, char* buff)
{
  unsigned int j;
  unsigned char k;
  for(j=0; j<ms; j++) {
    if (rx_count1()>0) {
      egets1(buff, 80);
    }
    for (k=0; k<4; k++) Delay_us(250);
  }
}

#define PIN_PERIOD (GPIO_B13) // Read period from PIO0_13 (pin 3)

// GetPeriod() seems to work fine for frequencies between 400Hz and 400kHz.
long int GetPeriod (int n)
{
  int i;
  unsigned int saved_TCNT1a, saved_TCNT1b;
	SYST_RVR = 0xffffff;  // 24-bit counter set to check for signal present SYST_CVR = 0xffffff; // load the SysTick counter
  SYST_CSR = 0x05; // Bit 0: ENABLE, BIT 1: TICKINT, BIT 2:CLKSOURCE
  while (PIN_PERIOD!=0) // Wait for square wave to be 0
    {
      if(SYST_CSR & BIT16) return 0;
    }
  SYST_CSR = 0x00; // Disable Systick counter

  SYST_RVR = 0xffffff;  // 24-bit counter set to check for signal present
  SYST_CVR = 0xffffff; // load the SysTick counter
  SYST_CSR = 0x05; // Bit 0: ENABLE, BIT 1: TICKINT, BIT 2:CLKSOURCE
  while (PIN_PERIOD==0) // Wait for square wave to be 1
    {
      if(SYST_CSR & BIT16) return 0;
    }
  SYST_CSR = 0x00; // Disable Systick counter
	
  SYST_RVR = 0xffffff;  // 24-bit counter reset
  SYST_CVR = 0xffffff; // load the SysTick counter to initial value
  SYST_CSR = 0x05; // Bit 0: ENABLE, BIT 1: TICKINT, BIT 2:CLKSOURCE
  for(i=0; i<n; i++) // Measure the time of 'n' periods
    {
      while (PIN_PERIOD!=0) // Wait for square wave to be 0
	{
	  if(SYST_CSR & BIT16) return 0;
	}
      while (PIN_PERIOD==0) // Wait for square wave to be 1
	{
	  if(SYST_CSR & BIT16) return 0;
	}
    }
  SYST_CSR = 0x00; // Disable Systick counter

  return 0xffffff-SYST_CVR;
}



void ConfigPins(void)
{
  GPIO_DIR0 &= ~(BIT13);  // Configure PIO0_13 as input (pin 2).
  GPIO_DIR0 |= BIT14;    // Configure PIO0_14 as output (pin 20).
	
	
  SWM_PINENABLE0 |= BIT4; // Disable SWCLK on pin PIO0_3
  GPIO_DIR0 |= BIT3;    // Configure PIO0_3  as output (pin 7).
	
  SWM_PINENABLE0 |= BIT5; // Disable SWIO on pin PIO0_2
  GPIO_DIR0 |= BIT2;    // Configure PIO0_2  as output (pin 8).
	
  // Warning: PIO0_11 and PIO0_10 need external pull-up resistors to 3.3V (1k seems to work)
  // Check page 90 of the user manual, section: 8.4.3 Pin mode
  GPIO_DIR0 |= BIT11;   // Configure PIO0_11 as output (pin 9).
  GPIO_DIR0 |= BIT10;   // Configure PIO0_10 as output (pin 10).
  GPIO_DIR0 |= BIT15;   // Configure PIO0_15 as output (pin 11).
  GPIO_DIR0 |= BIT1;    // Configure PIO0_1  as output (pin 12).
  GPIO_DIR0 |= BIT9;    // Configure PIO0_9  as output (pin 13).
}

void SendATCommand (char * s)
{
  char buff[31];
  eputs("Command: \r\n");
  eputs(s);
  GPIO_B11=0; // 'SET' pin to 0 is 'AT' mode.
  waitms(20);
  eputs1(s);
  egets1(buff, 30);
  GPIO_B11=1; // 'SET' pin to 1 is normal operation mode.
  waitms(20);
  eputs("Response: \r\n:");
  eputs(buff);
  eputc('\n');
}

void joystick_to_pwm (int js_X, int js_Y) {
  ISR_pwm1 = 1;
  ISR_pwm2 = 1;
  if (js_X > 8192 + JOYSTICK_DEADZONE || js_X < 8192 - JOYSTICK_DEADZONE) {
    ISR_pwm1 += (8192-js_X)*1500/8192;
    ISR_pwm2 += (js_X-8192)*1500/8192;
  }
  if (js_Y > 8192 + JOYSTICK_DEADZONE || js_Y < 8192 - JOYSTICK_DEADZONE) {
    ISR_pwm1 += (8192-js_Y)*2000/8192;
    ISR_pwm2 += (8192-js_Y)*2000/8192;
  }
  if (ISR_pwm1 > 2000) {
    ISR_pwm1 = 2000;
  } else if (ISR_pwm1 < -2000) {
    ISR_pwm1 = -2000;
  }

  if (ISR_pwm2 > 2000) {
    ISR_pwm2 = 2000;
  } else if (ISR_pwm2 < -2000) {
    ISR_pwm2 = -2000;
  }
}

// In order to keep this as nimble as possible, avoid
// using floating point or printf on any of its forms!
void main(void)
{
  int j, v, cnt;
  long int count, f;
  long int l;
  unsigned char LED_toggle=0;
  char buff[80];
  char induc[80];
  int joystick_X, joystick_Y;
	
  ConfigPins();
  initUART1(9600);
  initUART(115200);
  InitTimer();
  enable_interrupts();
	
  waitms(500); // Give PuTTY time to start
  eputs("\x1b[2J\x1b[1;1H"); // Clear screen using ANSI escape sequence.
  SendATCommand("AT+DVID0F28\r\n");
  
  SendATCommand("AT+VER\r\n");
  SendATCommand("AT+BAUD\r\n");
  SendATCommand("AT+RFID\r\n");
  SendATCommand("AT+DVID\r\n");
  SendATCommand("AT+RFC\r\n");
  SendATCommand("AT+POWE\r\n");
  SendATCommand("AT+CLSS\r\n");
  
  while(1){
      count=GetPeriod(35);
      if(count>0)
	{
	  f=(F_CPU*35L)/count;
	  l=1000000000000000/(4*PI*PI*f*f*50);
	  //eputs(" l=");
	  //PrintNumber(l, 10, 10);
	  //eputs("          \r\n");
	}
      else
	{
	  //eputs("NO SIGNAL                     \r");
	}
	

      // Int to string
      induc[0] = l/1000 + 48;
      induc[1] = (l % 1000) / 100 + 48;
      induc[2] = (l % 100) / 10 + 48;
      induc[3] = (l % 10) + 48;
      
      induc[4] = ',';

      // Checksum - sum of four digits, modulo 10
      induc[5] = (l/1000 + (l % 1000) / 100 + (l % 100) / 10 + l % 10) % 10 + 48;
      induc[6] = 0;
      
      eputs1(induc);
      eputs1("\r\n");
      

      wait_and_RX(100, buff);

      if (!parse_buffer(buff, &joystick_X, &joystick_Y)) { // Check for error
	joystick_to_pwm(joystick_X, joystick_Y);
      } // If there is an error, hold PWM values
      
      
    }
}
