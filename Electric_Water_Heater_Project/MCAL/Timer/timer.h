


#ifndef TIMER_H_
#define TIMER_H_

#include "Timer0 register.h"


/*Modes*/
#define OVERFLOW_MODE 0
#define CTC_MODE 1
#define FAST_PWM_MODE 2
#define PWM_PHASE_CORRECT_MODE 3


/* Pre */
#define NO_CLK 0
#define NO_PRE 1
#define PRE8 2
#define PRE64 3
#define PRE256 4
#define PRE1024 5
#define EX_FALL 6
#define EX_RIS 7

/* Flag */
#define OVERFLOW_FLAG 0
#define OUT_COMPARE_FLAG 1


/*Error Handling */
typedef enum EN_Timer_Error_t
{
	TIMER_OK,TIMER_NOT_OK
}EN_Timer_Error_t;
  
#define TIMER0_OVF_vect __vector_11

/* Function Prototype */
EN_Timer_Error_t timer0_init(u8 mode);
EN_Timer_Error_t timer0_start(u8 prescaler);
EN_Timer_Error_t timer0_intial_val(u8 initialval);
EN_Timer_Error_t timer0_stop(void);
EN_Timer_Error_t counter0_start(u8 mode);
EN_Timer_Error_t timer0_wait_for_flag(u8 flag);
EN_Timer_Error_t timer0_status(u8 *val);
EN_Timer_Error_t timer0_interrupt(u8 mode);
EN_Timer_Error_t delay(u8 pre,u8 OverflowNumber);







#endif /* TIMER_H_ */
