

#include "DIO_interface.h"


/*********function of port************/


void DIO_setPortDir(u8 PORTID,u8 portDir)
{
	switch(PORTID)
	{
	case A: DDRA=portDir;
		break;
	case B: DDRB=portDir;
		break;
	case C: DDRC=portDir;
		break;
	case D: DDRD=portDir;
		break;
	default:/*do no thing*/
		break;
	}
}


void DIO_setPortval(u8 PORTID,u8 portval)
{
	switch(PORTID)
		{
		case A: PORTA=portval;
			break;
		case B: PORTB=portval;
			break;
		case C: PORTC=portval;
			break;
		case D: PORTD=portval;
			break;
		default:/*do no thing*/
			break;
		}
}


u8 DIO_getPortval(u8 PORTID)
{
	u8 portval = 0;
	switch(PORTID)
			{
			case A: portval=PINA;
				break;
			case B: portval=PINB;
				break;
			case C: portval=PINC;
				break;
			case D: portval=PIND;
				break;
			default:/*do no thing*/
				break;
			}
	return portval;
}


/*********function of Pin************/
void DIO_setPinDir(u8 PORTID,u8 PINID,u8 Dir)
{
	if(Dir == OUT)
	{
		switch(PORTID)
				{
				case A: SET_BIT(DDRA, PINID);
					break;
				case B: SET_BIT(DDRB, PINID);
					break;
				case C: SET_BIT(DDRC, PINID);
					break;
				case D: SET_BIT(DDRD, PINID);
					break;
				default:/*do no thing*/
					break;
				}
	}
	else if(Dir == IN)
	{
		switch(PORTID)
			{
			case A : CLR_BIT(DDRA, PINID);
				break;
			case B: CLR_BIT(DDRB, PINID);
				break;
			case C: CLR_BIT(DDRC, PINID);
				break;
			case D: CLR_BIT(DDRD, PINID);
				break;
			default:/*do no thing*/
				break;
			}
	}
	else
	{
		/*do no thing*/
	}

}


void DIO_setPinval(u8 PORTID,u8 PINID,u8 pinval)
{
	if(pinval == HIGH)
		{
			switch(PORTID)
					{
					case A: SET_BIT(PORTA, PINID);
						break;
					case B: SET_BIT(PORTB, PINID);
						break;
					case C: SET_BIT(PORTC, PINID);
						break;
					case D: SET_BIT(PORTD, PINID);
						break;
					default:/*do no thing*/
						break;
					}
		}
	else if(pinval == LOW)
		{
			switch(PORTID)
				{
			case A : CLR_BIT(PORTA, PINID);
				break;
			case B: CLR_BIT(PORTB, PINID);
				break;
			case C: CLR_BIT(PORTC, PINID);
				break;
			case D: CLR_BIT(PORTD, PINID);
				break;
			default:/*do no thing*/
				break;
				}

		}
	else
	{
		/*do no thing*/
	}
}


u8 DIO_getPinval(u8 PORTID,u8 PINID)
{
	u8 pinval = 0;
	switch(PORTID)
	{
	case A: pinval=GET_BIT(PINA, PINID);
		break;
	case B: pinval=GET_BIT(PINB, PINID);
		break;
	case C: pinval=GET_BIT(PINC, PINID);
		break;
	case D: pinval=GET_BIT(PIND, PINID);
		break;
	default:/*do no thing*/
		break;
	}
	return pinval;
}


/*******************activate pullup resistor  **********************/
void DIO_pullup_Port(u8 PORTID)
{
	DIO_setPortDir(PORTID, IN_PORT);
	DIO_setPortval(PORTID, PORT_HIGH);
}
void DIO_pullup_PIN(u8 PORTID,u8 PINID)
{
	DIO_setPinDir(PORTID,PINID, IN);
	DIO_setPinval(PORTID,PINID, HIGH);
}


/****************Set nibbles ***************/
void DIO_SetHighrNibbles(u8 Data)
{
	PORTA=(PORTA & 0x0F)|(Data & 0xF0);
}


void DIO_SetLowerNibbles(u8 Data)
{
	PORTA=(PORTA & 0x0F)|(Data << 4);
}


