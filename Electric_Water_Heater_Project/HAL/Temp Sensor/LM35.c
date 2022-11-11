
#include "LM35.h"

void LM35_init(u8 PORTID,u8 PINID)
{
	ADC_init(MODE, VREF, prescale);
}

u8 LM35_Read(u8 Channel)
{
	float temp = 0 ;
	temp = (float)ADC_ReadChannel(Channel);
	temp = (float)((5*temp)/1024)*100;
	return temp;
}
