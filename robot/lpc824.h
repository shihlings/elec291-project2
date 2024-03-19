// lpc824.h
// LPC low level all-in-one header file for lpc824 devices
// principally targeted at lpc824 TSSOP20 package
// Written by Frank Duignan
// Latest version available at http://eleceng.dit.ie/frank/arm/
// Derived from UM10800 user manual from NXP semiconductors
// Naming convention: Register names are as described in UM10800
// No claims are made for the suitability, accuracy or otherwise of this file
// for any application
// Define some bitmasks
#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1 << 31)

typedef unsigned char byte;
// Macros to reduce typing later on
#define  REGISTER_32(ADDRESS) (*((volatile unsigned int *)(ADDRESS)))
#define  REGISTER_16(ADDRESS) (*((volatile unsigned short *)(ADDRESS)))
#define  REGISTER_8(ADDRESS) (*((volatile unsigned char *)(ADDRESS)))
// Macros to enable/disable global interrupts
#define enable_interrupts() asm(" cpsie i ")
#define disable_interrupts() asm(" cpsid i ")

// AHB stuff
#define RAM_START			0x10000000
#define RAM_SIZE			8192
#define ROM_START			0x1fff0000

#define CRC_BASE 			0x50000000
#define SCTIMER_BASE 		0x50004000
#define GPIO_BASE			0xa0000000
#define PIN_INT_BASE		0xa0004000
#define SYS_BASE			0xe000e000


// APB stuff
#define WWDT_BASE			0x40000000
#define MRT_BASE			0x40004000
#define WKT_BASE			0x40008000
#define SWITCH_MATRIX_BASE 	0x4000c000
#define ADC_BASE			0x4001c000
#define PMU_BASE			0x40020000
#define ANLG_COMP_BASE		0x40024000
#define DMA_ITRIG_BASE		0x40028000
#define DMA_INMUX_BASE		0x4002c000
#define DMA_BASE			0x50008000
#define FMC_BASE			0x40040000
#define IOCON_BASE			0x40044000
#define SYSCON_BASE			0x40048000
#define I2C0_BASE			0x40050000
#define I2C1_BASE			0x40054000
#define SPI0_BASE			0x40058000
#define SPI1_BASE			0x4005c000
#define USART0_BASE			0x40064000
#define USART1_BASE			0x40068000
#define USART2_BASE			0x4006c000
#define I2C2_BASE			0x40070000
#define I2C3_BASE			0x40074000

