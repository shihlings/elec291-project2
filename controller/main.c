/* 
	COMMENT OUT THE DEBUG FLAG IN "GLOBAL.H" WHEN NOT DEBUGGING/TESTING.
	COMMENT OUT THE SHUTUP FLAG IN "GLOBAL.H" TO ENABLE ALL BUZZER SOUNDS.
*/

#include <EFM8LB1.h>
#include <stdio.h>
#include "lcd.h"
#include "joystick.h"
#include "jdy40.h"
#include "global.h"
#include "buzzer.h"

#define VDD 3.3035 // The measured value of VDD in volts
idata char buff[25];
unsigned int ind = 0;
unsigned int old_ind = 0;
unsigned int baseline = 0;
unsigned int display_mode = 0;
bit SWITCH_LCD_pressed = 0;

// toggle buzzer pin upon triggering interrupt
void Timer2_ISR (void) interrupt INTERRUPT_TIMER2
{
	TF2H = 0; // Clear Timer2 interrupt flag
	OUT0=!OUT0;
}


float Volts_at_Pin(unsigned char pin)
{
	 return ((ADC_at_Pin(pin)*VDD)/0b_0011_1111_1111_1111);
}

int getsn (char * buff, int len)
{
	int j;
	char c;
	
	for(j=0; j<(len-1); j++)
	{
		c=getchar();
		if ( (c=='\n') || (c=='\r') )
		{
			buff[j]=0;
			return j;
		}
		else
		{
			buff[j]=c;
		}
	}
	buff[j]=0;
	return len;
}

void SendATCommand (char * s)
{
	printf("Command: %s", s);
	P2_0=0; // 'set' pin to 0 is 'AT' mode.
	waitms(5);
	sendstr1(s);
	getstr1(buff);
	waitms(10);
	P2_0=1; // 'set' pin to 1 is normal operation mode.
	printf("Response: %s\r\n", buff);
}

#ifdef DEBUG
void startupDebugDisplay ()
{
	waitms(500); // Give PuTTy a chance to start before sending
	printf("\x1b[2J"); // Clear screen using ANSI escape sequence.
	
	printf ("\n\nEFM8 Controller Test Program\n"
        "File: %s\n"
        "Compiled: %s, %s\n\n"
        "----------DEBUG ENABLED----------\n\n",
        __FILE__, __DATE__, __TIME__);
}
#endif

void initALL()
{
	// Configure the LCD
	LCD_4BIT();
	
	// Configure joystick analog inputs
	InitPinADC(2, 5); // Configure P2.5 as analog input
	InitPinADC(2, 2); // Configure P2.2 as analog input
	InitPinADC(3,0);
    InitADC();
    
    // We should select an unique device ID.  The device ID can be a hex
	// number from 0x0000 to 0xFFFF.
	// WE ARE USING 0x0F28
	UART1_Init(9600);
	SendATCommand("AT+DVID0F28\r\n");
#ifdef DEBUG
	SendATCommand("AT+VER\r\n");
	SendATCommand("AT+BAUD\r\n");
	SendATCommand("AT+RFID\r\n");
	SendATCommand("AT+DVID\r\n");
	SendATCommand("AT+RFC\r\n");
	SendATCommand("AT+POWE\r\n");
	SendATCommand("AT+CLSS\r\n");
	printf("\r\n");
#endif
}

#ifdef DEBUG
#ifndef SHUTUP
// tests buzzer by playing tones from low to high freq
void testBuzzer ()
{
	unsigned long int f;
	
	TR2=1; //Start timer 2
	for (f=200; f<2000;)
	{
		setFreq(f);
		waitms(250);
		f+=100;
	}
	TR2 = 0;
}
#endif
#endif 


// if frequency > 200, play, otherwize, mute
void compAndChangeFreq(unsigned int freq)
{
	if (freq > 200)
	{
		setFreq(freq);
		TR2 = 1;
	}
	else
	{
		setFreq(1);
		TR2 = 0;
	}
}

