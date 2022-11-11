

#ifndef MCAL_MCAL_TWI_TWI_CONFIG_H_
#define MCAL_MCAL_TWI_TWI_CONFIG_H_

#include "../../Helper/STD_TYPES.h"

#define TWBR *((volatile u8*)0x20)
#define TWCR *((volatile u8*)0x56)
#define TWSR *((volatile u8*)0x21)
#define TWDR *((volatile u8*)0x23)
#define TWAR *((volatile u8*)0x22)

/********************** TWSR ************************/
#define	TWS7 7
#define TWS6 6
#define TWS5 5
#define TWS4 4
#define TWS3 3

#define TWS1 1
#define TWS0 0

/********************** TWAR ************************/
/*
// #define	TWS6  7
// #define TWS5  6
// #define TWS4  5
// #define TWS3  4
// #define TWS2  3
// #define TWS1  2
// #define TWS0  1
// #define TWGCE 0
*/

/********************** TWCR ************************/
#define	TWINT  7
#define TWEA  6
#define TWSTA  5
#define TWSTO  4
#define TWWC  3
#define TWEN  2
#define TWIE 0

#endif /* MCAL_MCAL_TWI_TWI_CONFIG_H_ */