// SCTIMER
#define SCTIMER_CONFIG		REGISTER_32(SCTIMER_BASE + 0x000)
#define SCTIMER_CTRL		REGISTER_32(SCTIMER_BASE + 0x004)
#define SCTIMER_CTRL_L		REGISTER_16(SCTIMER_BASE + 0x004)
#define SCTIMER_CTRL_H		REGISTER_16(SCTIMER_BASE + 0x006)
#define SCTIMER_LIMIT		REGISTER_32(SCTIMER_BASE + 0x008)
#define SCTIMER_LIMIT_L		REGISTER_16(SCTIMER_BASE + 0x008)
#define SCTIMER_LIMIT_H		REGISTER_16(SCTIMER_BASE + 0x00a)
#define SCTIMER_HALT		REGISTER_32(SCTIMER_BASE + 0x00c)
#define SCTIMER_HALT_L		REGISTER_16(SCTIMER_BASE + 0x00c)
#define SCTIMER_HALT_H		REGISTER_16(SCTIMER_BASE + 0x00e)
#define SCTIMER_STOP		REGISTER_32(SCTIMER_BASE + 0x010)
#define SCTIMER_STOP_L		REGISTER_16(SCTIMER_BASE + 0x010)
#define SCTIMER_STOP_H		REGISTER_16(SCTIMER_BASE + 0x012)
#define SCTIMER_START		REGISTER_32(SCTIMER_BASE + 0x014)
#define SCTIMER_START_L		REGISTER_16(SCTIMER_BASE + 0x014)
#define SCTIMER_START_H		REGISTER_16(SCTIMER_BASE + 0x016)
#define SCTIMER_COUNT		REGISTER_32(SCTIMER_BASE + 0x040)
#define SCTIMER_COUNT_L		REGISTER_16(SCTIMER_BASE + 0x040)
#define SCTIMER_COUNT_H		REGISTER_16(SCTIMER_BASE + 0x042)
#define SCTIMER_STATE		REGISTER_32(SCTIMER_BASE + 0x044)
#define SCTIMER_STATE_L		REGISTER_16(SCTIMER_BASE + 0x044)
#define SCTIMER_STATE_H		REGISTER_16(SCTIMER_BASE + 0x046)
#define SCTIMER_INPUT		REGISTER_32(SCTIMER_BASE + 0x048)
#define SCTIMER_REGMODE		REGISTER_32(SCTIMER_BASE + 0x04c)
#define SCTIMER_REGMODE_L	REGISTER_16(SCTIMER_BASE + 0x04c)
#define SCTIMER_REGMODE_H	REGISTER_16(SCTIMER_BASE + 0x04e)
#define SCTIMER_OUTPUT		REGISTER_32(SCTIMER_BASE + 0x050)
#define SCTIMER_OUTPUTDIRCTRL		REGISTER_32(SCTIMER_BASE + 0x054)
#define SCTIMER_RES			REGISTER_32(SCTIMER_BASE + 0x058)
#define SCTIMER_DMAREQ0		REGISTER_32(SCTIMER_BASE + 0x05c)
#define SCTIMER_DMAREQ1		REGISTER_32(SCTIMER_BASE + 0x060)
#define SCTIMER_EVEN		REGISTER_32(SCTIMER_BASE + 0x0f0)
#define SCTIMER_EVFLAG		REGISTER_32(SCTIMER_BASE + 0x0f4)
#define SCTIMER_CONEN		REGISTER_32(SCTIMER_BASE + 0x0f8)
#define SCTIMER_CONFLAG		REGISTER_32(SCTIMER_BASE + 0x0fc)
#define SCTIMER_MATCH0		REGISTER_32(SCTIMER_BASE + 0x100)
#define SCTIMER_MATCH0_L	REGISTER_16(SCTIMER_BASE + 0x100)
#define SCTIMER_MATCH0_H	REGISTER_16(SCTIMER_BASE + 0x102)
#define SCTIMER_MATCH1		REGISTER_32(SCTIMER_BASE + 0x104)
#define SCTIMER_MATCH1_L	REGISTER_16(SCTIMER_BASE + 0x104)
#define SCTIMER_MATCH1_H	REGISTER_16(SCTIMER_BASE + 0x106)
#define SCTIMER_MATCH2		REGISTER_32(SCTIMER_BASE + 0x108)
#define SCTIMER_MATCH2_L	REGISTER_16(SCTIMER_BASE + 0x108)
#define SCTIMER_MATCH2_H	REGISTER_16(SCTIMER_BASE + 0x10a)
#define SCTIMER_MATCH3		REGISTER_32(SCTIMER_BASE + 0x10c)
#define SCTIMER_MATCH3_L	REGISTER_16(SCTIMER_BASE + 0x10c)
#define SCTIMER_MATCH3_H	REGISTER_16(SCTIMER_BASE + 0x10e)
#define SCTIMER_MATCH4		REGISTER_32(SCTIMER_BASE + 0x110)
#define SCTIMER_MATCH4_L	REGISTER_16(SCTIMER_BASE + 0x110)
#define SCTIMER_MATCH4_H	REGISTER_16(SCTIMER_BASE + 0x112)
#define SCTIMER_MATCH5		REGISTER_32(SCTIMER_BASE + 0x114)
#define SCTIMER_MATCH5_L	REGISTER_16(SCTIMER_BASE + 0x114)
#define SCTIMER_MATCH5_H	REGISTER_16(SCTIMER_BASE + 0x116)
#define SCTIMER_MATCH6		REGISTER_32(SCTIMER_BASE + 0x118)
#define SCTIMER_MATCH6_L	REGISTER_16(SCTIMER_BASE + 0x118)
#define SCTIMER_MATCH6_H	REGISTER_16(SCTIMER_BASE + 0x11a)
#define SCTIMER_MATCH7		REGISTER_32(SCTIMER_BASE + 0x11c)
#define SCTIMER_MATCH7_L	REGISTER_16(SCTIMER_BASE + 0x11c)
#define SCTIMER_MATCH7_H	REGISTER_16(SCTIMER_BASE + 0x11e)
#define SCTIMER_CAP0		REGISTER_32(SCTIMER_BASE + 0x100)
#define SCTIMER_CAP0_L		REGISTER_16(SCTIMER_BASE + 0x100)
#define SCTIMER_CAP0_H		REGISTER_16(SCTIMER_BASE + 0x102)
#define SCTIMER_CAP1		REGISTER_32(SCTIMER_BASE + 0x104)
#define SCTIMER_CAP1_L		REGISTER_16(SCTIMER_BASE + 0x104)
#define SCTIMER_CAP1_H		REGISTER_16(SCTIMER_BASE + 0x106)
#define SCTIMER_CAP2		REGISTER_32(SCTIMER_BASE + 0x108)
#define SCTIMER_CAP2_L		REGISTER_16(SCTIMER_BASE + 0x108)
#define SCTIMER_CAP2_H		REGISTER_16(SCTIMER_BASE + 0x10a)
#define SCTIMER_CAP3		REGISTER_32(SCTIMER_BASE + 0x10c)
#define SCTIMER_CAP3_L		REGISTER_16(SCTIMER_BASE + 0x10c)
#define SCTIMER_CAP3_H		REGISTER_16(SCTIMER_BASE + 0x10e)
#define SCTIMER_CAP4		REGISTER_32(SCTIMER_BASE + 0x110)
#define SCTIMER_CAP4_L		REGISTER_16(SCTIMER_BASE + 0x110)
#define SCTIMER_CAP4_H		REGISTER_16(SCTIMER_BASE + 0x112)
#define SCTIMER_CAP5		REGISTER_32(SCTIMER_BASE + 0x114)
#define SCTIMER_CAP5_L		REGISTER_16(SCTIMER_BASE + 0x114)
#define SCTIMER_CAP5_H		REGISTER_16(SCTIMER_BASE + 0x116)
#define SCTIMER_CAP6		REGISTER_32(SCTIMER_BASE + 0x118)
#define SCTIMER_CAP6_L		REGISTER_16(SCTIMER_BASE + 0x118)
#define SCTIMER_CAP6_H		REGISTER_16(SCTIMER_BASE + 0x11a)
#define SCTIMER_CAP7		REGISTER_32(SCTIMER_BASE + 0x11c)
#define SCTIMER_CAP7_L		REGISTER_16(SCTIMER_BASE + 0x11c)
#define SCTIMER_CAP7_H		REGISTER_16(SCTIMER_BASE + 0x11e)
#define SCTIMER_MATCHREL0		REGISTER_32(SCTIMER_BASE + 0x200)
#define SCTIMER_MATCHREL0_L		REGISTER_16(SCTIMER_BASE + 0x200)
#define SCTIMER_MATCHREL0_H		REGISTER_16(SCTIMER_BASE + 0x202)
#define SCTIMER_MATCHREL1		REGISTER_32(SCTIMER_BASE + 0x204)
#define SCTIMER_MATCHREL1_L		REGISTER_16(SCTIMER_BASE + 0x204)
#define SCTIMER_MATCHREL1_H		REGISTER_16(SCTIMER_BASE + 0x206)
#define SCTIMER_MATCHREL2		REGISTER_32(SCTIMER_BASE + 0x208)
#define SCTIMER_MATCHREL2_L		REGISTER_16(SCTIMER_BASE + 0x208)
#define SCTIMER_MATCHREL2_H		REGISTER_16(SCTIMER_BASE + 0x20a)
#define SCTIMER_MATCHREL3		REGISTER_32(SCTIMER_BASE + 0x20c)
#define SCTIMER_MATCHREL3_L		REGISTER_16(SCTIMER_BASE + 0x20c)
#define SCTIMER_MATCHREL3_H		REGISTER_16(SCTIMER_BASE + 0x20e)
#define SCTIMER_MATCHREL4		REGISTER_32(SCTIMER_BASE + 0x210)
#define SCTIMER_MATCHREL4_L		REGISTER_16(SCTIMER_BASE + 0x210)
#define SCTIMER_MATCHREL4_H		REGISTER_16(SCTIMER_BASE + 0x212)
#define SCTIMER_MATCHREL5		REGISTER_32(SCTIMER_BASE + 0x214)
#define SCTIMER_MATCHREL5_L		REGISTER_16(SCTIMER_BASE + 0x214)
#define SCTIMER_MATCHREL5_H		REGISTER_16(SCTIMER_BASE + 0x216)
#define SCTIMER_MATCHREL6		REGISTER_32(SCTIMER_BASE + 0x218)
#define SCTIMER_MATCHREL6_L		REGISTER_16(SCTIMER_BASE + 0x218)
#define SCTIMER_MATCHREL6_H		REGISTER_16(SCTIMER_BASE + 0x21a)
#define SCTIMER_MATCHREL7		REGISTER_32(SCTIMER_BASE + 0x21c)
#define SCTIMER_MATCHREL7_L		REGISTER_16(SCTIMER_BASE + 0x21c)
#define SCTIMER_MATCHREL7_H		REGISTER_16(SCTIMER_BASE + 0x21e)
#define SCTIMER_CAPCTRL0		REGISTER_32(SCTIMER_BASE + 0x200)
#define SCTIMER_CAPCTRL0_L		REGISTER_16(SCTIMER_BASE + 0x200)
#define SCTIMER_CAPCTRL0_H		REGISTER_16(SCTIMER_BASE + 0x202)
#define SCTIMER_CAPCTRL1		REGISTER_32(SCTIMER_BASE + 0x204)
#define SCTIMER_CAPCTRL1_L		REGISTER_16(SCTIMER_BASE + 0x204)
#define SCTIMER_CAPCTRL1_H		REGISTER_16(SCTIMER_BASE + 0x206)
#define SCTIMER_CAPCTRL2		REGISTER_32(SCTIMER_BASE + 0x208)
#define SCTIMER_CAPCTRL2_L		REGISTER_16(SCTIMER_BASE + 0x208)
#define SCTIMER_CAPCTRL2_H		REGISTER_16(SCTIMER_BASE + 0x20a)
#define SCTIMER_CAPCTRL3		REGISTER_32(SCTIMER_BASE + 0x20c)
#define SCTIMER_CAPCTRL3_L		REGISTER_16(SCTIMER_BASE + 0x20c)
#define SCTIMER_CAPCTRL3_H		REGISTER_16(SCTIMER_BASE + 0x20e)
#define SCTIMER_CAPCTRL4		REGISTER_32(SCTIMER_BASE + 0x210)
#define SCTIMER_CAPCTRL4_L		REGISTER_16(SCTIMER_BASE + 0x210)
#define SCTIMER_CAPCTRL4_H		REGISTER_16(SCTIMER_BASE + 0x212)
#define SCTIMER_CAPCTRL5		REGISTER_32(SCTIMER_BASE + 0x214)
#define SCTIMER_CAPCTRL5_L		REGISTER_16(SCTIMER_BASE + 0x214)
#define SCTIMER_CAPCTRL5_H		REGISTER_16(SCTIMER_BASE + 0x216)
#define SCTIMER_CAPCTRL6		REGISTER_32(SCTIMER_BASE + 0x218)
#define SCTIMER_CAPCTRL6_L		REGISTER_16(SCTIMER_BASE + 0x218)
#define SCTIMER_CAPCTRL6_H		REGISTER_16(SCTIMER_BASE + 0x21a)
#define SCTIMER_CAPCTRL7		REGISTER_32(SCTIMER_BASE + 0x21c)
#define SCTIMER_CAPCTRL7_L		REGISTER_16(SCTIMER_BASE + 0x21c)
#define SCTIMER_CAPCTRL7_H		REGISTER_16(SCTIMER_BASE + 0x21e)	
#define SCTIMER_EV0_STATE		REGISTER_32(SCTIMER_BASE + 0x300)	
#define SCTIMER_EV0_CTRL		REGISTER_32(SCTIMER_BASE + 0x304)	
#define SCTIMER_EV1_STATE		REGISTER_32(SCTIMER_BASE + 0x308)	
#define SCTIMER_EV1_CTRL		REGISTER_32(SCTIMER_BASE + 0x30c)	
#define SCTIMER_EV2_STATE		REGISTER_32(SCTIMER_BASE + 0x310)	
#define SCTIMER_EV2_CTRL		REGISTER_32(SCTIMER_BASE + 0x314)	
#define SCTIMER_EV3_STATE		REGISTER_32(SCTIMER_BASE + 0x318)	
#define SCTIMER_EV3_CTRL		REGISTER_32(SCTIMER_BASE + 0x31c)	
#define SCTIMER_EV4_STATE		REGISTER_32(SCTIMER_BASE + 0x320)	
#define SCTIMER_EV4_CTRL		REGISTER_32(SCTIMER_BASE + 0x324)	
#define SCTIMER_EV5_STATE		REGISTER_32(SCTIMER_BASE + 0x328)	
#define SCTIMER_EV5_CTRL		REGISTER_32(SCTIMER_BASE + 0x32c)	
#define SCTIMER_EV6_STATE		REGISTER_32(SCTIMER_BASE + 0x330)	
#define SCTIMER_EV6_CTRL		REGISTER_32(SCTIMER_BASE + 0x334)	
#define SCTIMER_EV7_STATE		REGISTER_32(SCTIMER_BASE + 0x338)	
#define SCTIMER_EV7_CTRL		REGISTER_32(SCTIMER_BASE + 0x33c)	
#define SCTIMER_OUT0_SET		REGISTER_32(SCTIMER_BASE + 0x500)
#define SCTIMER_OUT0_CLR		REGISTER_32(SCTIMER_BASE + 0x504)
#define SCTIMER_OUT1_SET		REGISTER_32(SCTIMER_BASE + 0x508)
#define SCTIMER_OUT1_CLR		REGISTER_32(SCTIMER_BASE + 0x50c)
#define SCTIMER_OUT2_SET		REGISTER_32(SCTIMER_BASE + 0x510)
#define SCTIMER_OUT2_CLR		REGISTER_32(SCTIMER_BASE + 0x514)
#define SCTIMER_OUT3_SET		REGISTER_32(SCTIMER_BASE + 0x518)
#define SCTIMER_OUT3_CLR		REGISTER_32(SCTIMER_BASE + 0x51c)
#define SCTIMER_OUT4_SET		REGISTER_32(SCTIMER_BASE + 0x520)
#define SCTIMER_OUT4_CLR		REGISTER_32(SCTIMER_BASE + 0x524)
#define SCTIMER_OUT5_SET		REGISTER_32(SCTIMER_BASE + 0x528)
#define SCTIMER_OUT5_CLR		REGISTER_32(SCTIMER_BASE + 0x52c)

