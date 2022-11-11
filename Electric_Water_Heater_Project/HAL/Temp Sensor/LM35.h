

#ifndef HAL_HAL_LM35_LM35_INTERFACE_H_
#define HAL_HAL_LM35_LM35_INTERFACE_H_


#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "../../HAL/7 Segment/Seven_Segment.h"


#define VREF		  external
#define prescale 	  64
#define MODE          LSB





void LM35_init(u8 PORTID,u8 PINID);

u8 LM35_Read(u8 Channel);

void LM35_Display(u8 Delay, u8 Channel);

#endif /* HAL_HAL_LM35_LM35_INTERFACE_H_ */
