/*
 * UART.c
 *
 * Created: 3/21/2023 3:27:53 PM
 *  Author: Ahmed Nour
 */ 
#include "UART.h"
void UART_init()
{
	/*local variable to hold the required value of UCSRC register */
	uint8 local_UCSRCVsl= 0;
	/*choose the UCSRC REG */ 
	Set_Bit(local_UCSRCVsl,UCSRC_URSEL);
	/*choose the character size : 8 bit size*/
	Set_Bit(UCSRC_REG,UCSRC_UCSZ0);
	Set_Bit(UCSRC_REG,UCSRC_UCSZ1);
	Clear_Bit(UCSRB_REG,UCSRB_UCSZ2);
	
	/*we need to set boud rate: for sys 8 MHz & boud rate 9600 we set boud =51 */
	UBRRL_REG = 51;
	/*enable TX*/
	Set_Bit(UCSRB_REG,UCSRB_TXEN);
	/*enable RX*/
	Set_Bit(UCSRB_REG,UCSRB_RXEN);
}

void UART_SendData(uint8 data)
{
	while((Get_Bit(UCSRA_REG,UCSRA_UDRE)==0));
	/*send the data*/
	UDR_REG= data;  //buffer
}

uint8 UART_ReceivedData()
{
	/*wait until receive complete event happens*/
	while((Get_Bit(UCSRA_REG,UCSRA_RXC))==0);
	
	/*return the data*/
	return UDR_REG; //buffer
}