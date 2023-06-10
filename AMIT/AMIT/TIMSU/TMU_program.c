
#include "STD_TYPES.h"

#include "TMU_config.h"
#include "TMU_private.h"
#include "TMU_interface.h"
#include "../utilities/DIO_REG.h"
#include "../MCAL/DIO/DIO.h"

static TCB_t Tasks[MAX_TASKS]; // MAX priority = MAX_TASKS-1

static u8 Num_ISR;
static u8 Count_ISR;

static u16 Count_Sch;
#define F_CPU	16000000ul
void TMU_Init(void)
{
	
#if TIM_CH == CH0
	
		TCCR0 = 0x0D;
		TIMSK |= (1 << 1);
		
		#if OS_TICK <= 16 && OS_TICK > 0
		
			OCR0 = (OS_TICK * F_CPU)/(1024000ul);
			Num_ISR = 1;
			Count_ISR = Num_ISR;
			
		#elif OS_TICK > 16 /// 1 2 3 ....16 ----> 28 14 7 2
			
			u8 max; //28 //41 any time greater than 16 ms 
			for(u8 i=1; i<=16; i++)
			{
				if(OS_TICK%i == 0)
				{
					max = i; //1  2   4   7  14
				}
			}
			
			//OCR0 = (OS_TICK * F_CPU)/(1024000ul);
			OCR0 = (max * F_CPU)/(1024000ul);
			Num_ISR = (OS_TICK / max);
			Count_ISR = Num_ISR;
		
		#else
			#error "your os tick exceed ( ) msec"
		#endif
			
	
#elif TIM_CH == CH1
	TCCR1A = 0x00;
	TCCR1B = 0x0D;
	TIMSK |= (1 << 4);
	
	#if OS_TICK < = 4194 && OS_TICK > 0
	u16 counts = (OS_TICK * F_CPU) / (1024000ul);
	OCR1AH_REG = (u8)(counts >> 8);
	OCR1Al_REG = (u8)(counts );

	Num_ISR = 1;
	Count_ISR = Num_ISR;
		#else
		#error "your os tick exceed ( ) msec"
		#endif

	#elif TIM_CH == CH2
		
		TCCR2 = 0x0F;
		TIMSK |= (1 << 7);
		
		#if OS_TICK <= 16 && OS_TICK > 0
		
			OCR2 = (OS_TICK * F_CPU)/(1024000ul);
			Num_ISR = 1;
			Count_ISR = Num_ISR;
			
		#elif OS_TICK > 16 /// 1 2 3 ....16 ---- 28 14 7 2
			
			u8 max; //28
			for(u8 i=1; i<=16; i++)
			{
				if(OS_TICK%i == 0)
				{
					max = i; 
				}
			}
			
			OCR2 = (max * F_CPU)/(1024000ul);
			Num_ISR = (OS_TICK / max);
			Count_ISR = Num_ISR;
		
		#else
			#error "your os tick exceed ( ) msec"
		#endif
			
	
	#else
		#error "selection of timer channel is wrong"
	#endif
	
//#endif	
}

void TMU_CreateTask( void(*Fptr)(void),
u16 Peridicity,
u8 Priority)
{
	if(Fptr != NULL && Priority < MAX_TASKS)
	{
		Tasks[Priority].Fptr = Fptr;
		Tasks[Priority].periodicity = Peridicity;
		Tasks[Priority].state = READY;
		
	}
}
void TMU_StartScheduler(void)
{
	asm("SEI");
	while(1);
}



#if TIM_CH == CH0
// timer0
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	Count_ISR --; //5 4 3 2 1 0
	if(Count_ISR == 0)
	{
		// scheduler
		Count_Sch++;
		
		//for(s8 i =MAX_TASKS-1; i>=0; i--)  // high = MAX_TASKS -1   , low = 0
		
		for(u8 i =0; i<MAX_TASKS; i++)  // high = 0   , low = MAX_TASKS -1
		{
			if(Tasks[i].Fptr != NULL &&
			Tasks[i].state == READY &&
			Count_Sch % Tasks[i].periodicity == 0)
			{
				Tasks[i].Fptr();
			}
		}

		Count_ISR = Num_ISR;
	}
	
}


#elif TIM_CH == CH1
// timer1
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	Count_ISR --;
	u8 i =0;
	if(Count_ISR == 0)
	{
		// scheduler
		Count_Sch++;
		
		//for(s8 i =MAX_TASKS-1; i>=0; i--)  // high = MAX_TASKS -1   , low = 0
		
		for( i =0; i<MAX_TASKS; i++)  // high = 0   , low = MAX_TASKS -1
		{
			if(Tasks[i].Fptr != NULL &&
			Tasks[i].state == READY &&
			Count_Sch % Tasks[i].periodicity == 0)
			{
				Tasks[i].Fptr();
			}
		}
		
		Count_ISR = Num_ISR;
	}
	
}


#elif TIM_CH == CH2
// timer2
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	Count_ISR --; //5 4 3 2 1 0
	if(Count_ISR == 0)
	{
		// scheduler
		Count_Sch++;
		
		//for(s8 i =MAX_TASKS-1; i>=0; i--)  // high = MAX_TASKS -1   , low = 0
		
		for(u8 i =0; i<MAX_TASKS; i++)  // high = 0   , low = MAX_TASKS -1
		{
			if(Tasks[i].Fptr != NULL &&
			Tasks[i].state == READY &&
			Count_Sch % Tasks[i].periodicity == 0)
			{
				Tasks[i].Fptr();
			}
		}
		
		Count_ISR = Num_ISR;
	}
	
}

#else
#error "selection of timer channel is wrong"
#endif
