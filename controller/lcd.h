#define LCD_RS P1_7
//#define LCD_RW Px_x // Not used in this code.  Connect to GND
#define LCD_E  P1_6
#define LCD_D4 P1_4
#define LCD_D5 P1_3
#define LCD_D6 P1_2
#define LCD_D7 P1_1
#define CHARS_PER_LINE 16
#define seg1 P3_1
#define seg2 P3_3

void Timer3us(unsigned char us);
void waitms (unsigned int ms);
void LCD_pulse (void);
void LCD_byte (unsigned char x);
void WriteData (unsigned char x);
void WriteCommand (unsigned char x);
void LCD_4BIT (void);
void LCDprint(char * string, unsigned char line, bit clear);
void prepLCDl10(char* lcdbuff, unsigned int RX, unsigned int RY);
void prepLCDl11(char* lcdbuff, unsigned int ind, unsigned int baseline);
void prepLCDl2(char* lcdbuff, unsigned int ind, unsigned int baseline);
