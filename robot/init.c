// Initialization and interrupt vectors for the LPC1114 microcontroller
// No claims are made as to the suitability of this code for any 
// purpose whatsoever.  Use at your own risk!
// Does not include initialization for C++ global/static objects
// so probably best to use this with C projects for now.
// Latest version of this code can be found by visiting
// http://eleceng.dit.ie/frank and follow the links
// Author: Frank Duignan

#include "lpc824.h"
void init(void);
void clock_init();
void Default_Handler(void);
void SysTick(void);
extern void UART0_isr(void);
void main(void);
void STC_IRQ_Handler(void);

// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;

// the section "vectors" is placed at the beginning of flash 
// by the linker script
const void * Vectors[] __attribute__((section(".vectors"))) ={
	(void *)(RAM_START+RAM_SIZE), 	/* Top of stack */ 
	init,   						/* Reset Handler */
	Default_Handler,				/* NMI */
	Default_Handler,				/* Hard Fault */
	0,	                			/* Reserved */
	0,            			 	    /* Reserved */
	0,                  			/* Reserved */
	0,                  			/* Reserved */
	0,                  			/* Reserved */
	0,                  			/* Reserved */
	0,                  			/* Reserved */
	Default_Handler,				/* SVC */
	0,                 				/* Reserved */
	0,                 				/* Reserved */
	Default_Handler,   				/* PendSV */
	Default_Handler, 				/* SysTick */		
/* External interrupt handlers follow */
	Default_Handler,				/* 0 SPI0_IRQ */
	Default_Handler,				/* 1 SPI1_IRQ */
	Default_Handler,				/* 2 RESERVED */
	UART0_isr,				/* 3 UART0_IRQ */
	Default_Handler,				/* 4 UART1_IRQ */
	Default_Handler,				/* 5 UART2_IRQ */
	Default_Handler,				/* 6 RESERVED */
	Default_Handler,				/* 7 I2C1_IRQ */
	Default_Handler,				/* 8 I2C0_IRQ */
	STC_IRQ_Handler,		/* 9 SCT_IRQ */
	Default_Handler,				/* 10 MRT_IRQ */
	Default_Handler,				/* 11 CMP_IRQ */
	Default_Handler,				/* 12 WDT_IRQ */
	Default_Handler,				/* 13 BOD_IRQ */
	Default_Handler,				/* 14 FLASH_IRQ */
	Default_Handler,				/* 15 WKT_IRQ */
	Default_Handler,				/* 16 ADC_SEQA_IRQ */
	Default_Handler,				/* 17 ADC_SEQB_IRQ */
	Default_Handler,				/* 18 ADC_THCMP_IRQ */
	Default_Handler,				/* 19 ADC_OVR_IRQ */
	Default_Handler,				/* 20 DMA_IRQ */
	Default_Handler,				/* 21 I2C2_IRQ */
	Default_Handler,				/* 22 I2C3_IRQ */
	Default_Handler,				/* 23 RESERVED */
	Default_Handler,				/* 24 PININT0_IRQ */
	Default_Handler,				/* 25 PININT1_IRQ */
	Default_Handler,				/* 26 PININT2_IRQ */
	Default_Handler,				/* 27 PININT3_IRQ */
	Default_Handler,				/* 28 PININT4_IRQ */
	Default_Handler,				/* 29 PININT5_IRQ */
	Default_Handler,				/* 30 PININT6_IRQ */
	Default_Handler,				/* 31 PININT7_IRQ */
};

void clock_init()
{
	// NOT PORTED TO LPC824 YET
	// This function sets the main clock to the PLL
	// The PLL input is the built in 12MHz RC oscillator
	// This is multiplied up to 60MHz for the main clock
	// MSEL=4 (i.e.M=5), PSEL = 0 (P=1) see page 35 of UM10800 user manual
	SYSCON_PDRUNCFG &= ~BIT7; // Power up the PLL.
	SYSCON_SYSPLLCLKSEL = 0; // select internal RC oscillator
	SYSCON_SYSPLLCLKUEN = 1; // inform PLL of update	
	SYSCON_SYSPLLCTRL = (4 << 0) | (0 << 5); // set divisors/multipliers
	SYSCON_SYSPLLCLKUEN = 1; // inform PLL of update	
	SYSCON_MAINCLKSEL = 3; // Use PLL as main clock
	SYSCON_MAINCLKUEN = 1; // Inform core of clock update
	//SYSCON_SYSAHBCLKDIV = 2; // Keep System clock <= 30MHz UNSURE ABOUT THIS 
}

void init()
{
// do global/static data initialization
	unsigned char *src;
	unsigned char *dest;
	unsigned len;
	clock_init(); // boost speed to 30MHz
	src= &INIT_DATA_VALUES;
	dest= &INIT_DATA_START;
	len= &INIT_DATA_END-&INIT_DATA_START;
	while (len--)
		*dest++ = *src++;
// zero out the uninitialized global/static variables
	dest = &BSS_START;
	len = &BSS_END - &BSS_START;
	while (len--)
		*dest++=0;
	main();
}

void Default_Handler()
{
	while(1);
}
