
#include "EEPROM_interface.h"

void EEPROM_init(void)
{
	TWI_Init();
}

void EEPROM_WRITE(u16 Address ,u8 Data)
{
	 TWI_Start();


	    //write the device address and so we need to get A8 A9 A10 address bits and R/W=0 (write)
	    TWI_Write((unsigned char)(0xA0 | ((Address & 0x0700)>>7)));


	    //send the required location address
	    TWI_Write((unsigned char)(Address));


	    //write byte to eeprom
	    TWI_Write(Data);


	    TWI_Stop();


}

void EEPROM_READ(u16 Address ,u8 *Data)
{
	 TWI_Start();


	    //write the device address and so we need to get A8 A9 A10 address bits and R/W=0 (write)
	    TWI_Write((unsigned char)((0xA0) | ((Address & 0x0700)>>7)));


	    //send the required location address
	    TWI_Write((unsigned char)(Address));


	    //send a repeated start
	    TWI_Start();


	    //write the device address and so we need to get A8 A9 A10 address bits and R/W=1 (Read)
	    TWI_Write((unsigned char)((0xA0) | ((Address & 0x0700)>>7) | 1));


	    *Data = TWI_Read_With_NACK();


	    TWI_Stop();
}
