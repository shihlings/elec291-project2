//  LCD in 4-bit interface mode
#include <EFM8LB1.h>
#include "lcd.h"
#include "jdy40.h"
#include "global.h"

// Uses Timer3 to delay <us> micro-seconds. 
void Timer3us(unsigned char us)
{
	unsigned char i;               // usec counter
	
	// The input for Timer 3 is selected as SYSCLK by setting T3ML (bit 6) of CKCON0:
	CKCON0|=0b_0100_0000;
	
	TMR3RL = (-(SYSCLK)/1000000L); // Set Timer3 to overflow in 1us.
	TMR3 = TMR3RL;                 // Initialize Timer3 for first overflow
	
	TMR3CN0 = 0x04;                 // Sart Timer3 and clear overflow flag
	for (i = 0; i < us; i++)       // Count <us> overflows
	{
		while (!(TMR3CN0 & 0x80));  // Wait for overflow
		TMR3CN0 &= ~(0x80);         // Clear overflow indicator
	}
	TMR3CN0 = 0 ;                   // Stop Timer3 and clear overflow flag
}

void waitms (unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) Timer3us(250);
}

void LCD_pulse (void)
{
	LCD_E=1;
	Timer3us(40);
	LCD_E=0;
}

void LCD_byte (unsigned char x)
{
	// The accumulator in the C8051Fxxx is bit addressable!
	ACC=x; //Send high nible
	LCD_D7=ACC_7;
	LCD_D6=ACC_6;
	LCD_D5=ACC_5;
	LCD_D4=ACC_4;
	LCD_pulse();
	Timer3us(40);
	ACC=x; //Send low nible
	LCD_D7=ACC_3;
	LCD_D6=ACC_2;
	LCD_D5=ACC_1;
	LCD_D4=ACC_0;
	LCD_pulse();
}

void WriteData (unsigned char x)
{
	LCD_RS=1;
	LCD_byte(x);
	waitms(2);
}

void WriteCommand (unsigned char x)
{
	LCD_RS=0;
	LCD_byte(x);
	waitms(5);
}

void LCD_4BIT (void)
{
	LCD_E=0; // Resting state of LCD's enable is zero
	//LCD_RW=0; // We are only writing to the LCD in this program
	waitms(20);
	// First make sure the LCD is in 8-bit mode and then change to 4-bit mode
	WriteCommand(0x33);
	WriteCommand(0x33);
	WriteCommand(0x32); // Change to 4-bit mode

	// Configure the LCD
	WriteCommand(0x28);
	WriteCommand(0x0c);
	WriteCommand(0x01); // Clear screen command (takes some time)
	waitms(20); // Wait for clear screen command to finsih.
}

void LCDprint(char * string, unsigned char line, bit clear)
{
	int j;

	WriteCommand(line==2?0xc0:0x80);
	waitms(5);
	for(j=0; string[j]!=0; j++)	WriteData(string[j]);// Write the message
	if(clear) for(; j<CHARS_PER_LINE; j++) WriteData(' '); // Clear the rest of the line
}

void prepLCDl10(char* lcdbuff, unsigned int RX, unsigned int RY)
{
	lcdbuff[0] = 'X';
	lcdbuff[1] = ':';
	numToChar5(lcdbuff+2, RX);
	
	lcdbuff[7] = ' ';
	lcdbuff[8] = ' ';
	
	lcdbuff[9] = 'Y';
	lcdbuff[10] = ':';
	numToChar5(lcdbuff+11, RY);
	lcdbuff[16] = '\0';
}

void prepLCDl11(char* lcdbuff, unsigned int percent)
{
	numToChar4(lcdbuff+6, percent);
	lcdbuff[0] = 'B';
	lcdbuff[1] = 'A';
	lcdbuff[2] = 'T';
	lcdbuff[3] = '%';
	lcdbuff[4] = ' ';
	lcdbuff[5] = '=';
	lcdbuff[6] = ' ';
	lcdbuff[10] = '%';
	lcdbuff[11] = '\0';
}

void prepLCDl2(char* lcdbuff, unsigned int ind, unsigned int baseline)
{
	lcdbuff[0] = 'L';
	lcdbuff[1] = ':';
	numToChar4(lcdbuff+2, ind);
	
	lcdbuff[6] = ' ';
	
	lcdbuff[7] = 'B';
	lcdbuff[8] = 'a';
	lcdbuff[9] = 's';
	lcdbuff[10] = 'e';
	lcdbuff[11] = ':';
	numToChar4(lcdbuff+12, baseline);
	lcdbuff[16] = '\0';
}
