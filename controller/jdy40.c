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

// wait for 'ms' milliseconds, if input is received, store in 'buff' while waiting
void wait_and_RI1 (unsigned int ms, char* buff)
{
	unsigned int j;
	unsigned char k;
	bit received = 0;
	for(j=0; j<19; j++)
	{
		buff[j] = ' ';
	}
	buff[19] = '\0';
	
	for(j=0; j<ms; j++)
	{
		for (k=0; k<8; k++)
		{
			if(RXU1())
			{
				if (received)
				{
					for(j=0; j<20; j++)
					{
						buff[j] = ' ';
					}
					buff[19] = '\0';
				}
				getstr1(buff);
			}
			Timer3us(125);
		}
	}
}

// prepares output string for RF sender
// output format "XXXXX;YYYYY;SSSSS."
// XXXXX is RX
// YYYYY is RY
// SSSSS is 5 digit checksum indicating RX+RY
void prepstr(char* buff, unsigned int RX, unsigned int RY)
{	
	numToChar5(buff+0, RX);
	numToChar5(buff+2, RY);
	numToChar5(buff+4, RX+RY);
	buff[6] = '\r';
	buff[7] = '\n';
	buff[8] = '\0';
}

// parsing formatted string from RF receiver
// expected input "XXXX,Y"
// XXXX is 4 digit uintA
// Y is 1 digit checksum = (X+X+X+X)%10
void parseind(char* buff, unsigned int* new_ind, unsigned int* checksum)
{
	//check if ',' is present
	if (buff[4] == ',')
	{
		// if ',' is present, parse new_ind and checksum
		*new_ind = (buff[0]-'0') * 1000;
		*new_ind += (buff[1]-'0') * 100;
		*new_ind += (buff[2]-'0') * 10;
		*new_ind += (buff[3]-'0');
		
		*checksum = (buff[5]-'0');
	}
}

void numToChar5(char* buff, unsigned int num)
{
	buff[0] = (num / 10000) + '0';
	num -= (buff[0] - '0')* 10000;
	buff[1] = (num / 1000) + '0';
	num -= (buff[1] - '0')*1000;
	//buff[2] = (num / 100) + '0';
	//num -= (buff[2]- '0')*100;
	//buff[3] = (num / 10) + '0';
	//num -= (buff[3]- '0')*10;
	//buff[4] = num + '0';
}

void numToChar4(char* buff, unsigned int num)
{
	buff[0] = (num / 1000) + '0';
	num -= (buff[0] - '0')*1000;
	buff[1] = (num / 100) + '0';
	num -= (buff[1]- '0')*100;
	buff[2] = (num / 10) + '0';
	num -= (buff[2]- '0')*10;
	buff[3] = num + '0';
}