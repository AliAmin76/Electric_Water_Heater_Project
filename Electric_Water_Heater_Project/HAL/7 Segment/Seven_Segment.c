

#include "Seven_Segment.h"


/*******************disable 7_segment*********************/
void Seven_segment_enable(u8 Segment)
{
	if (Segment == TENS)
	{
		DIO_setPinDir(B, PIN3, OUT);
		DIO_setPinval(B, PIN3, HIGH);
	}
	else if (Segment == UNIT)
	{
		DIO_setPinDir(B, PIN1, OUT);
		DIO_setPinval(B, PIN1, HIGH);
	}
}


/*******************enable 7_segment*********************/
void Seven_segment_disable(u8 Segment)
{
	if (Segment == TENS)
	{
		DIO_setPinDir(B, PIN3, OUT);
		DIO_setPinval(B, PIN3, LOW);
	}
	else if (Segment == UNIT)
	{
		DIO_setPinDir(B, PIN1, OUT);
		DIO_setPinval(B, PIN1, LOW);
	}
}
/**************active 7_segment on which pins *****************/
void Seven_segment_init(u8 PORTID,u8 type)
{
  if(type == MSB)
  {
	  DIO_setPinDir(PORTID, PIN4, OUT);
	  DIO_setPinDir(PORTID, PIN5, OUT);
	  DIO_setPinDir(PORTID, PIN6, OUT);
	  DIO_setPinDir(PORTID, PIN7, OUT);
  }
  else if (type == LSB)
  {
	  DIO_setPinDir(PORTID, PIN0, OUT);
	  DIO_setPinDir(PORTID, PIN1, OUT);
	  DIO_setPinDir(PORTID, PIN2, OUT);
	  DIO_setPinDir(PORTID, PIN3, OUT);
  }
  else
  {
	  /*do nothing*/
  }
}


/*********************write value on 7_segment*****************/
void Write_Seven_segment(u8 PORTID,u8 type, u8 num)
{
	if(type == MSB)
	{
		switch(PORTID)
				{
				case A: PORTA=(PORTA & 0x0F) | (num<<4);
					break;
				case B: PORTB=(PORTB & 0x0F) | (num<<4);
					break;
				case C: PORTC=(PORTC & 0x0F) | (num<<4);
					break;
				case D: PORTD=(PORTD & 0x0F) | (num<<4);
					break;
				default:/*do no thing*/
					break;
				}
	}
	else if (type == LSB)
	{
		switch(PORTID)
		{
		case A: PORTA=(PORTID & 0xF0) | (num & 0x0F);
			break;
		case B: PORTB=(PORTID & 0xF0) | (num & 0x0F);
			break;
		case C: PORTC=(PORTID & 0xF0) | (num & 0x0F);
			break;
		case D: PORTD=(PORTID & 0xF0) | (num & 0x0F);
			break;
		default:/*do no thing*/
			break;
		}
	}
}


/***********************read value on 7_segment***********************/
u8 Read_Seven_segment(u8 PORTID,u8 type)
{
	u8 Bits = 0;
	if(type == MSB)
	{
		Bits = ((PORTID & 0xF0)>>4);
	}
	else if (type == LSB)
	{
		Bits = (PORTID & 0x0F);
	}
	return Bits ;
}


/***********************write value on both 7_segment***********************/
void BothSevenSegmentWrite(u8 PORTID,u8 type,u8 val)
{
	u8 tens,ones;
	if (val <= 99)
	{
		tens = val / 10 ;
		ones = val%10;
		for (u8 i = 0 ; i <= 10 ; i++)
		{
			Seven_segment_disable(TENS);
			Seven_segment_enable(UNIT);
			Write_Seven_segment(PORTID,type,ones);
			_delay_ms(5);
			Seven_segment_disable(UNIT);
			Seven_segment_enable(TENS);
			Write_Seven_segment(PORTID,type,tens);
			_delay_ms(5);
		}
	}
	else
	{
		/* do nothing */
	}
}

void BothSevenSegmentWriteFloat(u8 PORTID,u8 type,u32 val)
{
	u8 tens,ones;
	if (val <= 99)
	{
		tens = val / 10 ;
		ones = val%10;
		for (u8 i = 0 ; i <= 10 ; i++)
		{
			Seven_segment_disable(TENS);
			Seven_segment_enable(UNIT);
			Write_Seven_segment(PORTID,type,ones);
			_delay_ms(5);
			Seven_segment_disable(UNIT);
			Seven_segment_enable(TENS);
			Write_Seven_segment(PORTID,type,tens);
			_delay_ms(5);
		}
	}
	else
	{
		/* do nothing */
	}
}

void SevenSegmentWriteFloat(u8 PORTID,u8 type,u32 val)
{
	u8 tens,ones;
	if (val <= 99)
	{
		tens = val / 10 ;
		ones = val%10;
		Seven_segment_enable(UNIT);
		Seven_segment_enable(TENS);
		if (type == MSB)
		{
			Write_Seven_segment(B,MSB,ones);
		}
		else if (type == LSB)
		{
			Write_Seven_segment(A,LSB,tens);
		}
	}
	else
	{
		/* do nothing */
	}
}