// GPIO_PORT
// Symbols defined according to pin naming
#define PIO0_0				REGISTER_8(GPIO_BASE + 0)
#define PIO0_1				REGISTER_8(GPIO_BASE + 1)
#define PIO0_2				REGISTER_8(GPIO_BASE + 2)
#define PIO0_3				REGISTER_8(GPIO_BASE + 3)
#define PIO0_4				REGISTER_8(GPIO_BASE + 4)
#define PIO0_5				REGISTER_8(GPIO_BASE + 5)
#define PIO0_6				REGISTER_8(GPIO_BASE + 6)
#define PIO0_7				REGISTER_8(GPIO_BASE + 7)
#define PIO0_8				REGISTER_8(GPIO_BASE + 8)
#define PIO0_9				REGISTER_8(GPIO_BASE + 9)
#define PIO0_10				REGISTER_8(GPIO_BASE + 10)
#define PIO0_11				REGISTER_8(GPIO_BASE + 11)
#define PIO0_12				REGISTER_8(GPIO_BASE + 12)
#define PIO0_13				REGISTER_8(GPIO_BASE + 13)
#define PIO0_14				REGISTER_8(GPIO_BASE + 14)
#define PIO0_15				REGISTER_8(GPIO_BASE + 15)
#define PIO0_16				REGISTER_8(GPIO_BASE + 16)
#define PIO0_17				REGISTER_8(GPIO_BASE + 17)
#define PIO0_23				REGISTER_8(GPIO_BASE + 23)

// byte register access
#define GPIO_B0				REGISTER_8(GPIO_BASE + 0)
#define GPIO_B1				REGISTER_8(GPIO_BASE + 1)
#define GPIO_B2				REGISTER_8(GPIO_BASE + 2)
#define GPIO_B3				REGISTER_8(GPIO_BASE + 3)
#define GPIO_B4				REGISTER_8(GPIO_BASE + 4)
#define GPIO_B5				REGISTER_8(GPIO_BASE + 5)
#define GPIO_B6				REGISTER_8(GPIO_BASE + 6)
#define GPIO_B7				REGISTER_8(GPIO_BASE + 7)
#define GPIO_B8				REGISTER_8(GPIO_BASE + 8)
#define GPIO_B9				REGISTER_8(GPIO_BASE + 9)
#define GPIO_B10			REGISTER_8(GPIO_BASE + 10)
#define GPIO_B11			REGISTER_8(GPIO_BASE + 11)
#define GPIO_B12			REGISTER_8(GPIO_BASE + 12)
#define GPIO_B13			REGISTER_8(GPIO_BASE + 13)
#define GPIO_B14			REGISTER_8(GPIO_BASE + 14)
#define GPIO_B15			REGISTER_8(GPIO_BASE + 15)
#define GPIO_B16			REGISTER_8(GPIO_BASE + 16)
#define GPIO_B17			REGISTER_8(GPIO_BASE + 17)
#define GPIO_B18			REGISTER_8(GPIO_BASE + 18)
#define GPIO_B19			REGISTER_8(GPIO_BASE + 19)
#define GPIO_B20			REGISTER_8(GPIO_BASE + 20)
#define GPIO_B21			REGISTER_8(GPIO_BASE + 21)
#define GPIO_B22			REGISTER_8(GPIO_BASE + 22)
#define GPIO_B23			REGISTER_8(GPIO_BASE + 23)
#define GPIO_B24			REGISTER_8(GPIO_BASE + 24)
#define GPIO_B25			REGISTER_8(GPIO_BASE + 25)
#define GPIO_B26			REGISTER_8(GPIO_BASE + 26)
#define GPIO_B27			REGISTER_8(GPIO_BASE + 27)
#define GPIO_B28			REGISTER_8(GPIO_BASE + 28)


#define GPIO_W0				REGISTER_32(GPIO_BASE + 0x1000)
#define GPIO_W1				REGISTER_32(GPIO_BASE + 0x1004)
#define GPIO_W2				REGISTER_32(GPIO_BASE + 0x1008)
#define GPIO_W3				REGISTER_32(GPIO_BASE + 0x100c)
#define GPIO_W4				REGISTER_32(GPIO_BASE + 0x1010)
#define GPIO_W5				REGISTER_32(GPIO_BASE + 0x1014)
#define GPIO_W6				REGISTER_32(GPIO_BASE + 0x1018)
#define GPIO_W7				REGISTER_32(GPIO_BASE + 0x101c)
#define GPIO_W8				REGISTER_32(GPIO_BASE + 0x1020)
#define GPIO_W9				REGISTER_32(GPIO_BASE + 0x1024)
#define GPIO_W10			REGISTER_32(GPIO_BASE + 0x1028)
#define GPIO_W11			REGISTER_32(GPIO_BASE + 0x102c)
#define GPIO_W12			REGISTER_32(GPIO_BASE + 0x1030)
#define GPIO_W13			REGISTER_32(GPIO_BASE + 0x1034)
#define GPIO_W14			REGISTER_32(GPIO_BASE + 0x1038)
#define GPIO_W15			REGISTER_32(GPIO_BASE + 0x103c)
#define GPIO_W16			REGISTER_32(GPIO_BASE + 0x1040)
#define GPIO_W17			REGISTER_32(GPIO_BASE + 0x1044)
#define GPIO_W18			REGISTER_32(GPIO_BASE + 0x1048)
#define GPIO_W19			REGISTER_32(GPIO_BASE + 0x104c)
#define GPIO_W20			REGISTER_32(GPIO_BASE + 0x1050)
#define GPIO_W21			REGISTER_32(GPIO_BASE + 0x1054)
#define GPIO_W22			REGISTER_32(GPIO_BASE + 0x1058)
#define GPIO_W23			REGISTER_32(GPIO_BASE + 0x105c)
#define GPIO_W24			REGISTER_32(GPIO_BASE + 0x1060)
#define GPIO_W25			REGISTER_32(GPIO_BASE + 0x1064)
#define GPIO_W26			REGISTER_32(GPIO_BASE + 0x1068)
#define GPIO_W27			REGISTER_32(GPIO_BASE + 0x106c)
#define GPIO_W28			REGISTER_32(GPIO_BASE + 0x1070)

