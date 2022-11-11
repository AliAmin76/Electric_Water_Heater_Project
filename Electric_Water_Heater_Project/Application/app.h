


#ifndef APP_H_
#define APP_H_


/************************************************************************/
/*                        Needed Files                                  */
#include "../HAL/LED/LED_interface.h"
#include "../HAL/Button/Button_interface.h"
#include "../HAL/7 Segment/Seven_Segment.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../MCAL/Interrupt/interrupt.h"
#include "../MCAL/Timer/timer.h"
#include "../HAL/Heater/HEATER_ELEMENT.h"
#include "../HAL/Temp Sensor/LM35.h"
/************************************************************************/


/************************************************************************/
/*                   Important Defines                                  */
#define OFF 0
#define ON 1
#define SET 2
#define ADDRESS 0X0311
#define INITIAL_SET_TEMP 60
#define SET_NUM_OVERFLOWS 4
#define ON_NUM_OVERFLOWS 2
#define SET_INTIAL_VALUE 12
#define READ_VALUE 61
#define SIZE 10
/************************************************************************/


/************************************************************************/
/*                      Function Prototypes                             */
void APP_init();
void APP_start();
/************************************************************************/



#endif /* APP_H_ */