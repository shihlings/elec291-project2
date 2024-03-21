// Serial I/O routines.
// This routine will use interrupt driven serial data reception
// and blocking serial data transmission

#include "serial1.h"
#include "serial.h"
#include "lpc824.h"
static SerialBuffer1 RXBuffer1;
void UART1_isr1(void);

void initUART1(int baudrate)
{		
	SYSCON_PRESETCTRL &= ~BIT4;   // put UART1 in reset 
	// initialize the receive buffer
	RXBuffer1.count = RXBuffer1.head = RXBuffer1.tail = 0;		
	SYSCON_SYSAHBCLKCTRL |= BIT15; // enable UART1 clock
	SYSCON_PRESETCTRL |= BIT4;   // take UART1 out of reset
	NVIC_ISER0 |= BIT4;  // Enable USART1 IRQ's in NVIC
	
	// Remap the IO pins for USART1. Want RXD on pin 1 (PIO0_23) and TXD on Pin 2 (PIO0_17)

	SWM_PINASSIGN1 &= 0xff0000ff;
	SWM_PINASSIGN1 |= 0x00171100; // Map RXD to PIO0_15 and TXD to PIO0_1
	
	// Baud rate generation.	
	SYSCON_UARTCLKDIV = 1;
	SYSCON_UARTFRGDIV = 0;
	SYSCON_UARTFRGMULT = 0;
	// rx data signal is sampled 16 times faster than baud rate
	// so need to "scale up" by factor of 16 when calculating
	// baud rate
	USART1_BRG = (60000000) / (baudrate*16);

	USART1_INTENSET = BIT0; // Enable RX interrupts
	USART1_CTL = 0;
	// Config USART1 : 8 bit data, 1 stop, no parity.  Enable
	USART1_CFG = (BIT2|BIT0);
}

void UART1_isr(void)
{	
	int Source=USART1_INTSTAT;	
	if (Source & BIT0) // RX Interrupt
	{
		putBuf1(&RXBuffer1,USART1_RXDAT);
	}
}

void putBuf1(SerialBuffer1 *sbuf, char c)
{
	if (sbuf->count < SBUFSIZE)
	{
		disable_interrupts();
		sbuf->count++;
		sbuf->buffer[sbuf->head] = c;
		sbuf->head=(sbuf->head+1) % SBUFSIZE;
		enable_interrupts();
	}
}

char getBuf1(SerialBuffer1 *sbuf)
{
	char c=0;
	if (sbuf->count >0 )
	{
		disable_interrupts();
		sbuf->count--;
		c=sbuf->buffer[sbuf->tail];	
		sbuf->tail=(sbuf->tail+1) % SBUFSIZE;
		enable_interrupts();
	}
	return c;
}

int rx_count1()
{
	return RXBuffer1.count;
}

void eputc1(char c)
{
	long int timeout=0x1ffff;
	// Wait for transmitter to be ready with timeout
	while( (timeout--) && ((USART1_STAT & BIT2)==0));
	USART1_TXDAT = c;
}

void eputs1(const char *String)
{	
	while(*String)
	{
		eputc1(*String);
		String++;
	}
}

char egetc1()
{
	return getBuf1(&RXBuffer1);
}

int egets1(char *s,int Max)
{
	long int timeout;
	// read from the comms port until end of string
	// or newline is encountered.  Buffer is terminated with null
	// returns number of characters read on success
	// returns 0 or -1 if error occurs
	// Warning: This is a blocking call.
	int Len;
	char c;
	Len=0;
	c = 0;
	timeout=0;
	while ( (Len < Max-1) && (c != '\n') )
	{   
		do {
			c=egetc1();
		} while (c==0); // wait for a character
		//eputc1(c); // echo? If you want echo, uncomment this line
		if(c != '\n') s[Len++] = c;
		if(++timeout>1000000)
		{
			break;
		}
	}
	if (Len>0)
	{
		s[Len]=0;
	}	
	return Len;
}

void printString1(const char *String)
{
	eputs1(String);
	eputs1("\r\n");
}

void PrintNumber1(int N, int Base, int digits)
{ 
	char HexDigit[]="0123456789ABCDEF";
	int j;
	#define NBITS 32
	char buff[NBITS+1];
	buff[NBITS]=0;

	j=NBITS-1;
	while ( (N>0) | (digits>0) )
	{
		buff[j--]=HexDigit[N%Base];
		N/=Base;
		if(digits!=0) digits--;
	}
	eputs1(&buff[j+1]);
}