#define GPIO_DIR0			REGISTER_32(GPIO_BASE + 0x2000)
#define GPIO_MASK0			REGISTER_32(GPIO_BASE + 0x2080)
#define GPIO_PIN0			REGISTER_32(GPIO_BASE + 0x2100)
#define GPIO_MPIN0			REGISTER_32(GPIO_BASE + 0x2180)
#define GPIO_SET0			REGISTER_32(GPIO_BASE + 0x2200)
#define GPIO_CLR0			REGISTER_32(GPIO_BASE + 0x2280)
#define GPIO_NOT0			REGISTER_32(GPIO_BASE + 0x2300)

#define GPIO_DIRSET0		REGISTER_32(GPIO_BASE + 0x2380)
#define GPIO_DIRCLR0		REGISTER_32(GPIO_BASE + 0x2400)
#define GPIO_DIRNOT0		REGISTER_32(GPIO_BASE + 0x2480)


// Switch Matrix
#define SWM_PINASSIGN0		REGISTER_32(SWITCH_MATRIX_BASE + 0x0)
#define SWM_PINASSIGN1		REGISTER_32(SWITCH_MATRIX_BASE + 0x4)
#define SWM_PINASSIGN2		REGISTER_32(SWITCH_MATRIX_BASE + 0x8)
#define SWM_PINASSIGN3		REGISTER_32(SWITCH_MATRIX_BASE + 0xc)
#define SWM_PINASSIGN4		REGISTER_32(SWITCH_MATRIX_BASE + 0x10)
#define SWM_PINASSIGN5		REGISTER_32(SWITCH_MATRIX_BASE + 0x14)
#define SWM_PINASSIGN6		REGISTER_32(SWITCH_MATRIX_BASE + 0x18)
#define SWM_PINASSIGN7		REGISTER_32(SWITCH_MATRIX_BASE + 0x1c)
#define SWM_PINASSIGN8		REGISTER_32(SWITCH_MATRIX_BASE + 0x20)
#define SWM_PINASSIGN9		REGISTER_32(SWITCH_MATRIX_BASE + 0x24)
#define SWM_PINASSIGN10		REGISTER_32(SWITCH_MATRIX_BASE + 0x28)
#define SWM_PINASSIGN11		REGISTER_32(SWITCH_MATRIX_BASE + 0x2C)
#define SWM_PINENABLE0		REGISTER_32(SWITCH_MATRIX_BASE + 0x1c0)

// USART0
#define USART0_CFG			REGISTER_32(USART0_BASE + 0x00)
#define USART0_CTL			REGISTER_32(USART0_BASE + 0x04)
#define USART0_STAT			REGISTER_32(USART0_BASE + 0x08)
#define USART0_INTENSET		REGISTER_32(USART0_BASE + 0x0c)
#define USART0_INTENCLR		REGISTER_32(USART0_BASE + 0x10)
#define USART0_RXDAT		REGISTER_32(USART0_BASE + 0x14)
#define USART0_RXDATSTAT	REGISTER_32(USART0_BASE + 0x18)
#define USART0_TXDAT		REGISTER_32(USART0_BASE + 0x1c)
#define USART0_BRG			REGISTER_32(USART0_BASE + 0x20)
#define USART0_INTSTAT		REGISTER_32(USART0_BASE + 0x24)
#define USART0_OSR			REGISTER_32(USART0_BASE + 0x28)
#define USART0_ADDR			REGISTER_32(USART0_BASE + 0x2c)


// USART1
#define USART1_CFG			REGISTER_32(USART1_BASE + 0x00)
#define USART1_CTL			REGISTER_32(USART1_BASE + 0x04)
#define USART1_STAT			REGISTER_32(USART1_BASE + 0x08)
#define USART1_INTENSET		REGISTER_32(USART1_BASE + 0x0c)
#define USART1_INTENCLR		REGISTER_32(USART1_BASE + 0x10)
#define USART1_RXDAT		REGISTER_32(USART1_BASE + 0x14)
#define USART1_RXDATSTAT	REGISTER_32(USART1_BASE + 0x18)
#define USART1_TXDAT		REGISTER_32(USART1_BASE + 0x1c)
#define USART1_BRG			REGISTER_32(USART1_BASE + 0x20)
#define USART1_INTSTAT		REGISTER_32(USART1_BASE + 0x24)
#define USART1_OSR			REGISTER_32(USART1_BASE + 0x28)
#define USART1_ADDR			REGISTER_32(USART1_BASE + 0x2c)


// USART2
#define USART2_CFG			REGISTER_32(USART2_BASE + 0x00)
#define USART2_CTL			REGISTER_32(USART2_BASE + 0x04)
#define USART2_STAT			REGISTER_32(USART2_BASE + 0x08)
#define USART2_INTENSET		REGISTER_32(USART2_BASE + 0x0c)
#define USART2_INTENCLR		REGISTER_32(USART2_BASE + 0x10)
#define USART2_RXDAT		REGISTER_32(USART2_BASE + 0x14)
#define USART2_RXDATSTAT	REGISTER_32(USART2_BASE + 0x18)
#define USART2_TXDAT		REGISTER_32(USART2_BASE + 0x1c)
#define USART2_BRG			REGISTER_32(USART2_BASE + 0x20)
#define USART2_INTSTAT		REGISTER_32(USART2_BASE + 0x24)
#define USART2_OSR			REGISTER_32(USART2_BASE + 0x28)
#define USART2_ADDR			REGISTER_32(USART2_BASE + 0x2c)


