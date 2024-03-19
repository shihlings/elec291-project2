void UART1_Init (unsigned long baudrate);
void putchar1 (char c);
void sendstr1 (char * s);
char getchar1 (void);
char getchar1_with_timeout (void);
void getstr1 (char * s);
bit RXU1 (void);
void waitms_or_RI1 (unsigned int ms);