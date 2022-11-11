

/*include interrupt.h */
#include "interrupt.h"



/*global_interrupt_state is used to set the state of the SREG bit 7 which is 
global interrupt pin and it takes the state*/
EN_INT_Error_t global_interrupt_state(u8 state)
{
	/*check if state is enable set else clear*/
	if (state == ENABLE)
	{
		SET_BIT(SREG,7);
	}
	else
	{
		CLR_BIT(SREG,7);
	}
	/*this function will always do its function so it will always return ok*/
	return INT_OK;
}


/*interrupt_init function is used to initialize one of the external interrupt
it takes the id of the interrupt and the mode of it */
EN_INT_Error_t interrupt_init(u8 id,u8 mode)
{
	/*enable global interrupt */
	global_interrupt_state(ENABLE);
	/*switch on the external interrupt*/
	/*for external interrupt 0 and 1 check for the mode
	if mode is low then clear bit 0 and 1 in MCUCR reg and set enable bit in GICR
	if mode is any then set bit 0 and clear bit 1 in MCUCR reg and set enable bit in GICR
	if mode is falling then clear bit 0 and set bit 1 in MCUCR reg and set enable bit in GICR
	if mode is rising then set bit 0 and 1 in MCUCR reg and set enable bit in GICR
	if non return not ok
	for external interrupt 2 check for the mode 
	if mode is falling then clear bit 6 in MCUCSR reg and set enable bit in GICR
	if mode is falling then set bit 6 in MCUCSR reg and set enable bit in GICR*/
	switch(id)
	{
		/*if external interrupt 0 then check for mode */
		case EX_INT0:
		if (mode == LOW_MODE)
		{
			CLR_BIT(MCUCR,0);
			CLR_BIT(MCUCR,1);
			SET_BIT(GICR,6);
		}
		else if (mode == ANY_CHANGE_MODE)
		{
			SET_BIT(MCUCR,0);
			CLR_BIT(MCUCR,1);
			SET_BIT(GICR,6);
		}
		else if (mode == FALLING_MODE)
		{
			CLR_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);
			SET_BIT(GICR,6);
		}
		else if (mode == RISING_MODE)
		{
			SET_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);
			SET_BIT(GICR,6);
		}
		else
		{
			return INT_NOT_OK;
		}
		break;
		/*if external interrupt 1 then check for mode */
		case EX_INT1:
		if (mode == LOW_MODE)
		{
			CLR_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
			SET_BIT(GICR,7);
		}
		else if (mode == ANY_CHANGE_MODE)
		{
			SET_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
			SET_BIT(GICR,7);
		}
		else if (mode == FALLING_MODE)
		{
			CLR_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
			SET_BIT(GICR,7);
		}
		else if (mode == RISING_MODE)
		{
			SET_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
			SET_BIT(GICR,7);
		}
		else
		{
			return INT_NOT_OK;
		}
		break;
		/*if external interrupt 2 then check for mode */
		case EX_INT2:
		if (mode == FALLING_MODE)
		{
			CLR_BIT(MCUCSR,6);
			SET_BIT(GICR,5);
		}
		else if (mode == RISING_MODE)
		{
			SET_BIT(MCUCSR,6);
			SET_BIT(GICR,5);
		}
		else
		{
			return INT_NOT_OK;
		}
		break;
		/*if no interrupt found then return not ok*/
		default:
		return INT_NOT_OK;
		break;
	}
	/*if the function did not return not ok till now then it is ok*/
	return INT_OK;
}


/*interrupt_wait_for_flag function is used to busy wait on the flag if needed
and it takes the id of the external interrupt*/
EN_INT_Error_t interrupt_wait_for_flag(u8 id)
{
	/*switch on the id*/
	/*for any of it busy wait on its flag then clear the flag*/
	switch(id)
	{
		/*if external interrupt 0*/
		case EX_INT0:
		while(!GET_BIT(GIFR,6));
		SET_BIT(GIFR,6);
		break;
		/*if external interrupt 1*/
		case EX_INT1:
		while(!GET_BIT(GIFR,7));
		SET_BIT(GIFR,7);
		break;
		/*if external interrupt 2*/
		case EX_INT2:
		while(!GET_BIT(GIFR,5));
		SET_BIT(GIFR,5);
		break;
		/*if not found return not ok*/
		default:
		return INT_NOT_OK;
		break;
	}
	/*if the function did not return not ok till now then it is ok*/
	return INT_OK;
}


/*interrupt_enable function is used to enable the interrupt and it takes the id */
EN_INT_Error_t interrupt_enable(u8 id)
{
	/*switch on the id of the external interrupt
	when found set it is enable bit */
	switch(id)
	{
		/*if external interrupt 0*/
		case EX_INT0:
		SET_BIT(GICR,6);
		break;
		/*if external interrupt 1*/
		case EX_INT1:
		SET_BIT(GICR,7);
		break;
		/*if external interrupt 2*/
		case EX_INT2:
		SET_BIT(GICR,5);
		break;
		/*if not found return not ok*/
		default:
		return INT_NOT_OK;
		break;
	}
	/*if the function did not return not ok till now then it is ok*/
	return INT_OK;
}

/*interrupt_disable function is used to disable the interrupt and it takes the id */
EN_INT_Error_t interrupt_disable(u8 id)
{
	/*switch on the id of the external interrupt
	when found clear it is enable bit */
	switch(id)
	{
		/*if external interrupt 0*/
		case EX_INT0:
		CLR_BIT(GICR,6);
		break;
		/*if external interrupt 1*/
		case EX_INT1:
		CLR_BIT(GICR,7);
		break;
		/*if external interrupt 2*/
		case EX_INT2:
		CLR_BIT(GICR,5);
		break;
		/*if not found return not ok*/
		default:
		return INT_NOT_OK;
		break;
	}
	/*if the function did not return not ok till now then it is ok*/
	return INT_OK;
}


