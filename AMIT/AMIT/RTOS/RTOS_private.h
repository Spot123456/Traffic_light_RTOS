/*
 * RTOS_private.h
 *
 * Created: 4/4/2023 8:06:00 AM
 *  Author: Ahmed Nour
 */ 


#ifndef RTOS_PRIVATE_H_
#define RTOS_PRIVATE_H_



typedef struct
{
	uint16 Periodicity;
	void(*TaskFunc)(void);

}Task_t;

 void voidScheduler(void);





#endif /* RTOS_PRIVATE_H_ */