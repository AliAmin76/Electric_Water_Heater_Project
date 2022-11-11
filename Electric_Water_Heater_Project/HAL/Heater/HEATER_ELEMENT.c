
#include "../../HAL/Heater/HEATER_ELEMENT.h"
#include "../../HAL/EEPROM/EEPROM_interface.h"
void HEAT_INIT(void)
{
	DIO_setPinDir(HEAT_PORT,HEAT_PIN,OUT);
}
void HEAT_START(void)
{
	DIO_setPinval(HEAT_PORT,HEAT_PIN,HIGH);
}
void HEAT_STOP(void)
{
	DIO_setPinval(HEAT_PORT,HEAT_PIN,LOW);
}

void COOL_INIT(void)
{
	DIO_setPinDir(COOL_PORT,COOL_PIN,OUT);
}
void COOL_START(void)
{
	DIO_setPinval(COOL_PORT,COOL_PIN,HIGH);
}
void COOL_STOP(void)
{
	DIO_setPinval(COOL_PORT,COOL_PIN,LOW);
}

void State_led_INIT(void)
{
	DIO_setPinDir(STATE_LED_PORT,STATE_LED_PIN,OUT);
}
void State_led_start(void)
{
	DIO_setPinval(STATE_LED_PORT,STATE_LED_PIN,HIGH);
}
void State_led_stop(void)
{
	DIO_setPinval(STATE_LED_PORT,STATE_LED_PIN,LOW);
}

void State_led_tog(void)
{
	DIO_setPinval(STATE_LED_PORT,STATE_LED_PIN,HIGH);
	_delay_ms(1000);
	DIO_setPinval(STATE_LED_PORT,STATE_LED_PIN,LOW);
}


u8 getState(void)
{
	if (DIO_getPinval(HEAT_PORT,HEAT_PIN)==HIGH)
	{
		return HEAT_ON;
	}
	else if (DIO_getPinval(COOL_PORT,COOL_PIN)==HIGH)
	{
		return COOL_ON;
	}
	else
	{
		return BOTH_OFF;
	}
}

void SEND_TEMP(u8 val,u8 add)
{
	EEPROM_init();
	EEPROM_WRITE(add ,val);
}
