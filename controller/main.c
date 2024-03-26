#include <EFM8LB1.h>
#include <stdio.h>
#include "lcd.h"
#include "joystick.h"
#include "jdy40.h"
#include "global.h"
#include "buzzer.h"

idata char buff[20];

void Timer2_ISR (void) interrupt INTERRUPT_TIMER2
{
	TF2H = 0; // Clear Timer2 interrupt flag
	OUT0=!OUT0;
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

void main (void)
{
	unsigned long int f;
	unsigned int RX = 0;
	unsigned int RY = 0;
	char buff[20];
	char lcdbuff[17];
	unsigned int cnt = 0;

	// Configure the LCD
	LCD_4BIT(); 
	
#ifdef DEBUG	
    waitms(500); // Give PuTTy a chance to start before sending
	printf("\x1b[2J"); // Clear screen using ANSI escape sequence.
	
	printf ("\n\nEFM8 Controller Test Program\n"
        "File: %s\n"
        "Compiled: %s, %s\n\n"
        "----------DEBUG ENABLED----------\n\n",
        __FILE__, __DATE__, __TIME__);
#endif

   	// Display something in the LCD
	LCDprint("CONTROLLER TEST", 1, 1);
	LCDprint("PROGRAM", 2, 1);
	
	InitPinADC(2, 5); // Configure P2.5 as analog input
	InitPinADC(2, 2); // Configure P2.2 as analog input
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

	TR2=0;	
#ifdef DEBUG	
	TR2=1; //Start timer 2
	for (f=200; f<2000;)
	{
		setFreq(f);
		waitms(250);
		f+=100;
	}
	TR2 = 0;
#endif

	while(1)
	{
		RX = readVRX();
		RY = readVRY();
#ifdef DEBUG
		printf("RX: %05d, RY: %05d\r", RX, RY);
#endif

		sprintf(lcdbuff, "%05d", RX);
		LCDprint(lcdbuff, 1, 1);
		sprintf(lcdbuff, "%05d", RY);
		LCDprint(lcdbuff, 2, 1);
		
		sprintf(buff, "%05d;%05d!%05d.\r\n", RX, RY, RX+RY);
		sendstr1(buff);
		waitms_or_RI1(100);

		if(RXU1())
		{
			getstr1(buff);
#ifdef DEBUG
			printf("RX: %s\r\n", buff);
#endif
		}
	}
}