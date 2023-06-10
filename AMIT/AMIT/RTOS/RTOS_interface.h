/*
 * RTOS_interface.h
 *
 * Created: 4/4/2023 8:05:39 AM
 *  Author: Ahmed Nour
 */ 


#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_

void RTOS_voidStart(void);

void RTOS_voidCreateTask(uint8 Copy_u8Priority, uint16 Copy_u16Periodicity, void (*Copy_pvTaskFunc)(void));
 //  ??????? ???? ?? ?? Timer 0 



#endif /* RTOS_INTERFACE_H_ */