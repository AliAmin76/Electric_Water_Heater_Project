

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


/************************************************************************/
/*                        Needed Files                                  */
#include "DIO_register.h"
#include "../../Helper/BIT_MATH.h"
/************************************************************************/


#define IN 0
#define OUT 1


#define LOW 0
#define HIGH 1


#define PORT_LOW 0x00
#define PORT_HIGH 0xFF


#define IN_PORT 0x00
#define OUT_PORT 0xFF


/*********port id************/
#define A 0
#define B 1
#define C 2
#define D 3


/*********pin id************/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7


/*********function of port prototypes************/
void DIO_setPortDir(u8 PORTID,u8 Dir);
void DIO_setPortval(u8 PORTID,u8 portval);
u8 DIO_getPortval(u8 PORTID);


/*********function of Pin prototypes************/
void DIO_setPinDir(u8 PORTID,u8 PINID,u8 Dir);
void DIO_setPinval(u8 PORTID,u8 PINID,u8 pinval);
u8 DIO_getPinval(u8 PORTID,u8 PINID);


/*******************activate pullup resistor  **********************/
void DIO_pullup_Port(u8 PORTID);
void DIO_pullup_PIN(u8 PORTID,u8 PINID);


/****************Set nibbles ***************/
void DIO_SetHighrNibbles(u8 Data);
void DIO_SetLowerNibbles(u8 Data);


#endif /* DIO_INTERFACE_H_ */


