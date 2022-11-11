

#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_


#include "../../MCAL/DIO/DIO_interface.h"


#define PULL_UP 0
#define PULL_DOWN 1

/**************set pin to be output for PushButton*************/
void PB_init(u8 PORTID,u8 PINID,u8 mode);


/**************check value on pin***************/
u8 PB_state(u8 PORTID,u8 PINID);


#endif /* BUTTON_INTERFACE_H_ */
