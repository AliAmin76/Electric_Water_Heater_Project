

#ifndef MCAL_MCAL_ADC_ADC_CONFIG_H_
#define MCAL_MCAL_ADC_ADC_CONFIG_H_


#include "../../Helper/STD_TYPES.h"


/**********REG address******************/
#define ADMUX   *((volatile u8*)0x27)
#define ADCSRA  *((volatile u8*)0x26)
#define ADCH    *((volatile u8*)0x25)
#define ADCL	*((volatile u8*)0x24)


/************ADMUX PINS*************/
#define MUX0  0
#define MUX1  1
#define MUX2  2
#define MUX3  3
#define MUX4  4
#define ADLAR 5
#define REFS0 6
#define REFS1 7


/*************ADCSRA PINS************/
#define ADPS0  0
#define ADPS1  1
#define ADPS2  2
#define ADIE   3
#define ADIF   4
#define ADATE  5
#define ADSC   6
#define ADEN   7


/****************ADC PINS*************/
#define ADC_PORT A
#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7


#endif /* MCAL_MCAL_ADC_ADC_CONFIG_H_ */
