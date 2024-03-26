#define VRX QFP32_MUX_P2_5
#define VRY QFP32_MUX_P2_2

void InitADC (void);
void InitPinADC (unsigned char portno, unsigned char pin_num);
unsigned int ADC_at_Pin(unsigned char pin);
unsigned int readVRX(void);
unsigned int readVRY(void);