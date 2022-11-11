

#ifndef HAL_HAL_HEATER_ELEMENT_HEATER_ELEMENT_H_
#define HAL_HAL_HEATER_ELEMENT_HEATER_ELEMENT_H_

#include "../../Helper/STD_TYPES.h"
#include "../../Helper/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_register.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include <util/delay.h>

/*CONFIG*/
#define HEAT_PORT        C
#define HEAT_PIN         PIN2

#define COOL_PORT        C
#define COOL_PIN         PIN3

#define STATE_LED_PORT        C
#define STATE_LED_PIN         PIN4

#define BOTH_OFF 0
#define HEAT_ON 1
#define COOL_ON 2
 
/*Functions*/
void HEAT_INIT(void);
void HEAT_START(void);
void HEAT_STOP(void);

void COOL_INIT(void);
void COOL_START(void);
void COOL_STOP(void);

void State_led_INIT(void);
void State_led_start(void);
void State_led_stop(void);
void State_led_tog(void);
u8 getState(void);
/*SET value in EEPROM*/
 void SEND_TEMP(u8 val,u8 add);

#endif /* HAL_HAL_HEATER_ELEMENT_HEATER_ELEMENT_H_ */
