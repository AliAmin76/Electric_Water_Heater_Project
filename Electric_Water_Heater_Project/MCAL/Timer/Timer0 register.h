


#ifndef REGISTER_H_
#define REGISTER_H_

#include "../../Helper/STD_TYPES.h"
#include "../../Helper/BIT_MATH.h"


/************************************************************************/
/*                          Timer0                                      */
#define TIMSK (*((volatile u8 *)0x59))
#define TIFR (*((volatile u8 *)0x58))
#define TCCR0 (*((volatile u8 *)0x53))
#define TCNT0 (*((volatile u8 *)0x52))
/************************************************************************/





#endif /* REGISTER_H_ */
