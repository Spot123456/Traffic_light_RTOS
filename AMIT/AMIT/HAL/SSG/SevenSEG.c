/*
 * SevenSEG.c
 *
 * Created: 2/24/2023 6:47:05 PM
 *  Author:  Ahmed Nour
 */ 

#include "SevenSEG.h"
#include <util/delay.h>
void sev_segment_init()
{
	
	DIO_set_pin_direction(seven_SEG_Port,pin4,output);
	DIO_set_pin_direction(seven_SEG_Port,pin5,output);
	DIO_set_pin_direction(seven_SEG_Port,pin6,output);
	DIO_set_pin_direction(seven_SEG_Port,pin7,output);
	
}

void seven_segment_enable(EN_Enable_segment EN)
{
	if(EN<=EN2)
	switch (EN)
	{
		case EN1 :DIO_set_pin_direction(Enable_seven_port,pin4,output); DIO_set_pin_value(Enable_seven_port,pin4,HIGH) ; break;
		case EN2 :DIO_set_pin_direction(Enable_seven_port,pin5,output); DIO_set_pin_value(Enable_seven_port,pin5,HIGH) ; break;
	}
}

void seven_segment_Disable(EN_Enable_segment EN)
{
	if(EN<=EN2)
	switch (EN)
	{
		case EN1 : DIO_set_pin_value(Enable_seven_port,pin4,LOW) ; break;
		case EN2 : DIO_set_pin_value(Enable_seven_port,pin5,LOW) ; break;
	}
}

void seven_segment_write_NO(uint8 No)
{
	//No =3  ----> 0b0000 0011
	//					  dcba
	if(No<10)
	{
		DIO_set_pin_value(seven_SEG_Port,pin4,Get_Bit(No,0));  //a
		DIO_set_pin_value(seven_SEG_Port,pin5,Get_Bit(No,1));  //b
		DIO_set_pin_value(seven_SEG_Port,pin6,Get_Bit(No,2));  //c
		DIO_set_pin_value(seven_SEG_Port,pin7,Get_Bit(No,3));  //d
	}
}

void two_sev_seg(uint8 No)
{
	//please don't forget the INIT fun. 
	//NO = 48 ----> 4  8 use remender and divider
	
	uint8 right=No%10;
	uint8 left=No/10;
	//seven_segment_Disable(EN1);
	//seven_segment_Disable(EN2);
	seven_segment_write_NO(right);
	seven_segment_enable(EN1);
	_delay_ms(100);
	seven_segment_Disable(EN1);
	seven_segment_write_NO(left);
	seven_segment_enable(EN2);
	_delay_ms(100);
	seven_segment_Disable(EN2);
}