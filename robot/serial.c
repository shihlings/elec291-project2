// Serial I/O routines.
// This routine will use interrupt driven serial data reception
// and blocking serial data transmission

#include "serial.h"
#include "lpc824.h"
static SerialBuffer RXBuffer;
void UART0_isr(void);

void initUART(int baudrate)
{		
	SYSCON_PRESETCTRL &= ~BIT3;   // put uart in reset 
	// initialize the receive buffer
	//RXBuffer.count = RXBuffer.head = RXBuffer.tail = 0;		
	SYSCON_SYSAHBCLKCTRL |= BIT14; // enable USART0 clock
	SYSCON_PRESETCTRL |= BIT3;   // take uart out of reset
	NVIC_ISER0 |= BIT3;  // Enable USART0 IRQ's in NVIC
	// Remap the IO pins for USART0
	// Want RXD on pin 19 (PIO0_0) and TXD on Pin 6 (PIO0_4) to match the
	// ISP setup.
	SWM_PINENABLE0 |= BIT0;	// Ensure special function on pin 8 is disabled
	// Pin doesn't appear to have a default "special" function
	SWM_PINASSIGN0 &= 0xffffff00;
	SWM_PINASSIGN0 |= 4; // Map TXD to PIO0_4
	SWM_PINASSIGN0 &= 0xffff00ff;
	SWM_PINASSIGN0 |= 0<<8; // Map RXD to PIO0_0
		
	// Baud rate generation:	
	SYSCON_UARTCLKDIV = 1;
	SYSCON_UARTFRGDIV = 0;
	SYSCON_UARTFRGMULT = 0;
	// rx data signal is sampled 16 times faster than baud rate
	// so need to "scale up" by factor of 16 when calculating
	// baud rate
	USART0_BRG = (60000000) / (baudrate*16);

	USART0_INTENSET = BIT0; // Enable RX interrupts
	USART0_CTL = 0;
	// Config USART : 8 bit data, 2 stops, no parity.  Enable
	USART0_CFG |= BIT6+BIT2+BIT0;		
}

void UART0_isr(void)
{	
	int Source=USART0_INTSTAT;	
	if (Source & BIT0) // RX Interrupt
	{
		putBuf(&RXBuffer,USART0_RXDAT);
	}
}

void putBuf(SerialBuffer *sbuf, char c)
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

char getBuf(SerialBuffer *sbuf)
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

int rx_count()
{
	return RXBuffer.count;
}

void eputc(char c)
{
	int timeout=0xffff;
	// Wait for transmitter to be ready with timeout
	while( (timeout--) && ((USART0_STAT & BIT2)==0));	
	USART0_TXDAT = c;
}

void eputs(const char *String)
{	
	while(*String)
	{
		eputc(*String);
		String++;
	}
}

char egetc()
{
	return getBuf(&RXBuffer);
}

int egets(char *s,int Max)
{
#define NEWLINE 0x0a
	// read from the comms port until end of string
	// or newline is encountered.  Buffer is terminated with null
	// returns number of characters read on success
	// returns 0 or -1 if error occurs
	// Warning: This is a blocking call.
	int Len;
	char c;
	Len=0;
	c = 0;
	while ( (Len < Max-1) && (c != NEWLINE) )
	{   
		do {
			c=egetc();
		} while (c==0); // wait for a character
		eputc(c);
		s[Len++] = c;
	}
	if (Len>0)
	{
		s[Len]=0;
	}	
	return Len;
}

void printString(const char *String)
{
	eputs(String);
	eputs("\r\n");
}

char HexDigit[]="0123456789ABCDEF";
void PrintNumber(long int val, int Base, int digits)
{ 
	int j;
	#define NBITS 32
	char buff[NBITS+1];
	buff[NBITS]=0;

	j=NBITS-1;
	while ( (val>0) | (digits>0) )
	{
		buff[j--]=HexDigit[val%Base];
		val/=Base;
		if(digits!=0) digits--;
	}
	eputs(&buff[j+1]);
}

