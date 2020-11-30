/*
 * PB.h
 *
 * Created: 11/10/2020 3:04:34 PM
 *  Author: hp
 */ 


#ifndef PB_H_
#define PB_H_

#include "data_types.h"
#include "RTC_ds1307.h"
void PB_Init();

void PB_Update();

void PB_Get_RTC_ARR(t_RTC_time *parr);


#endif /* PB_H_ */