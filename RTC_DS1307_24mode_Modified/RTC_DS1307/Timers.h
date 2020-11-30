/*
 * Timers.h
 *
 * Created: 10/24/2020 2:52:47 PM
 *  Author: hp
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_





#include "data_types.h"




typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}Timer0Mode_type;
typedef enum
{
	OCO_DISCONNECTED=0,
	OCO_TOGGLE,
	OCO_NON_INVERTING,
	OCO_INVERTING

}OC0Mode_type;


typedef enum
{
	NO_CLK_SRC,          //Timer Disable
	NO_PRESCALING,
	PRESCALING_CLK8,
	PRESCALING_CLK64,
	PRESCALING_CLK256,
	PRESCALING_CLK1024,
	EXT_CLK_FALLING,
	EXT_CLK_RISING
}clk_selectType;

typedef enum
{
	TIMER0_OVF_INT_ENABLE=0,
	TIMER0_OVF_INT_DISABLE
}INT_OVF_Status;


typedef enum
{
	TIMER0_CTC_INT_ENABLE=0,
	TIMER0_CTC_DISABLE
}INT_CTC_Status;


void Timer0_Init(Timer0Mode_type Timer_mode,clk_selectType clk,OC0Mode_type Oc_Mode);


void Timer0_OVF_Interrupt_Status(INT_OVF_Status state);

void Timer0_CTC_Interrupt_Status(INT_CTC_Status state);




void Timer0_OVF_Set_Call_Back(void(*ptr_call_back)(void));

void Timer0_CTC_Set_Call_Back(void(*ptr_call_back)(void));



/**********************myfunc*********************************/

void Timer0_Set_Compare_Value(uint8 value);

void Timer0_Set_OVF_Value(uint8 value);

void Timer0_GETCounter_Value(uint8 *numticks);



void Timer0_Get_Tov_Number(uint8 *tov_number);

void Timer0_Get_Ticks_Of_Sw_Counter(uint16 *counter);















/*******************************TIMER1*****************************************************/
typedef enum
{
		TIMER1_NO_CLK_SRC=0,          //Timer Disable
		TIMER1_NO_PRESCALING,
		TIMER1_PRESCALING_CLK8,
		TIMER1_PRESCALING_CLK64,
		TIMER1_PRESCALING_CLK256,
		TIMER1_PRESCALING_CLK1024,
		TIMER1_EXT_CLK_FALLING,
		TIMER1_EXT_CLK_RISING
}Timer1_CLK_Select;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE

}Timer1Mode_type;




typedef enum
{
	OC1RA_DISCONNECTED=0,
	OC1RA_TOGGLE,
	OC1RA_NON_INVERTING,
	OC1RA_INVERTING

}OC1RAMode_type;



typedef enum
{
	OC1RB_DISCONNECTED=0,
	OC1RB_TOGGLE,
	OC1RB_NON_INVERTING,
	OC1RB_INVERTING

}OC1RBMode_type;



typedef enum
{
FALLING_EDGE=0,	
RISIING_EDGE	
}ICR_Edge_Select;

typedef enum
{
	TIMER1_ICR1_INT_ENABLE,
    TIMER1_ICR1_INT_DISABLE,
}TIMER1_INT_ICR1_State;

typedef enum
{
	TIMER1_CTC_OC1RA_INT_ENABLE,
	TIMER1_CTC_OC1RA_INT_DISABLE,
}TIMER1_INT_CTC_OC1RA_State;


typedef enum
{
	TIMER1_CTC_OC1RB_INT_ENABLE,
	TIMER1_CTC_OC1RB_INT_DISABLE,
}TIMER1_INT_CTC_OC1RB_State;

typedef enum
{
	TIMER1_OVF_INT_ENABLE,
	TIMER1_OVF_INT_DISABLE,
}TIMER1_INT_OVF_State;






void Timer1_Init(Timer1Mode_type mod,Timer1_CLK_Select clk,OC1RAMode_type OC1A_mode,OC1RBMode_type OC1B_mode );

void Timer1_ICR1_Edge_Select(ICR_Edge_Select select);

void Timer1_Set_ICR_REG(uint16 reg);


void Timer1_Set_OCR1A_Top(uint16 value);

void Timer1_Set_ICR_Top(uint16 value);

void Timer1_OCR1B_REG(uint16 VALUE);

uint16 Timer1_Get_OCR1A_Top();

uint16 Timer1_Get_ICR_Top();

//INT_FUNC

void Timer1_ICU_Interrupt_State(TIMER1_INT_ICR1_State state);

void Timer1_CTC_OCR1A_Interrupt_State(TIMER1_INT_CTC_OC1RA_State state);

void Timer1_CTC_OCR1B_Interrupt_State(TIMER1_INT_CTC_OC1RB_State state);

void Timer1_OVF_Interrupt_State(TIMER1_INT_OVF_State state);

// Set_Call_Back

void Timer1_OVF_Set_Call_Back(ptr_call_back Ovf_Func);


void Timer1_CTC_OC1RA_Set_Call_Back(ptr_call_back CTC_OC1RA_Func);


void Timer1_CTC_OC1RB_Set_Call_Back(ptr_call_back CTC_OC1RB_Func);


void Timer1_ICU_Set_Call_Back(ptr_call_back ICU_Func);



















#endif /* TIMERS_H_ */