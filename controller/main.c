#include <EFM8LB1.h>
#include <stdio.h>
#include "lcd.h"
#include "joystick.h"
#include "jdy40.h"

idata char buff[20];

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
	unsigned int RX = 0;
	unsigned int RY = 0;
	char buff[20];
	unsigned int cnt = 0;
	
	// Configure the LCD
	LCD_4BIT();
	
	UART1_Init(9600);
	
    waitms(500); // Give PuTTy a chance to start before sending
	printf("\x1b[2J"); // Clear screen using ANSI escape sequence.
	
	printf ("\n\nEFM8 Controller Test Program\n"
        "File: %s\n"
        "Compiled: %s, %s\n\n",
        __FILE__, __DATE__, __TIME__);

   	// Display something in the LCD
	LCDprint("CONTROLLER TEST", 1, 1);
	LCDprint("PROGRAM", 2, 1);
	
	InitPinADC(2, 1); // Configure P2.1 as analog input
	InitPinADC(2, 2); // Configure P2.2 as analog input
    InitADC();
	
	// We should select an unique device ID.  The device ID can be a hex
	// number from 0x0000 to 0xFFFF.
	// WE ARE USING 0x0F28
	SendATCommand("AT+DVID0F28\r\n");
	
	while(1)
	{
		RX = readVRX();
		RY = readVRY();
		printf("RX: %5d, RY: %5d\r", RX, RY);
		
		if(P3_7==0)
		{
			sprintf(buff, "JDY40 test %d\r\n", cnt++);
			sendstr1(buff);
			putchar('.');
			waitms_or_RI1(200);
		}
		if(RXU1())
		{
			getstr1(buff);
			printf("RX: %s\r\n", buff);
		}
	}
}
/*
void main (void)
{
	unsigned int cnt;
	
	waitms(500);
	printf("\r\nJDY-40 test\r\n");
	UART1_Init(9600);

	// To configure the device (shown here using default values).
	// For some changes to take effect, the JDY-40 needs to be power cycled.
	// Communication can only happen between devices with the
	// same RFID and DVID in the same channel.
	
	//SendATCommand("AT+BAUD4\r\n");
	//SendATCommand("AT+RFID8899\r\n");
	//SendATCommand("AT+DVID1122\r\n"); // Default device ID.
	//SendATCommand("AT+RFC001\r\n");
	//SendATCommand("AT+POWE9\r\n");
	//SendATCommand("AT+CLSSA0\r\n");
	
	// We should select an unique device ID.  The device ID can be a hex
	// number from 0x0000 to 0xFFFF.  In this case is set to 0xABBA
	SendATCommand("AT+DVID0F28\r\n");  

	// To check configuration
	SendATCommand("AT+VER\r\n");
	SendATCommand("AT+BAUD\r\n");
	SendATCommand("AT+RFID\r\n");
	SendATCommand("AT+DVID\r\n");
	SendATCommand("AT+RFC\r\n");
	SendATCommand("AT+POWE\r\n");
	SendATCommand("AT+CLSS\r\n");
	
	printf("\r\Press and hold the BOOT button to transmit.\r\n");
	
	cnt=0;
	
	while(1)
	{
		if(P3_7==0)
		{
			sprintf(buff, "JDY40 test %d\r\n", cnt++);
			sendstr1(buff);
			putchar('.');
			waitms_or_RI1(200);
		}
		if(RXU1())
		{
			getstr1(buff);
			printf("RX: %s\r\n", buff);
		}
	}
}
*/