// SYSCON
#define SYSCON_MAP			REGISTER_32(SYSCON_BASE + 0x00)
#define SYSCON_PRESETCTRL	REGISTER_32(SYSCON_BASE + 0x04)
#define SYSCON_SYSPLLCTRL	REGISTER_32(SYSCON_BASE + 0x08)
#define SYSCON_SYSPLLSTAT	REGISTER_32(SYSCON_BASE + 0x0c)
#define SYSCON_SYSOSCCTRL	REGISTER_32(SYSCON_BASE + 0x20)
#define SYSCON_WDTOSCCTRL	REGISTER_32(SYSCON_BASE + 0x24)
#define SYSCON_IRCCTRL		REGISTER_32(SYSCON_BASE + 0x28)
#define SYSCON_SYSRSTSTAT	REGISTER_32(SYSCON_BASE + 0x30)
#define SYSCON_SYSPLLCLKSEL	REGISTER_32(SYSCON_BASE + 0x40)
#define SYSCON_SYSPLLCLKUEN	REGISTER_32(SYSCON_BASE + 0x44)
#define SYSCON_MAINCLKSEL 	REGISTER_32(SYSCON_BASE + 0x70)
#define SYSCON_MAINCLKUEN 	REGISTER_32(SYSCON_BASE + 0x74)
#define SYSCON_SYSAHBCLKDIV	REGISTER_32(SYSCON_BASE + 0x78)
#define SYSCON_SYSAHBCLKCTRL	REGISTER_32(SYSCON_BASE + 0x80)
#define SYSCON_UARTCLKDIV	REGISTER_32(SYSCON_BASE + 0x94)
#define SYSCON_CLKOUTSEL	REGISTER_32(SYSCON_BASE + 0xe0)
#define SYSCON_CLKOUTUEN	REGISTER_32(SYSCON_BASE + 0xe4)
#define SYSCON_CLKOUTDIV	REGISTER_32(SYSCON_BASE + 0xe8)
#define SYSCON_UARTFRGDIV	REGISTER_32(SYSCON_BASE + 0xf0)
#define SYSCON_UARTFRGMULT	REGISTER_32(SYSCON_BASE + 0xf4)
#define SYSCON_EXTTRACECMD	REGISTER_32(SYSCON_BASE + 0xfc)
#define SYSCON_PIOPORCAP0	REGISTER_32(SYSCON_BASE + 0x100)
#define SYSCON_IOCONCLKDIV6	REGISTER_32(SYSCON_BASE + 0x134)
#define SYSCON_IOCONCLKDIV5	REGISTER_32(SYSCON_BASE + 0x138)
#define SYSCON_IOCONCLKDIV4	REGISTER_32(SYSCON_BASE + 0x13c)
#define SYSCON_IOCONCLKDIV3	REGISTER_32(SYSCON_BASE + 0x140)
#define SYSCON_IOCONCLKDIV2	REGISTER_32(SYSCON_BASE + 0x144)
#define SYSCON_IOCONCLKDIV1	REGISTER_32(SYSCON_BASE + 0x148)
#define SYSCON_IOCONCLKDIV0	REGISTER_32(SYSCON_BASE + 0x14c)
#define SYSCON_BODCTRL		REGISTER_32(SYSCON_BASE + 0x150)
#define SYSCON_SYSTCKCAL	REGISTER_32(SYSCON_BASE + 0x154)
#define SYSCON_IRQLATENCY	REGISTER_32(SYSCON_BASE + 0x170)
#define SYSCON_NMISRC		REGISTER_32(SYSCON_BASE + 0x174)
#define SYSCON_PINTSEL0		REGISTER_32(SYSCON_BASE + 0x178)
#define SYSCON_PINTSEL1		REGISTER_32(SYSCON_BASE + 0x17c)
#define SYSCON_PINTSEL2		REGISTER_32(SYSCON_BASE + 0x180)
#define SYSCON_PINTSEL3		REGISTER_32(SYSCON_BASE + 0x184)
#define SYSCON_PINTSEL4		REGISTER_32(SYSCON_BASE + 0x188)
#define SYSCON_PINTSEL5		REGISTER_32(SYSCON_BASE + 0x18c)
#define SYSCON_PINTSEL6		REGISTER_32(SYSCON_BASE + 0x190)
#define SYSCON_PINTSEL7		REGISTER_32(SYSCON_BASE + 0x194)
#define SYSCON_STARTERP0	REGISTER_32(SYSCON_BASE + 0x204)
#define SYSCON_STARTERP1	REGISTER_32(SYSCON_BASE + 0x214)
#define SYSCON_PDSLEEPCFG	REGISTER_32(SYSCON_BASE + 0x230)
#define SYSCON_PDAWAKECFG	REGISTER_32(SYSCON_BASE + 0x234)
#define SYSCON_PDRUNCFG		REGISTER_32(SYSCON_BASE + 0x238)
#define SYSCON_DEVICE_ID	REGISTER_32(SYSCON_BASE + 0x3f8)


// NVIC 
#define NVIC_ISER0			REGISTER_32(SYS_BASE + 0x100)
#define NVIC_ICER0			REGISTER_32(SYS_BASE + 0x180)
#define NVIC_ISPR0			REGISTER_32(SYS_BASE + 0x200)
#define NVIC_ICPR0			REGISTER_32(SYS_BASE + 0x280)
#define NVIC_IABR0			REGISTER_32(SYS_BASE + 0x300)
#define NVIC_IPR0			REGISTER_32(SYS_BASE + 0x400)
#define NVIC_IPR1			REGISTER_32(SYS_BASE + 0x404)
#define NVIC_IPR2			REGISTER_32(SYS_BASE + 0x408)
#define NVIC_IPR3			REGISTER_32(SYS_BASE + 0x40c)
#define NVIC_IPR6			REGISTER_32(SYS_BASE + 0x418)
#define NVIC_IPR7			REGISTER_32(SYS_BASE + 0x41c)


// STK
#define SYST_CSR	REGISTER_32(SYS_BASE + 0x10)
#define SYST_RVR	REGISTER_32(SYS_BASE + 0x14)
#define SYST_CVR	REGISTER_32(SYS_BASE + 0x18)
#define SYST_CALIB	REGISTER_32(SYS_BASE + 0x1c)

// ADC
#define ADC_CTRL		REGISTER_32(ADC_BASE + 0x000)
#define ADC_SEQA_CTRL	REGISTER_32(ADC_BASE + 0x008)
#define ADC_SEQB_CTRL	REGISTER_32(ADC_BASE + 0x00c)
#define ADC_SEQA_GDAT	REGISTER_32(ADC_BASE + 0x010)
#define ADC_SEQB_GDAT	REGISTER_32(ADC_BASE + 0x014)
#define ADC_DAT0		REGISTER_32(ADC_BASE + 0x020)
#define ADC_DAT1		REGISTER_32(ADC_BASE + 0x024)
#define ADC_DAT2		REGISTER_32(ADC_BASE + 0x028)
#define ADC_DAT3		REGISTER_32(ADC_BASE + 0x02c)
#define ADC_DAT4		REGISTER_32(ADC_BASE + 0x030)
#define ADC_DAT5		REGISTER_32(ADC_BASE + 0x034)
#define ADC_DAT6		REGISTER_32(ADC_BASE + 0x038)
#define ADC_DAT7		REGISTER_32(ADC_BASE + 0x03c)
#define ADC_DAT8		REGISTER_32(ADC_BASE + 0x040)
#define ADC_DAT9		REGISTER_32(ADC_BASE + 0x044)
#define ADC_DAT10		REGISTER_32(ADC_BASE + 0x048)
#define ADC_DAT11		REGISTER_32(ADC_BASE + 0x04c)
#define ADC_THR0_LOW	REGISTER_32(ADC_BASE + 0x050)
#define ADC_THR1_LOW	REGISTER_32(ADC_BASE + 0x054)
#define ADC_THR0_HIGH	REGISTER_32(ADC_BASE + 0x058)
#define ADC_THR1_HIGH	REGISTER_32(ADC_BASE + 0x05c)
#define ADC_CHAN_THRSEL	REGISTER_32(ADC_BASE + 0x060)
#define ADC_INTEN		REGISTER_32(ADC_BASE + 0x064)
#define ADC_FLAGS		REGISTER_32(ADC_BASE + 0x068)
#define ADC_TRM			REGISTER_32(ADC_BASE + 0x06c)

// PMU 
#define PMU_PCON		REGISTER_32(PMU_BASE + 0x000)
#define PMU_GPREG0		REGISTER_32(PMU_BASE + 0x004)
#define PMU_GPREG1		REGISTER_32(PMU_BASE + 0x008)
#define PMU_GPREG2		REGISTER_32(PMU_BASE + 0x00c)
#define PMU_GPREG3		REGISTER_32(PMU_BASE + 0x010)
#define PMU_DPDCTRL		REGISTER_32(PMU_BASE + 0x014)

// ANLG_COMP
#define ANLG_COMP_CTRL	REGISTER_32(ANLG_COMP + 0x000)
#define ANLG_COMP_LAD	REGISTER_32(ANLG_COMP + 0x004)

