

#ifndef HAL_HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_HAL_EEPROM_EEPROM_INTERFACE_H_

#include "../../MCAL/TWI/TWI_interface.h"


void EEPROM_init(void);

void EEPROM_WRITE(u16 Address ,u8 Data);

void EEPROM_READ(u16 Address ,u8 *Data);
#endif /* HAL_HAL_EEPROM_EEPROM_INTERFACE_H_ */
