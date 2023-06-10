/*
 * RTOS_program.c
 *
 * Created: 4/4/2023 8:06:21 AM
 *  Author: Ahmed Nour
 */ 



#include "../utilities/BIT_MATH.h"
#include "../utilities/Data_Type.h"
#include "../utilities/DIO_REG.h"
#include "../MCAL/Timer/Timer.h"
#include "../MCAL/EXTI/Interrupt.h"

#include "RTOS_private.h"
#include "RTOS_interface.h"
#include "RTOS_config.h"



Task_t SystemTasks[TASK_NUM] = {{NULL}};

/*Init the system*/
void RTOS_voidStart(void)
{
	//timer0_ComparaMatch_setCallBack  ---> this is the isr set call back timer 0
	timer0_ComparaMatch_setCallBack(&voidScheduler);  // (voidScheduler) de ely 3ayzeenha t run fe isr fun bta3t al timer
	global_inti_Enable();
	Timer0_init();
}

void RTOS_voidCreateTask(uint8 Copy_u8Priority, uint16 Copy_u16Periodicity, void (*Copy_pvTaskFunc)(void))
{
	/*work as static allocation f ana m7tag 3dd al task hro7 a3rfo fe al config */
	/*index of arr hwa hwa priority */
	SystemTasks[Copy_u8Priority].Periodicity= Copy_u16Periodicity;  // arr[0] , arr[1] ,arr[2]
	SystemTasks[Copy_u8Priority].TaskFunc=Copy_pvTaskFunc;
}

 void voidScheduler(void)
{
	static uint16 local_u16TickCounter=0;
	
	
	uint8 Local_u8TaskCounter;
	/*this var for for loop to read the tasks the user made*/
	local_u16TickCounter++;
	
	
	/*loop on all tasks to check the periodicity*/
	for(Local_u8TaskCounter=0;Local_u8TaskCounter<TASK_NUM;Local_u8TaskCounter++)
	{
		if((local_u16TickCounter % SystemTasks[Local_u8TaskCounter].Periodicity)==0)
		{
			/*invoke the task function*/
			if (SystemTasks[Local_u8TaskCounter].TaskFunc != NULL)
			{
				SystemTasks[Local_u8TaskCounter].TaskFunc();
			}
			else
			{
				// do nothing
			}
		}
	}


}







