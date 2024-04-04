#define VRX QFP32_MUX_P2_2
#define VRY QFP32_MUX_P2_5

//definition for reading battery percentage
#define BP QFP32_MUX_P3_0


void InitADC (void);
void InitPinADC (unsigned char portno, unsigned char pin_num);
unsigned int ADC_at_Pin(unsigned char pin);
