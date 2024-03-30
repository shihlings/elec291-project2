#include <EFM8LB1.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "lcd.h"
#include "jdy40.h"

void UART1_Init (unsigned long baudrate)
{
    SFRPAGE = 0x20;
	SMOD1 = 0x0C; // no parity, 8 data bits, 1 stop bit
	SCON1 = 0x10;
	SBCON1 =0x00;   // disable baud rate generator
	SBRL1 = 0x10000L-((SYSCLK/baudrate)/(12L*2L));
	TI1 = 1; // indicate ready for TX
	SBCON1 |= 0x40;   // enable baud rate generator
	SFRPAGE = 0x00;
}

void putchar1 (char c) 
{
    SFRPAGE = 0x20;
	while (!TI1);
	TI1=0;
	SBUF1 = c;
	SFRPAGE = 0x00;
}

void sendstr1 (char * s)
{
	while(*s)
	{
		putchar1(*s);
		s++;	
	}
}

char getchar1 (void)
{
	char c;
    SFRPAGE = 0x20;
	while (!RI1);
	RI1=0;
	// Clear Overrun and Parity error flags 
	SCON1&=0b_0011_1111;
	c = SBUF1;
	SFRPAGE = 0x00;
	return (c);
}

char getchar1_with_timeout (void)
{
	char c;
	unsigned int timeout;
    SFRPAGE = 0x20;
    timeout=0;
	while (!RI1)
	{
		SFRPAGE = 0x00;
		Timer3us(20);
		SFRPAGE = 0x20;
		timeout++;
		if(timeout==25000)
		{
			SFRPAGE = 0x00;
			return ('\n'); // Timeout after half second
		}
	}
	RI1=0;
	// Clear Overrun and Parity error flags 
	SCON1&=0b_0011_1111;
	c = SBUF1;
	SFRPAGE = 0x00;
	return (c);
}

void getstr1 (char * s)
{
	char c;
	
	while(1)
	{
		c=getchar1_with_timeout();
		if(c=='\n')
		{
			*s=0;
			return;
		}
		*s=c;
		s++;
	}
}

// RXU1 returns '1' if there is a byte available in the receive buffer of UART1
bit RXU1 (void)
{
	bit mybit;
    SFRPAGE = 0x20;
	mybit=RI1;
	SFRPAGE = 0x00;
	return mybit;
}

void waitms_or_RI1 (unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
	{
		for (k=0; k<4; k++)
		{
			if(RXU1()) return;
			Timer3us(250);
		}
	}
}

void wait_and_RI1 (unsigned int ms, char* buff)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<20; j++)
	{
		buff[j] = ' ';
	}
	
	for(j=0; j<ms; j++)
	{
		for (k=0; k<4; k++)
		{
			if(RXU1())
			{
				getstr1(buff);
			}
			Timer3us(250);
		}
	}
}

void prepstr(char* buff, unsigned int RX, unsigned int RY)
{
	unsigned int temp = RX+RY;
	buff[0] = (RX / 10000) + '0';
	RX -= (buff[0] - '0') * 10000;
	buff[1] = (RX / 1000) + '0';
	RX -= (buff[2] - '0')*1000;
	buff[2] = (RX / 100) + '0';
	RX -= (buff[3]- '0')*100;
	buff[3] = (RX / 10) + '0';
	RX -= (buff[4]- '0')*10;
	buff[4] = RX + '0';
	
	buff[5] = ';';
	
	buff[6] = (RY / 10000) + '0';
	RX -= (buff[6] - '0')* 10000;
	buff[7] = (RY / 1000) + '0';
	RX -= (buff[7] - '0')*1000;
	buff[8] =(RY / 100) + '0';
	RX -= (buff[8]- '0')*100;
	buff[9] = (RY / 10) + '0';
	RX -= (buff[9]- '0')*10;
	buff[10] = RY + '0';
	
	buff[11] = '!';
	
	buff[12] = (temp / 10000) + '0';
	temp -= (buff[12] - '0')* 10000;
	buff[13] = (temp / 1000) + '0';
	temp -= (buff[13] - '0')*1000;
	buff[14] = (temp / 100) + '0';
	temp -= (buff[14]- '0')*100;
	buff[15] = (temp / 10) + '0';
	temp -= (buff[15]- '0')*10;
	buff[16] = temp + '0';

	buff[17] = '.';
	buff[18] = '\0';
}

void parseind(char* buff, unsigned int* new_ind, unsigned int* checksum)
{
	if (buff[4] == ',')
	{
		*new_ind = buff[0] * 1000;
		*new_ind += buff[1] * 100;
		*new_ind += buff[2] * 10;
		*new_ind += buff[3];
		
		*checksum = buff[5] * 1000;
		*checksum += buff[6] * 100;
		*checksum += buff[7] * 10;
		*checksum += buff[8];
	}
}