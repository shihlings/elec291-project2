#define SBUFSIZE 16
typedef struct 
{
	volatile unsigned head;
	volatile unsigned tail;
	volatile unsigned count;
	char buffer[SBUFSIZE];
} SerialBuffer1;

void initUART1(int baud);
void putBuf1(SerialBuffer1 *sbuf, char c);
char getBuf1(SerialBuffer1 *sbuf);
int rx_count1();
char egetc1(void);
int egets1(char *s,int Max);
void eputc1(const char c);
void eputs1(const char *s);
void printString1(const char *s);
void PrintNumber1(int N, int Base, int digits);
