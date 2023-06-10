/*
 * SevenSEG.h
 *
 * Created: 2/24/2023 6:47:15 PM
 *  Author:  Ahmed Nour
 */ 


#ifndef SEVENSEG_H_
#define SEVENSEG_H_
#include "../../utilities/BIT_MATH.h"
#include "../../utilities/Data_Type.h"
#include "../../utilities/DIO_REG.h"
#include "../../MCAL/DIO/dio.h"
#include "SevenSEG_config.h"

void sev_segment_init();
void seven_segment_enable(EN_Enable_segment EN);
void seven_segment_Disable(EN_Enable_segment EN);
void seven_segment_write_NO(uint8 No);
void two_sev_seg(uint8 No);



#endif /* SEVENSEG_H_ */