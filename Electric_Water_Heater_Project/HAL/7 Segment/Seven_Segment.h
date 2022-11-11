

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_


#include "../Button/Button_interface.h"
#include <util/delay.h>


#define MSB 1          //second 4 bits in port
#define LSB 0          //first 4 bits in port


#define TENS 1
#define UNIT 0


/*******************enable 7_segment*********************/
void Seven_segment_enable(u8 Segment);
/*******************disable 7_segment*********************/
void Seven_segment_disable(u8 Segment);
/**************active 7_segment on which pins *****************/
void Seven_segment_init(u8 PORTID,u8 type);
/*********************write value on 7_segment*****************/
void Write_Seven_segment(u8 PORTID,u8 type, u8 num);
/***********************read value on 7_segment***********************/
u8 Read_Seven_segment(u8 PORTID,u8 type);
/***********************write value on both 7_segment***********************/
void BothSevenSegmentWrite(u8 PORTID,u8 type,u8 val);

void BothSevenSegmentWriteFloat(u8 PORTID,u8 type,u32 val);
void SevenSegmentWriteFloat(u8 PORTID,u8 type,u32 val);


#endif /* SEVEN_SEGMENT_H_ */