// DMA Input trigger
#define DMA_ITRIG_INMUX0	REGISTER_32(DMA_ITRIG_BASE + 0x000)
#define DMA_ITRIG_INMUX1	REGISTER_32(DMA_ITRIG_BASE + 0x004)
#define DMA_ITRIG_INMUX2	REGISTER_32(DMA_ITRIG_BASE + 0x008)
#define DMA_ITRIG_INMUX3	REGISTER_32(DMA_ITRIG_BASE + 0x00c)
#define DMA_ITRIG_INMUX4	REGISTER_32(DMA_ITRIG_BASE + 0x010)
#define DMA_ITRIG_INMUX5	REGISTER_32(DMA_ITRIG_BASE + 0x014)
#define DMA_ITRIG_INMUX6	REGISTER_32(DMA_ITRIG_BASE + 0x018)
#define DMA_ITRIG_INMUX7	REGISTER_32(DMA_ITRIG_BASE + 0x01c)
#define DMA_ITRIG_INMUX8	REGISTER_32(DMA_ITRIG_BASE + 0x020)
#define DMA_ITRIG_INMUX9	REGISTER_32(DMA_ITRIG_BASE + 0x024)
#define DMA_ITRIG_INMUX10	REGISTER_32(DMA_ITRIG_BASE + 0x028)
#define DMA_ITRIG_INMUX11	REGISTER_32(DMA_ITRIG_BASE + 0x02c)
#define DMA_ITRIG_INMUX12	REGISTER_32(DMA_ITRIG_BASE + 0x030)
#define DMA_ITRIG_INMUX13	REGISTER_32(DMA_ITRIG_BASE + 0x034)
#define DMA_ITRIG_INMUX14	REGISTER_32(DMA_ITRIG_BASE + 0x038)
#define DMA_ITRIG_INMUX15	REGISTER_32(DMA_ITRIG_BASE + 0x03c)
#define DMA_ITRIG_INMUX16	REGISTER_32(DMA_ITRIG_BASE + 0x040)
#define DMA_ITRIG_INMUX17	REGISTER_32(DMA_ITRIG_BASE + 0x044)

// DMA Input multiplexing
#define DMA_INMUX_INMUX0	REGISTER_32(DMA_INMUX_BASE + 0x000)
#define DMA_INMUX_INMUX1	REGISTER_32(DMA_INMUX_BASE + 0x004)
// slightly violating naming convention here.
#define DMA_SCT0_INMUX0		REGISTER_32(DMA_INMUX_BASE + 0x020)
#define DMA_SCT0_INMUX1		REGISTER_32(DMA_INMUX_BASE + 0x024)
#define DMA_SCT0_INMUX2		REGISTER_32(DMA_INMUX_BASE + 0x028)
#define DMA_SCT0_INMUX3		REGISTER_32(DMA_INMUX_BASE + 0x02c)

// DMA
#define DMA_CTRL			REGISTER_32(DMA_BASE + 0x000)
#define DMA_INTSTAT			REGISTER_32(DMA_BASE + 0x004)
#define DMA_SRAMBASE		REGISTER_32(DMA_BASE + 0x008)
#define DMA_ENABLESET0		REGISTER_32(DMA_BASE + 0x020)
#define DMA_ENABLECLR0		REGISTER_32(DMA_BASE + 0x028)
#define DMA_ACTIVE0			REGISTER_32(DMA_BASE + 0x030)
#define DMA_BUSY0			REGISTER_32(DMA_BASE + 0x038)
#define DMA_ERRINT0			REGISTER_32(DMA_BASE + 0x040)
#define DMA_INTSET0			REGISTER_32(DMA_BASE + 0x048)
#define DMA_CLRSET0			REGISTER_32(DMA_BASE + 0x050)
#define DMA_INTA0			REGISTER_32(DMA_BASE + 0x058)
#define DMA_INTB0			REGISTER_32(DMA_BASE + 0x060)
#define DMA_SETVALID0		REGISTER_32(DMA_BASE + 0x068)
#define DMA_SETTRIG0		REGISTER_32(DMA_BASE + 0x070)
#define DMA_ABORT0			REGISTER_32(DMA_BASE + 0x078)

#define DMA_CFG0			REGISTER_32(DMA_BASE + 0x400)
#define DMA_CTLSTAT0		REGISTER_32(DMA_BASE + 0x404)
#define DMA_XFERCFG0		REGISTER_32(DMA_BASE + 0x408)
#define DMA_CFG1			REGISTER_32(DMA_BASE + 0x410)
#define DMA_CTLSTAT1		REGISTER_32(DMA_BASE + 0x414)
#define DMA_XFERCFG1		REGISTER_32(DMA_BASE + 0x418)
#define DMA_CFG2			REGISTER_32(DMA_BASE + 0x420)
#define DMA_CTLSTAT2		REGISTER_32(DMA_BASE + 0x424)
#define DMA_XFERCFG2		REGISTER_32(DMA_BASE + 0x428)
#define DMA_CFG3			REGISTER_32(DMA_BASE + 0x430)
#define DMA_CTLSTAT3		REGISTER_32(DMA_BASE + 0x434)
#define DMA_XFERCFG3		REGISTER_32(DMA_BASE + 0x438)
#define DMA_CFG4			REGISTER_32(DMA_BASE + 0x440)
#define DMA_CTLSTAT4		REGISTER_32(DMA_BASE + 0x444)
#define DMA_XFERCFG4		REGISTER_32(DMA_BASE + 0x448)
#define DMA_CFG5			REGISTER_32(DMA_BASE + 0x450)
#define DMA_CTLSTAT5		REGISTER_32(DMA_BASE + 0x454)
#define DMA_XFERCFG5		REGISTER_32(DMA_BASE + 0x458)
#define DMA_CFG6			REGISTER_32(DMA_BASE + 0x460)
#define DMA_CTLSTAT6		REGISTER_32(DMA_BASE + 0x464)
#define DMA_XFERCFG6		REGISTER_32(DMA_BASE + 0x468)
#define DMA_CFG7			REGISTER_32(DMA_BASE + 0x470)
#define DMA_CTLSTAT7		REGISTER_32(DMA_BASE + 0x474)
#define DMA_XFERCFG7		REGISTER_32(DMA_BASE + 0x478)
#define DMA_CFG8			REGISTER_32(DMA_BASE + 0x480)
#define DMA_CTLSTAT8		REGISTER_32(DMA_BASE + 0x484)
#define DMA_XFERCFG8		REGISTER_32(DMA_BASE + 0x488)
#define DMA_CFG9			REGISTER_32(DMA_BASE + 0x490)
#define DMA_CTLSTAT9		REGISTER_32(DMA_BASE + 0x494)
#define DMA_XFERCFG9		REGISTER_32(DMA_BASE + 0x498)
#define DMA_CFG10			REGISTER_32(DMA_BASE + 0x4a0)
#define DMA_CTLSTAT10		REGISTER_32(DMA_BASE + 0x4a4)
#define DMA_XFERCFG10		REGISTER_32(DMA_BASE + 0x4a8)
#define DMA_CFG11			REGISTER_32(DMA_BASE + 0x4b0)
#define DMA_CTLSTAT11		REGISTER_32(DMA_BASE + 0x4b4)
#define DMA_XFERCFG11		REGISTER_32(DMA_BASE + 0x4b8)
#define DMA_CFG12			REGISTER_32(DMA_BASE + 0x4c0)
#define DMA_CTLSTAT12		REGISTER_32(DMA_BASE + 0x4c4)
#define DMA_XFERCFG12		REGISTER_32(DMA_BASE + 0x4c8)
#define DMA_CFG13			REGISTER_32(DMA_BASE + 0x4d0)
#define DMA_CTLSTAT13		REGISTER_32(DMA_BASE + 0x4d4)
#define DMA_XFERCFG13		REGISTER_32(DMA_BASE + 0x4d8)
#define DMA_CFG14			REGISTER_32(DMA_BASE + 0x4e0)
#define DMA_CTLSTAT14		REGISTER_32(DMA_BASE + 0x4e4)
#define DMA_XFERCFG14		REGISTER_32(DMA_BASE + 0x4e8)
#define DMA_CFG15			REGISTER_32(DMA_BASE + 0x4f0)
#define DMA_CTLSTAT15		REGISTER_32(DMA_BASE + 0x4f4)
#define DMA_XFERCFG15		REGISTER_32(DMA_BASE + 0x4f8)
#define DMA_CFG16			REGISTER_32(DMA_BASE + 0x500)
#define DMA_CTLSTAT16		REGISTER_32(DMA_BASE + 0x504)
#define DMA_XFERCFG16		REGISTER_32(DMA_BASE + 0x508)
#define DMA_CFG17			REGISTER_32(DMA_BASE + 0x510)
#define DMA_CTLSTAT17		REGISTER_32(DMA_BASE + 0x514)
#define DMA_XFERCFG17		REGISTER_32(DMA_BASE + 0x518)

