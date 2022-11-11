

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_


#include "../../MCAL/DIO/DIO_interface.h"


/***********setPinDir to output**********/
void LED_init(u8 PORTID,u8 PINID);



/***********setPinval to high**********/
void LED_on(u8 PORTID,u8 PINID);


/***********setPinval to low**********/
void LED_off(u8 PORTID,u8 PINID);


/***************toggle led between high and low*****************/
void LED_toggle(u8 PORTID,u8 PINID);



#endif /* LED_INTERFACE_H_ */
