//  LCD in 4-bit interface mode
#include <EFM8LB1.h>
#include "lcd.h"
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

void prepLCDl1(char* lcdbuff, unsigned int RX, unsigned int RY)
{
	lcdbuff[0] = 'X';
	lcdbuff[1] = ':';
	lcdbuff[2] = (RX / 10000) + '0';
	RX -= (lcdbuff[2] - '0') * 10000;
	lcdbuff[3] = (RX / 1000) + '0';
	RX -= (lcdbuff[3] - '0')*1000;
	lcdbuff[4] = (RX / 100) + '0';
	RX -= (lcdbuff[4]- '0')*100;
	lcdbuff[5] = (RX / 10) + '0';
	RX -= (lcdbuff[5]- '0')*10;
	lcdbuff[6] = RX + '0';
	
	lcdbuff[7] = ' ';
	lcdbuff[8] = ' ';
	lcdbuff[9] = ' ';
	
	lcdbuff[10] = 'Y';
	lcdbuff[11] = ':';
	lcdbuff[12] = (RY / 10000) + '0';
	RY -= (lcdbuff[12] - '0') * 10000;
	lcdbuff[13] = (RY / 1000) + '0';
	RY -= (lcdbuff[13] - '0')*1000;
	lcdbuff[14] = (RY / 100) + '0';
	RY -= (lcdbuff[14]- '0')*100;
	lcdbuff[15] = (RY / 10) + '0';
	RY -= (lcdbuff[15]- '0')*10;
	lcdbuff[16] = RY + '0';
	lcdbuff[17] = '\0';
}

void prepLCDl2(char* lcdbuff, unsigned int ind, unsigned int baseline)
{
	lcdbuff[0] = 'L';
	lcdbuff[1] = ':';
	lcdbuff[2] = (ind / 1000) + '0';
	ind -= (lcdbuff[2] - '0') * 1000;
	lcdbuff[3] = (ind / 100) + '0';
	ind -= (lcdbuff[3] - '0')*100;
	lcdbuff[4] = (ind / 10) + '0';
	ind -= (lcdbuff[4]- '0')*10;
	lcdbuff[5] = ind + '0';
	
	lcdbuff[6] = ' ';
	lcdbuff[7] = ' ';
	
	lcdbuff[8] = 'B';
	lcdbuff[9] = 'a';
	lcdbuff[10] = 's';
	lcdbuff[11] = 'e';
	lcdbuff[12] = ':';
	lcdbuff[13] = (baseline / 1000) + '0';
	baseline -= (lcdbuff[13] - '0')*1000;
	lcdbuff[14] = (baseline / 100) + '0';
	baseline -= (lcdbuff[14]- '0')*100;
	lcdbuff[15] = (baseline / 10) + '0';
	baseline -= (lcdbuff[15]- '0')*10;
	lcdbuff[16] = baseline + '0';
	lcdbuff[17] = '\0';
}