void main (void)
{
	char buff[10];
	unsigned int RX = 0;
	unsigned int RY = 0;
	float batvot;
	unsigned int temp = 0;
	unsigned int new_ind = 1;
	unsigned int checksum = 0;
	unsigned int percent;
	char lcdbuff[17];
	
	// Turn off Buzzer
	TR2=0;
	
	// show program info in PuTTY if DEBUG flag is set
#ifdef DEBUG	
    startupDebugDisplay();
#endif
	
	// initialize all devices
	initALL();

#ifdef DEBUG
#ifndef SHUTUP
	//testBuzzer();
#endif
#endif

	while(1)
	{
		//read battery voltage
		// read joystick data
		RX = ADC_at_Pin(VRX);
		RY = ADC_at_Pin(VRY);
		//Measuring voltage
		batvot = Volts_at_Pin(BP);
		percent = (int)(batvot/3.0*100.0);

		// put data on LCD
		if (display_mode == 0)
		{
			prepLCDl10(lcdbuff, RX, RY);
		}
		else if (display_mode == 1)
		{
			prepLCDl11(lcdbuff, ind, baseline);
			lcdbuff[0] = 'B';
			lcdbuff[1] = 'A';
			lcdbuff[2] = 'T';
			lcdbuff[3] = '%';
			lcdbuff[4] = ' ';
			lcdbuff[5] = '=';
			lcdbuff[6] = ' ';
			numToChar4(lcdbuff+7, percent); 

		}
		LCDprint(lcdbuff, 1, 1);
#ifdef DEBUG
		printf("\r\n");
		printf(lcdbuff);
		printf(" ");
#endif
		prepLCDl2(lcdbuff, ind, baseline);
		LCDprint(lcdbuff, 2, 1);
#ifdef DEBUG
		printf(lcdbuff);
		printf("\r\n");
#endif
		
		// send joystick data
		prepstr(buff, RX, RY);
		sendstr1(buff);
#ifdef DEBUG
		printf("TX: ");
		printf(buff);
		printf("\r\n");
#endif
		
		// wait and receive
		wait_and_RI1(50, buff);
#ifdef DEBUG
		printf("RX: ");
		printf(buff);
		printf("\r\n\n");
#endif

		// parse received data
		parseind(buff, &new_ind, &checksum);
		
		// validate data
		temp = (new_ind / 1000) + (new_ind % 1000) / 100 + (new_ind % 100) / 10 + (new_ind % 10);
		if (checksum == (temp % 10))
		{
			ind = new_ind;
		}
		
		// if button pressed, update baseline inductance
		if (RESET_IND == 0)
		{
			if (ind != 0)
			{
				baseline = ind;
			}
		}
		
		if (SWITCH_LCD == 0)
		{
			SWITCH_LCD_pressed = 1;
		}
		
		if (SWITCH_LCD_pressed == 1 && SWITCH_LCD != 0)
		{
			SWITCH_LCD_pressed = 0;
			display_mode = (display_mode + 1) % NUM_LCD_MODE;
		}
		
		// if controller just started up, immediately set baseline as current inductance.
		// baseline and ind are initialized with 0, it will continue resetting until 
		// valid values start appearing
		if (baseline == 0)
		{
			baseline = ind;
		}
		
#ifndef SHUTUP
		// compare inductance and play sound on buzzer
		// 		  |baseline - ind| 
		// freq = ---------------- * 2048
		//		         100
		// buzzer is loudest at 2048 
		if (baseline > ind && ind != 0)
		{
			temp = (baseline - (ind + old_ind) / 2) * 2048 / 100;
			compAndChangeFreq(temp);
		}
		else if (baseline < ind && ind != 0)
		{
			temp = ((ind + old_ind) / 2 - baseline) * 2048 / 100;
			compAndChangeFreq(temp);
		}
		old_ind = ind;

		
#endif
	}
}
