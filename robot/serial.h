#define SBUFSIZE 16
typedef struct 
{
	volatile unsigned head;
	volatile unsigned tail;
	volatile unsigned count;
	char buffer[SBUFSIZE];
} SerialBuffer;

void initUART(int baud);
void putBuf(SerialBuffer *sbuf, char c);
char getBuf(SerialBuffer *sbuf);
int rx_count();
char egetc(void);
int egets(char *s,int Max);
void eputc(const char c);
void eputs(const char *s);
void printString(const char *s);
void PrintNumber(long int N, int Base, int digits);