// Flash
#define FMC_FLASHCFG		REGISTER_32(FMC_BASE + 0x010)
#define FMC_FMSSTART		REGISTER_32(FMC_BASE + 0x020)
#define FMC_FMSSTOP			REGISTER_32(FMC_BASE + 0x024)
#define FMC_FMSW0			REGISTER_32(FMC_BASE + 0x02c)	


// IOCON
#define IOCON_PIO0_17		REGISTER_32(IOCON_BASE + 0x000)	
#define IOCON_PIO0_13		REGISTER_32(IOCON_BASE + 0x004)	
#define IOCON_PIO0_12		REGISTER_32(IOCON_BASE + 0x008)	
#define IOCON_PIO0_5		REGISTER_32(IOCON_BASE + 0x00c)	
#define IOCON_PIO0_4		REGISTER_32(IOCON_BASE + 0x010)
#define IOCON_PIO0_3		REGISTER_32(IOCON_BASE + 0x014)		
#define IOCON_PIO0_2		REGISTER_32(IOCON_BASE + 0x018)
#define IOCON_PIO0_11		REGISTER_32(IOCON_BASE + 0x01c)		
#define IOCON_PIO0_10		REGISTER_32(IOCON_BASE + 0x020)
#define IOCON_PIO0_16		REGISTER_32(IOCON_BASE + 0x024)				
#define IOCON_PIO0_15		REGISTER_32(IOCON_BASE + 0x028)
#define IOCON_PIO0_1		REGISTER_32(IOCON_BASE + 0x02c)
#define IOCON_PIO0_9		REGISTER_32(IOCON_BASE + 0x034)
#define IOCON_PIO0_8		REGISTER_32(IOCON_BASE + 0x038)
#define IOCON_PIO0_7		REGISTER_32(IOCON_BASE + 0x03c)
#define IOCON_PIO0_6		REGISTER_32(IOCON_BASE + 0x040)
#define IOCON_PIO0_0		REGISTER_32(IOCON_BASE + 0x044)
#define IOCON_PIO0_14		REGISTER_32(IOCON_BASE + 0x048)
#define IOCON_PIO0_28		REGISTER_32(IOCON_BASE + 0x050)
#define IOCON_PIO0_27		REGISTER_32(IOCON_BASE + 0x054)
#define IOCON_PIO0_26		REGISTER_32(IOCON_BASE + 0x058)
#define IOCON_PIO0_25		REGISTER_32(IOCON_BASE + 0x05c)
#define IOCON_PIO0_24		REGISTER_32(IOCON_BASE + 0x060)
#define IOCON_PIO0_23		REGISTER_32(IOCON_BASE + 0x064)
#define IOCON_PIO0_22		REGISTER_32(IOCON_BASE + 0x068)
#define IOCON_PIO0_21		REGISTER_32(IOCON_BASE + 0x06c)
#define IOCON_PIO0_20		REGISTER_32(IOCON_BASE + 0x070)
#define IOCON_PIO0_19		REGISTER_32(IOCON_BASE + 0x074)
#define IOCON_PIO0_18		REGISTER_32(IOCON_BASE + 0x078)

// I2C0

#define I2C0_CFG			REGISTER_32(I2C0_BASE + 0x000)
#define I2C0_STAT			REGISTER_32(I2C0_BASE + 0x004)
#define I2C0_INTENSET		REGISTER_32(I2C0_BASE + 0x008)
#define I2C0_INTENCLR		REGISTER_32(I2C0_BASE + 0x00c)
#define I2C0_TIMEOUT		REGISTER_32(I2C0_BASE + 0x010)
#define I2C0_CLKDIV			REGISTER_32(I2C0_BASE + 0x014)
#define I2C0_INTSTAT		REGISTER_32(I2C0_BASE + 0x018)
#define I2C0_MSTCTL			REGISTER_32(I2C0_BASE + 0x020)
#define I2C0_MSTTIME		REGISTER_32(I2C0_BASE + 0x024)
#define I2C0_MSTDAT			REGISTER_32(I2C0_BASE + 0x028)
#define I2C0_SLVCTL			REGISTER_32(I2C0_BASE + 0x040)
#define I2C0_SLVDAT			REGISTER_32(I2C0_BASE + 0x044)
#define I2C0_SLVADR0		REGISTER_32(I2C0_BASE + 0x048)
#define I2C0_SLVADR1		REGISTER_32(I2C0_BASE + 0x04c)
#define I2C0_SLVADR2		REGISTER_32(I2C0_BASE + 0x050)
#define I2C0_SLVADR3		REGISTER_32(I2C0_BASE + 0x054)
#define I2C0_SLVQUAL0		REGISTER_32(I2C0_BASE + 0x058)
#define I2C0_MONRXDAT		REGISTER_32(I2C0_BASE + 0x080)

// I2C1

#define I2C1_CFG			REGISTER_32(I2C1_BASE + 0x000)
#define I2C1_STAT			REGISTER_32(I2C1_BASE + 0x004)
#define I2C1_INTENSET		REGISTER_32(I2C1_BASE + 0x008)
#define I2C1_INTENCLR		REGISTER_32(I2C1_BASE + 0x00c)
#define I2C1_TIMEOUT		REGISTER_32(I2C1_BASE + 0x010)
#define I2C1_CLKDIV			REGISTER_32(I2C1_BASE + 0x014)
#define I2C1_INTSTAT		REGISTER_32(I2C1_BASE + 0x018)
#define I2C1_MSTCTL			REGISTER_32(I2C1_BASE + 0x020)
#define I2C1_MSTTIME		REGISTER_32(I2C1_BASE + 0x024)
#define I2C1_MSTDAT			REGISTER_32(I2C1_BASE + 0x028)
#define I2C1_SLVCTL			REGISTER_32(I2C1_BASE + 0x040)
#define I2C1_SLVDAT			REGISTER_32(I2C1_BASE + 0x044)
#define I2C1_SLVADR0		REGISTER_32(I2C1_BASE + 0x048)
#define I2C1_SLVADR1		REGISTER_32(I2C1_BASE + 0x04c)
#define I2C1_SLVADR2		REGISTER_32(I2C1_BASE + 0x050)
#define I2C1_SLVADR3		REGISTER_32(I2C1_BASE + 0x054)
#define I2C1_SLVQUAL0		REGISTER_32(I2C1_BASE + 0x058)
#define I2C1_MONRXDAT		REGISTER_32(I2C1_BASE + 0x080)

// I2C2

#define I2C2_CFG			REGISTER_32(I2C2_BASE + 0x000)
#define I2C2_STAT			REGISTER_32(I2C2_BASE + 0x004)
#define I2C2_INTENSET		REGISTER_32(I2C2_BASE + 0x008)
#define I2C2_INTENCLR		REGISTER_32(I2C2_BASE + 0x00c)
#define I2C2_TIMEOUT		REGISTER_32(I2C2_BASE + 0x010)
#define I2C2_CLKDIV			REGISTER_32(I2C2_BASE + 0x014)
#define I2C2_INTSTAT		REGISTER_32(I2C2_BASE + 0x018)
#define I2C2_MSTCTL			REGISTER_32(I2C2_BASE + 0x020)
#define I2C2_MSTTIME		REGISTER_32(I2C2_BASE + 0x024)
#define I2C2_MSTDAT			REGISTER_32(I2C2_BASE + 0x028)
#define I2C2_SLVCTL			REGISTER_32(I2C2_BASE + 0x040)
#define I2C2_SLVDAT			REGISTER_32(I2C2_BASE + 0x044)
#define I2C2_SLVADR0		REGISTER_32(I2C2_BASE + 0x048)
#define I2C2_SLVADR1		REGISTER_32(I2C2_BASE + 0x04c)
#define I2C2_SLVADR2		REGISTER_32(I2C2_BASE + 0x050)
#define I2C2_SLVADR3		REGISTER_32(I2C2_BASE + 0x054)
#define I2C2_SLVQUAL0		REGISTER_32(I2C2_BASE + 0x058)
#define I2C2_MONRXDAT		REGISTER_32(I2C2_BASE + 0x080)

