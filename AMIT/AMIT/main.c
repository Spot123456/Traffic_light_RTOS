/*
 * AMIT.c
 *
 * Created: 2/17/2023 7:48:36 PM
 * Author : Ahmed Nour
 */ 

//#include <avr/io.h>
#include <util/delay.h>
#include "HAL/keypad/keypad.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/ADC/ADC.h"
#include "MCAL/Timer/Timer.h"
#include "MCAL/EXTI/Interrupt.h"
#include "Comm/Spi/SPI.h"
#include "RTOS/RTOS_interface.h"
#include "HAL/ICU/ICU.h"
#include "TIMSU/TMU_interface.h"
#include "HAL/SSG/SevenSEG.h"
#include "HAL/Button/Button.h"
//#define F_CPU	16000000

/*	
void led1();
void led2();

//lab2&3 
void main ()
{
	DIO_set_pin_direction(PORTA,pin0,output);
	Timer0_init();
	DIO_set_pin_direction(PORTA,pin0,output);
	DIO_set_pin_direction(PORTA,pin1,output);
	DIO_set_pin_direction(PORTA,pin2,output);
	DIO_set_pin_direction(PORTA,pin3,output);
	
	timer0_setCallBack(&led1);

	
	
	asm("SEI");
	while(1);
}
// lab 2 

void led1()
{
	uint16 static local_counter=0; // for interrupt
	local_counter++;
	uint8 static x =0;
	uint8 static a =0;
	uint8 static b =0;
	uint8 static c =0;
	if(local_counter%500*8==0)
	{
		
		x^=1;
		DIO_set_pin_value(PORTA,pin0,x);
	}
	if(local_counter%1000*8==0)
	{
		a^=1;
		DIO_set_pin_value(PORTA,pin1,a);
	}
	if(local_counter%1500*8==0)
	{
		b^=1;
		DIO_set_pin_value(PORTA,pin2,b);
	}
	if(local_counter%2000*8==0)
	{
		c^=1;
		DIO_set_pin_value(PORTA,pin3,c);
	}
}
// lab 3
void led2()
{
	uint16 static local_counter=0; // for interrupt
	local_counter++;
	uint8 static x =0;
	uint8 static a =0;
	uint8 static b =0;
	uint8 static c =0;
	if(local_counter%53*8==0)
	{
		x^=1;
		DIO_set_pin_value(PORTA,pin0,x);
	}
	if(local_counter%117*8==0)
	{
		a^=1;
		DIO_set_pin_value(PORTA,pin1,a);
	}
	if(local_counter%159*8==0)
	{
		b^=1;
		DIO_set_pin_value(PORTA,pin2,b);
	}
	if(local_counter%216*8==0)
	{
		c^=1;
		DIO_set_pin_value(PORTA,pin3,c);
	}
}

*/

/*
// lab 4 
void task1();
void task2();
void task3();
void task4();
int main()
{
	DIO_set_pin_direction(PORTA,pin0,output);
	DIO_set_pin_direction(PORTA,pin1,output);
	DIO_set_pin_direction(PORTA,pin2,output);
	DIO_set_pin_direction(PORTA,pin3,output);
	TMU_Init();
	TMU_CreateTask(task1,53,0);
	TMU_CreateTask(task2,117,1);
	TMU_CreateTask(task3,153,2);
	TMU_CreateTask(task4,216,3);
		asm("SEI");
	while(1)
	{
		
	}
	return 0;
}


void task1()
{
	
	uint8 static x =0;
		x^=1;
		DIO_set_pin_value(PORTA,pin0,x);
}
void task2()
{
	uint8 static a =0;
	a^=1;
	DIO_set_pin_value(PORTA,pin1,a);
}
void task3()
{
	uint8 static b =0;
	b^=1;
	DIO_set_pin_value(PORTA,pin2,b);
}
void task4()
{
	uint8 static c =0;
	c^=1;
	DIO_set_pin_value(PORTA,pin3,c);
}*/

void task1();	//green
void task2();	// yellow
void task3();	// red
void task4();	// 7 seg
void task5();	// up
void task6();	// down
uint8 static global_count = 0;
uint8 static x=0;
int main ()
{
	// led initialized 
		DIO_set_pin_direction(PORTA,pin0,output);
		DIO_set_pin_direction(PORTA,pin1,output);
		DIO_set_pin_direction(PORTA,pin2,output);
	//	seven seg initialized	
		sev_segment_init();
		// first seven seg enable
		seven_segment_enable(0);
		// first seven seg enable
		seven_segment_enable(1);
		
		// button up 
		Button_Init(pin0,PORTC);
		// button down 
		Button_Init(pin1,PORTC);
		// init the user RTOS ( not free RTOS)
		TMU_Init();
		// create the taskes we have on the system
		TMU_CreateTask(task1,100,0); // 1 sec
		TMU_CreateTask(task2,100,1);
		TMU_CreateTask(task3,100,2);
		TMU_CreateTask(task4,100,3);
		TMU_CreateTask(task5,5,4);	//0.05 sec
		TMU_CreateTask(task6,5,5);
		// open the global init 
		asm("SEI");
	
	while(1);
	
}



void task1()
{
	global_count++; // every 10 ms counter inc by 1 
	if(global_count<=15+(x/2)) 
	{
		DIO_set_pin_value(PORTA,pin0,HIGH); // green led on 
	}
	else
	{
		DIO_set_pin_value(PORTA,pin0,LOW);	// green led off
	}
	if(global_count>=30+(x))  // if go to the max reset the counter
	{
		global_count=0;
	}
}
void task2()
{
	if((global_count<=15+(x/2)&&global_count>12+(x/2) ) || ((global_count<=30+(x) && global_count>=27+(x))) ) //30 -->33  T 33-->36 T
	{
		DIO_set_pin_value(PORTA,pin1,HIGH); // yellow on
	}
	else
	{
		DIO_set_pin_value(PORTA,pin1,LOW);	// yellow off
	}
}
void task3()
{
	if(global_count>15+(x/2) && global_count<=30+(x) ) //18--->33 T but i need 36 not 33  so we wrote x not x/2
	{
		DIO_set_pin_value(PORTA,pin2,HIGH);		// red on
	}

	else
	{
		DIO_set_pin_value(PORTA,pin2,LOW);	//red off
		
	}
}

void task4()
{
	u8 z =0 ;
	z=global_count; // counter for 7_SEG
	if(z<=15+(x/2)) // less than the have way counter 
	{
		two_sev_seg(z); // 0 -> max count / 2 
	}
	if(z>15+(x/2))	// more than the half	// EX:  19	 33		36
	{
		z-=15+(x/2);	//19-18=1    // 33-18 =15	36-18=18
		two_sev_seg(z); // 0 ->> max count / 2
	}
	
	
}

void task5()
{
	
 	if(Button_read(pin0,PORTC)==1) // get the state of button 1 if pressed count x by +2 
	 {
		 while (Button_read(pin0,PORTC)==1);
		 x+=2;
	 }
	 if (x>=85)	// if more than the maximum val return it to the max value ( 85)
	 {
		 x=85;
	 }
	 
}

void task6()
{
	
	if(Button_read(pin1,PORTC)==1)  // get the state of button 1 if pressed count x by -2 
	{
		while (Button_read(pin1,PORTC)==1);
		x-=2;
	}
	if (x<=0) // if less than the minimum val return it to minmum val ( zero) 
	{
		x=0;
	}
	
}