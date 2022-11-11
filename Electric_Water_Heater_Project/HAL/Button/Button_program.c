

#include "Button_interface.h"


/**************set pin to be output for PushButton*************/
void PB_init(u8 PORTID,u8 PINID,u8 mode)
{
	if (mode == PULL_UP)
	{
		DIO_setPinDir(PORTID, PINID, IN);
		DIO_setPinval(PORTID,PINID,HIGH);
	}
	else if (mode == PULL_DOWN)
	{
		DIO_setPinDir(PORTID, PINID, IN);
	}
	else
	{
		/*do nothing*/
	}
	
}


/**************check value on pin***************/
u8 PB_state(u8 PORTID,u8 PINID)
{
	return DIO_getPinval(PORTID,PINID);
}
