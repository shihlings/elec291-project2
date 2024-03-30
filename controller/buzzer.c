#include <EFM8LB1.h>
#include "global.h"
#include "buzzer.h"

// sets buzzer frequency and turns it on
void setFreq (unsigned long int freq)
{
	TR2 = 0;
	TMR2RL=(-(SYSCLK/(2*freq))); // Initialize reload value
	TR2 = 1;
}
