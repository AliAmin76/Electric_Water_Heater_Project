

/*include timer.h*/
#include "timer.h"


/*function to set timer 0 mode*/
EN_Timer_Error_t timer0_init(u8 mode)
{
	/*switch on mode 
	Bit  3 6
	//   0 0   Normal
	0 1   PWM, Phase Correct
	1 0   CTC OCR0
	1 1   Fast PWM*/ 
	switch(mode)
	{
		/*overflow mode*/
		case OVERFLOW_MODE: // 0 0
		CLR_BIT(TCCR0,3);
		CLR_BIT(TCCR0,6);
		break;
		/*compare mode*/
		case CTC_MODE:// 1 0
		SET_BIT(TCCR0,3);
		CLR_BIT(TCCR0,6);
		break;
		/*fast pwm mode */
		case FAST_PWM_MODE: // 1 1
		SET_BIT(TCCR0,3);
		SET_BIT(TCCR0,6);
		break;
		/*pwm with ohase correct mode*/
		case PWM_PHASE_CORRECT_MODE: // 0 1
		CLR_BIT(TCCR0,3);
		SET_BIT(TCCR0,6);
		break;
		/*if not found return not ok*/
		default:
		return TIMER_NOT_OK;
		break;	
	}
	/*set intial value of data reg to zero*/
	TCNT0 = 0;
	/*if the function did not return not ok till now then it is ok*/
	return TIMER_OK;
}

/*function set prescaler so that timer start*/
EN_Timer_Error_t timer0_start(u8 prescaler)
{
	/*switch on prescaler
	clock select bits 2 1 0
	No clock source   0 0 0
	clk/no prescaler  0 0 1
	clk/8             0 1 0
	clk/64            0 1 1
	clk/256           1 0 0
	clk/1024          1 0 1*/
	switch (prescaler)
	{
		/*if no pre*/
		case NO_PRE:  // 0 0 1
		SET_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);
		break; 
		/*if pre is  8*/
		case PRE8: // 0 1 0
		CLR_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);
		break;
		/*if pre is 64*/
		case PRE64:  // 0 1 1
		SET_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);
		break;
		/*pre 256*/
		case PRE256: // 1 0 0
		CLR_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
		break;
		/*pre 1024*/
		case PRE1024:// 1 0 1
		SET_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
		break;
		/*if not found return not ok*/
		default:
		return TIMER_NOT_OK;
		break;
	}
	/*if the function did not return not ok till now then it is ok*/
	return TIMER_OK;
}


/*function to write intial value on timer0 data reg */
EN_Timer_Error_t timer0_intial_val(u8 initialval)
{
	/*set TCNT0 equal the value*/
	TCNT0 = initialval;
	/*this function will always return ok*/
	return TIMER_OK;
}


/*function to stop the timer*/
EN_Timer_Error_t timer0_stop(void)
{
	// 0 0 0
	/*clear bit 0 , 1 and 2 in TCCR0 reg */
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
	/*this function will always return ok*/
	return TIMER_OK;
}


/*function to set timer0 as counter*/
EN_Timer_Error_t counter0_start(u8 mode)
{
	/*switch on mode
	if falling clear bit 0 and set bit 1 and 2 in TCCR0 reg
	if rising set bit 0,1 and 2 in TCCR0 reg */
	switch(mode)
	{
		/*if on falling*/
		case EX_FALL:// 1 1 0
		CLR_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
		break;
		/*if on rising*/
		case EX_RIS:// 1 1 1
		SET_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
		break;
		/*if not found return not ok*/
		default:
		return TIMER_NOT_OK;
		break;
	}
	/*if the function did not return not ok till now then it is ok*/
	return TIMER_OK;
}

/*timer0_wait_for_flag function is used to busy wait on the flag*/
EN_Timer_Error_t timer0_wait_for_flag(u8 flag)
{
	/*switch on flag
	when found busy wait on it then clear the flag*/
	switch(flag)
	{
		/*if overflow flag*/
		case OVERFLOW_FLAG: // 0 0
		while(!GET_BIT(TIFR,0));  // busy wait 
		SET_BIT(TIFR,0); // clear flag
		break;
		/*if compare flag*/
		case OUT_COMPARE_FLAG:// 1 0
		while(!GET_BIT(TIFR,1));
		SET_BIT(TIFR,1); // clear flag
		break;
		/*if not found return not ok*/
		default:
		return TIMER_NOT_OK;
		break;
	}
	/*if the function did not return not ok till now then it is ok*/
	return TIMER_OK;
}


/*timer0_status is used to get the current timer value
it takes pointer to value*/
EN_Timer_Error_t timer0_status(u8 *val)
{
	/*set pointer to value equal timer value reg */
	*val = TCNT0;
	/*this function will always return ok*/
	return TIMER_OK;
}


EN_Timer_Error_t timer0_interrupt(u8 mode)
{
	switch(mode)
	{
		case OVERFLOW_MODE:
		SET_BIT(TIMSK,0);
		break;
		case CTC_MODE:
		SET_BIT(TIMSK,1);
		break;
		default:
		return TIMER_NOT_OK;
		break;
	} 
	return TIMER_OK;
}


/*delay is a function that takes number of overflow and prescaler to set timer to it*/
EN_Timer_Error_t delay(u8 pre,u8 OverflowNumber)
{
	/*declare counter */
	u8 count = 0;
	/*set timer0 with the passed prescaler*/
	timer0_start(pre);
	/*enter a loop till we reach the needed over flows number so
	we reached the needed delay*/
	while (count < OverflowNumber)
	{
		timer0_wait_for_flag(OVERFLOW_FLAG);
		count++;
	}
	// stop the timer 
	timer0_stop();
	/*this function will always return ok*/
	return TIMER_OK;
}