// I2C3

#define I2C3_CFG			REGISTER_32(I2C3_BASE + 0x000)
#define I2C3_STAT			REGISTER_32(I2C3_BASE + 0x004)
#define I2C3_INTENSET		REGISTER_32(I2C3_BASE + 0x008)
#define I2C3_INTENCLR		REGISTER_32(I2C3_BASE + 0x00c)
#define I2C3_TIMEOUT		REGISTER_32(I2C3_BASE + 0x010)
#define I2C3_CLKDIV			REGISTER_32(I2C3_BASE + 0x014)
#define I2C3_INTSTAT		REGISTER_32(I2C3_BASE + 0x018)
#define I2C3_MSTCTL			REGISTER_32(I2C3_BASE + 0x020)
#define I2C3_MSTTIME		REGISTER_32(I2C3_BASE + 0x024)
#define I2C3_MSTDAT			REGISTER_32(I2C3_BASE + 0x028)
#define I2C3_SLVCTL			REGISTER_32(I2C3_BASE + 0x040)
#define I2C3_SLVDAT			REGISTER_32(I2C3_BASE + 0x044)
#define I2C3_SLVADR0		REGISTER_32(I2C3_BASE + 0x048)
#define I2C3_SLVADR1		REGISTER_32(I2C3_BASE + 0x04c)
#define I2C3_SLVADR2		REGISTER_32(I2C3_BASE + 0x050)
#define I2C3_SLVADR3		REGISTER_32(I2C3_BASE + 0x054)
#define I2C3_SLVQUAL0		REGISTER_32(I2C3_BASE + 0x058)
#define I2C3_MONRXDAT		REGISTER_32(I2C3_BASE + 0x080)


// SPI0
#define SPI0_CFG			REGISTER_32(SPI0_BASE + 0x000)
#define SPI0_DLY			REGISTER_32(SPI0_BASE + 0x004)
#define SPI0_STAT			REGISTER_32(SPI0_BASE + 0x008)
#define SPI0_INTENSET		REGISTER_32(SPI0_BASE + 0x00c)
#define SPI0_INTENCLR		REGISTER_32(SPI0_BASE + 0x010)
#define SPI0_RXDAT			REGISTER_32(SPI0_BASE + 0x014)
#define SPI0_TXDATCTL		REGISTER_32(SPI0_BASE + 0x018)
#define SPI0_TXDAT			REGISTER_32(SPI0_BASE + 0x01c)
#define SPI0_TXCTL			REGISTER_32(SPI0_BASE + 0x020)
#define SPI0_DIV			REGISTER_32(SPI0_BASE + 0x024)
#define SPI0_INSTAT			REGISTER_32(SPI0_BASE + 0x028)

// SPI1
#define SPI1_CFG			REGISTER_32(SPI1_BASE + 0x000)
#define SPI1_DLY			REGISTER_32(SPI1_BASE + 0x004)
#define SPI1_STAT			REGISTER_32(SPI1_BASE + 0x008)
#define SPI1_INTENSET		REGISTER_32(SPI1_BASE + 0x00c)
#define SPI1_INTENCLR		REGISTER_32(SPI1_BASE + 0x010)
#define SPI1_RXDAT			REGISTER_32(SPI1_BASE + 0x014)
#define SPI1_TXDATCTL		REGISTER_32(SPI1_BASE + 0x018)
#define SPI1_TXDAT			REGISTER_32(SPI1_BASE + 0x01c)
#define SPI1_TXCTL			REGISTER_32(SPI1_BASE + 0x020)
#define SPI1_DIV			REGISTER_32(SPI1_BASE + 0x024)
#define SPI1_INSTAT			REGISTER_32(SPI1_BASE + 0x028)

// Pin interrupts
#define PIN_INT_ISEL		REGISTER_32(PIN_INT_BASE + 0x000)
#define PIN_INT_IENR		REGISTER_32(PIN_INT_BASE + 0x004)
#define PIN_INT_SIENR		REGISTER_32(PIN_INT_BASE + 0x008)
#define PIN_INT_CIENR		REGISTER_32(PIN_INT_BASE + 0x00c)
#define PIN_INT_IENF		REGISTER_32(PIN_INT_BASE + 0x010)
#define PIN_INT_SIENF		REGISTER_32(PIN_INT_BASE + 0x014)
#define PIN_INT_CIENF		REGISTER_32(PIN_INT_BASE + 0x018)
#define PIN_INT_RISE		REGISTER_32(PIN_INT_BASE + 0x01c)
#define PIN_INT_FALL		REGISTER_32(PIN_INT_BASE + 0x020)
#define PIN_INT_IST			REGISTER_32(PIN_INT_BASE + 0x024)
#define PIN_INT_PMCTL		REGISTER_32(PIN_INT_BASE + 0x028)
#define PIN_INT_PMSRC		REGISTER_32(PIN_INT_BASE + 0x02c)
#define PIN_INT_PMCFG		REGISTER_32(PIN_INT_BASE + 0x030)

// CRC
#define CRC_MODE			REGISTER_32(CRC_BASE + 0x000)
#define CRC_SEED			REGISTER_32(CRC_BASE + 0x004)
#define CRC_SUM				REGISTER_32(CRC_BASE + 0x008)
#define CRC_WR_DATA			REGISTER_32(CRC_BASE + 0x008)


// WWDT
#define WWDT_MOD			REGISTER_32(WWDT_BASE + 0x000)
#define WWDT_TC				REGISTER_32(WWDT_BASE + 0x004)
#define WWDT_FEED			REGISTER_32(WWDT_BASE + 0x008)
#define WWDT_TV				REGISTER_32(WWDT_BASE + 0x00c)
#define WWDT_WARNINT		REGISTER_32(WWDT_BASE + 0x014)
#define WWDT_WINDOW			REGISTER_32(WWDT_BASE + 0x018)

// MRT
#define MRT_INTVAL0			REGISTER_32(MRT_BASE + 0x000)
#define MRT_TIMER0			REGISTER_32(MRT_BASE + 0x004)
#define MRT_CTRL0			REGISTER_32(MRT_BASE + 0x008)
#define MRT_STAT0			REGISTER_32(MRT_BASE + 0x00c)
#define MRT_INTVAL1			REGISTER_32(MRT_BASE + 0x010)
#define MRT_TIMER1			REGISTER_32(MRT_BASE + 0x014)
#define MRT_CTRL1			REGISTER_32(MRT_BASE + 0x018)
#define MRT_STAT1			REGISTER_32(MRT_BASE + 0x01c)
#define MRT_INTVAL2			REGISTER_32(MRT_BASE + 0x020)
#define MRT_TIMER2			REGISTER_32(MRT_BASE + 0x024)
#define MRT_CTRL2			REGISTER_32(MRT_BASE + 0x028)
#define MRT_STAT2			REGISTER_32(MRT_BASE + 0x02c)
#define MRT_INTVAL3			REGISTER_32(MRT_BASE + 0x030)
#define MRT_TIMER3			REGISTER_32(MRT_BASE + 0x034)
#define MRT_CTRL3			REGISTER_32(MRT_BASE + 0x038)
#define MRT_STAT3			REGISTER_32(MRT_BASE + 0x03c)
#define MRT_IDLE_CH			REGISTER_32(MRT_BASE + 0x0f4)
#define MRT_IRQ_FLAG		REGISTER_32(MRT_BASE + 0x0f8)

// WKT
#define WKT_CTRL			REGISTER_32(WKT_BASE + 0x000)
#define WKT_COUNT			REGISTER_32(WKT_BASE + 0x00c)

