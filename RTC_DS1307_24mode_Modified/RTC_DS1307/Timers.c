/*
 * Timers.c
 *
 * Created: 10/24/2020 2:53:16 PM
 *  Author: hp
 */ 
#include "Mem_map.h"
#include "Timers.h"

#define TIMER0_PTR_CALL_BACK_FUNC       (2)

#define TIMER1_PTR_CALL_BACK_FUNC       (4)
/*
#define OVF_CallFUNC_Back               (0)

#define CTC_OCR1A_FUNC                  (1)

#define CTC_OCR1A_FUNC                  (2)

#define ICU_FUNC                        (3)
*/




static void(*Timer0_ptr_Func[TIMER0_PTR_CALL_BACK_FUNC])(void)={NULL_PTR,NULL_PTR};
	
static void(*Timer1_ptr_Func[TIMER1_PTR_CALL_BACK_FUNC])(void)={NULL_PTR};	

static uint16 Timer_Counter=0;

void Timer0_Init(Timer0Mode_type Timer_mode,clk_selectType clk,OC0Mode_type Oc_Mode)
{
	switch(Timer_mode)
	{
		case   (TIMER0_NORMAL_MODE):
		CLEAR_BIT(Timer0_TCCR0,WGM00);
		CLEAR_BIT(Timer0_TCCR0,WGM01);
		break;
		
		case   (TIMER0_PHASECORRECT_MODE):
		Set_BIT(Timer0_TCCR0,WGM00);
		CLEAR_BIT(Timer0_TCCR0,WGM01);
		break;
		
		case   (TIMER0_CTC_MODE):
		CLEAR_BIT(Timer0_TCCR0,WGM00);
		Set_BIT(Timer0_TCCR0,WGM01);
		break;
		
		case    (TIMER0_FASTPWM_MODE):
		Set_BIT(Timer0_TCCR0,WGM00);
		Set_BIT(Timer0_TCCR0,WGM01);
		break;
	}
	
	switch(Oc_Mode)
	{
		case  OCO_DISCONNECTED:
		CLEAR_BIT(Timer0_TCCR0,COM00);
		CLEAR_BIT(Timer0_TCCR0,COM01);
		break;
		case OCO_TOGGLE:
		Set_BIT(Timer0_TCCR0,COM00);
		CLEAR_BIT(Timer0_TCCR0,COM01);
		break;
		case OCO_NON_INVERTING:
		CLEAR_BIT(Timer0_TCCR0,COM00);
		Set_BIT(Timer0_TCCR0,COM01);
		break;
		case OCO_INVERTING:
		Set_BIT(Timer0_TCCR0,COM00);
		Set_BIT(Timer0_TCCR0,COM01);
		break;
		
		
	}
	
	switch(clk)
	{
		case (NO_CLK_SRC)://Timer Disable
		CLEAR_BIT(Timer0_TCCR0,CS00);
		CLEAR_BIT(Timer0_TCCR0,CS01);
		CLEAR_BIT(Timer0_TCCR0,CS02);
		break;
		case (NO_PRESCALING):
		Set_BIT(Timer0_TCCR0,CS00);
		CLEAR_BIT(Timer0_TCCR0,CS01);
		CLEAR_BIT(Timer0_TCCR0,CS02);
		break;
		case (PRESCALING_CLK8):
		CLEAR_BIT(Timer0_TCCR0,CS00);
		Set_BIT(Timer0_TCCR0,CS01);
		CLEAR_BIT(Timer0_TCCR0,CS02);
		break;
		case (PRESCALING_CLK64):
		Set_BIT(Timer0_TCCR0,CS00);
		Set_BIT(Timer0_TCCR0,CS01);
		CLEAR_BIT(Timer0_TCCR0,CS02);
		break;
		case (PRESCALING_CLK256):
		CLEAR_BIT(Timer0_TCCR0,CS00);
		CLEAR_BIT(Timer0_TCCR0,CS01);
		Set_BIT(Timer0_TCCR0,CS02);
		break;
		case(PRESCALING_CLK1024):
		Set_BIT(Timer0_TCCR0,CS00);
		CLEAR_BIT(Timer0_TCCR0,CS01);
		Set_BIT(Timer0_TCCR0,CS02);
		break;
		case(EXT_CLK_FALLING):
		CLEAR_BIT(Timer0_TCCR0,CS00);
		Set_BIT(Timer0_TCCR0,CS01);
		Set_BIT(Timer0_TCCR0,CS02);
		break;
		case(EXT_CLK_RISING):
		Set_BIT(Timer0_TCCR0,CS00);
		Set_BIT(Timer0_TCCR0,CS01);
		Set_BIT(Timer0_TCCR0,CS02);
		break;
		
	}
}


void Timer0_OVF_Interrupt_Status(INT_OVF_Status state)
{
	
	switch(state)
	{
		case(TIMER0_OVF_INT_ENABLE):
		Set_BIT(Timsk,TOIE0);
		break;
		
		case (TIMER0_OVF_INT_DISABLE):
		CLEAR_BIT(Timsk,TOIE0);
		break;
		
	}
	
}

void Timer0_CTC_Interrupt_Status(INT_CTC_Status state)
{
	switch(state)
	{
		case TIMER0_CTC_DISABLE:
		
		Set_BIT(Timsk,OCIE0);
		break;
		
		case TIMER0_CTC_INT_ENABLE:
		
		CLEAR_BIT(Timsk,OCIE0);
		break;
	}
	
	
}





void Timer0_Set_Compare_Value(uint8 value)
{
	
	Timer0_OCR0=value;
	
}

void Timer0_Set_OVF_Value(uint8 value)
{
	Timer_Counter=value;
	
}

void Timer0_GETCounter_Value(uint8 *numticks)
{
	
	*numticks=Timer0_TCNT0;

}

void Timer0_Get_Tov_Number(uint8 *tov_number)
{
	*tov_number=Timer_Counter;
}

void Timer0_Get_Ticks_Of_Sw_Counter(uint16 *counter)
{
	*counter=(256*Timer_Counter)+Timer0_TCNT0;
}


void Timer0_OVF_Set_Call_Back(void(*ptr_call_back)(void))
{
	Timer0_ptr_Func[0]=ptr_call_back;
}

void Timer0_CTC_Set_Call_Back(void(*ptr_call_back)(void))
{

	Timer0_ptr_Func[1]=ptr_call_back;

}
ISR(TIMER0_OVF_vect)
{
	if (Timer0_ptr_Func[0]!=NULL_PTR)
	{
		Timer0_ptr_Func[0]();
		Timer_Counter++;
	}
	
}
ISR(TIMER0_OC_vect)
{
	if (Timer0_ptr_Func[1]!=NULL_PTR)
	{
		Timer0_ptr_Func[1]();
	}

}
/*******************************TIMER1********************************************/






void Timer1_Init(Timer1Mode_type mod,Timer1_CLK_Select clk,OC1RAMode_type OC1A_mode,OC1RBMode_type OC1B_mode )
{
	
	switch(mod)
	{
			case  TIMER1_NORMAL_MODE:
			CLEAR_BIT(Timer1_TCCR1A,WGM10);
			CLEAR_BIT(Timer1_TCCR1A,WGM11);
			CLEAR_BIT(Timer1_TCCR1B,WGM12);
			CLEAR_BIT(Timer1_TCCR1B,WGM13);
			break;
			
			case  TIMER1_CTC_ICR_TOP_MODE:
			CLEAR_BIT(Timer1_TCCR1A,WGM10);
			CLEAR_BIT(Timer1_TCCR1A,WGM11);
			Set_BIT(Timer1_TCCR1B,WGM12);
			Set_BIT(Timer1_TCCR1B,WGM13);			
			break;
			
			case  TIMER1_CTC_OCRA_TOP_MODE:
			CLEAR_BIT(Timer1_TCCR1A,WGM10);
			CLEAR_BIT(Timer1_TCCR1A,WGM11);
			Set_BIT(Timer1_TCCR1B,WGM12);
			CLEAR_BIT(Timer1_TCCR1B,WGM13);		
			break;
			
			case  TIMER1_FASTPWM_ICR_TOP_MODE:
			CLEAR_BIT(Timer1_TCCR1A,WGM10);
			Set_BIT(Timer1_TCCR1A,WGM11);
			Set_BIT(Timer1_TCCR1B,WGM12);
			Set_BIT(Timer1_TCCR1B,WGM13);	
			break;
			
			case  TIMER1_FASTPWM_OCRA_TOP_MODE:
			Set_BIT(Timer1_TCCR1A,WGM10);
			Set_BIT(Timer1_TCCR1A,WGM11);
			Set_BIT(Timer1_TCCR1B,WGM12);
			Set_BIT(Timer1_TCCR1B,WGM13);		
			break;
	}
	switch(OC1B_mode)
	{
			case  OC1RB_DISCONNECTED:
		     CLEAR_BIT(Timer1_TCCR1A,COM1B0);
		     CLEAR_BIT(Timer1_TCCR1A,COM1B1);
			break;
			case OC1RB_TOGGLE:
			Set_BIT(Timer1_TCCR1A,COM1B0);
			CLEAR_BIT(Timer1_TCCR1A,COM1B1);		
			break;
			
			case OC1RB_NON_INVERTING:
			CLEAR_BIT(Timer1_TCCR1A,COM1B0);
		    Set_BIT(Timer1_TCCR1A,COM1B1);		
			break;
		 	
			 
			case OC1RB_INVERTING:
			Set_BIT(Timer1_TCCR1A,COM1B0);
			Set_BIT(Timer1_TCCR1A,COM1B1);		
			break;
	
	}
	switch(OC1A_mode)
	{
			case OC1RA_DISCONNECTED:
			
	      		CLEAR_BIT(Timer1_TCCR1A,COM1A0);
	      		CLEAR_BIT(Timer1_TCCR1A,COM1A1);		
			
			break;
			
			case OC1RA_TOGGLE:
	      		Set_BIT(Timer1_TCCR1A,COM1A0);
	      		CLEAR_BIT(Timer1_TCCR1A,COM1A1);		
			
			break;
			case OC1RA_NON_INVERTING:
		      	CLEAR_BIT(Timer1_TCCR1A,COM1A0);
		      	Set_BIT(Timer1_TCCR1A,COM1A1);	
			break;
			
			case OC1RA_INVERTING:
		      Set_BIT(Timer1_TCCR1A,COM1A0);
		      Set_BIT(Timer1_TCCR1A,COM1A1);	
			
			break;
	}
	
	
		switch(clk)
		{
			case (TIMER1_NO_CLK_SRC)://Timer Disable
			CLEAR_BIT(Timer1_TCCR1B,CS10);
			CLEAR_BIT(Timer1_TCCR1B,CS11);
			CLEAR_BIT(Timer1_TCCR1B,CS12);
			break;
			case (TIMER1_NO_PRESCALING):
			Set_BIT(Timer1_TCCR1B,CS10);
			CLEAR_BIT(Timer1_TCCR1B,CS11);
			CLEAR_BIT(Timer1_TCCR1B,CS12);
			break;
			case (TIMER1_PRESCALING_CLK8):
			CLEAR_BIT(Timer1_TCCR1B,CS10);
			Set_BIT(Timer1_TCCR1B,CS11);
			CLEAR_BIT(Timer1_TCCR1B,CS12);
			break;
			case (TIMER1_PRESCALING_CLK64):
			Set_BIT(Timer1_TCCR1B,CS10);
			Set_BIT(Timer1_TCCR1B,CS11);
			CLEAR_BIT(Timer1_TCCR1B,CS12);
			break;
			case (TIMER1_PRESCALING_CLK256):
			CLEAR_BIT(Timer1_TCCR1B,CS10);
			CLEAR_BIT(Timer1_TCCR1B,CS11);
			Set_BIT(Timer1_TCCR1B,CS12);
			break;
			case(TIMER1_PRESCALING_CLK1024):
			Set_BIT(Timer1_TCCR1B,CS10);
			CLEAR_BIT(Timer1_TCCR1B,CS11);
			Set_BIT(Timer1_TCCR1B,CS12);
			break;
			case(TIMER1_EXT_CLK_FALLING):
			CLEAR_BIT(Timer1_TCCR1B,CS10);
			Set_BIT(Timer1_TCCR1B,CS11);
			Set_BIT(Timer1_TCCR1B,CS12);
			break;
			case(TIMER1_EXT_CLK_RISING):
			Set_BIT(Timer1_TCCR1B,CS10);
			Set_BIT(Timer1_TCCR1B,CS11);
			Set_BIT(Timer1_TCCR1B,CS12);
			break;
			
		}
	
	
	

	
}

void Timer1_ICR1_Edge_Select(ICR_Edge_Select select)
{
	
	switch(select)
	{
		case FALLING_EDGE:
		
		CLEAR_BIT(Timer1_TCCR1B,ICES1);
		
		break;
		
		case RISIING_EDGE:
		
		Set_BIT(Timer1_TCCR1B,ICES1);
		
		break;
	
	
	}
	
}

void Timer1_Set_ICR_REG(uint16 reg)
{
	TIMER1_ICR1=reg;
}


//INT_FUNC

void Timer1_ICU_Interrupt_State(TIMER1_INT_ICR1_State state)
{
	
	switch(state)
	{
			case  TIMER1_ICR1_INT_ENABLE:
			Set_BIT(Timsk,TICIE1);
			break;
			
		    case TIMER1_ICR1_INT_DISABLE:
			CLEAR_BIT(Timsk,TICIE1);
			break;
		
	}


}


void Timer1_CTC_OCR1A_Interrupt_State(TIMER1_INT_CTC_OC1RA_State state)
{
	switch(state)
	{
	case TIMER1_CTC_OC1RA_INT_ENABLE:
	
	Set_BIT(Timsk,OCIE1A);
	
	break;
	
	case TIMER1_CTC_OC1RA_INT_DISABLE:
	
	CLEAR_BIT(Timsk,OCIE1A);
	
	break;
	}




}

void Timer1_CTC_OCR1B_Interrupt_State(TIMER1_INT_CTC_OC1RB_State state)
{
		switch(state)
		{
			case TIMER1_CTC_OC1RB_INT_ENABLE:
			
			Set_BIT(Timsk,OCIE1B);
			
			break;
			
			case TIMER1_CTC_OC1RB_INT_DISABLE:
			
			CLEAR_BIT(Timsk,OCIE1B);
			
			break;
		}


}

void Timer1_OVF_Interrupt_State(TIMER1_INT_OVF_State state)
{
		switch(state)
		{
			case TIMER1_OVF_INT_ENABLE:
			
			Set_BIT(Timsk,TOIE1);
			
			break;
			
			case TIMER1_OVF_INT_DISABLE:
			
			CLEAR_BIT(Timsk,TOIE1);
			
			break;
		}
	
	
	
}

// Set_Call_Back

void Timer1_OVF_Set_Call_Back(ptr_call_back Ovf_Func)
{
	Timer1_ptr_Func[0]=Ovf_Func;
}


void Timer1_CTC_OC1RA_Set_Call_Back(ptr_call_back CTC_OC1RA_Func)
{
	
	Timer1_ptr_Func[1]=CTC_OC1RA_Func;
	
}


void Timer1_CTC_OC1RB_Set_Call_Back(ptr_call_back CTC_OC1RB_Func)
{
        Timer1_ptr_Func[2]=CTC_OC1RB_Func;
}


void Timer1_ICU_Set_Call_Back(ptr_call_back ICU_Func)
{
	Timer1_ptr_Func[3]=ICU_Func;
}

void Timer1_Set_OCR1A_Top(uint16 value)
{
	if (value!=0)
	{
		Timer1_OCR1A=value-1;
	}
	
}

void Timer1_Set_ICR_Top(uint16 value)
{
	if (value!=0)
	{
		TIMER1_ICR1=value-1;	
	}
	
}

void Timer1_OCR1B_REG(uint16 VALUE)
{
	Timer1_OCR1B=VALUE-1;
	
}
uint16 Timer1_Get_OCR1A_Top()
{
	return TIMER1_ICR1;
	
}

uint16 Timer1_Get_ICR_Top()
{
	return TIMER1_ICR1;
	
}

ISR(TIMER1_OVF_vect)
{
	if(Timer1_ptr_Func[0]!=NULL_PTR)
	{
		Timer1_ptr_Func[0]();
	}


}


ISR(TIMER1_OCA_vect)
{
	if(Timer1_ptr_Func[1]!=NULL_PTR)
	{
		Timer1_ptr_Func[1]();
	}


}



ISR(TIMER1_OCB_vect)
{
	if(Timer1_ptr_Func[2]!=NULL_PTR)
	{
		Timer1_ptr_Func[2]();
	}


}

ISR(TIMER1_ICU_vect)
{
	if(Timer1_ptr_Func[3]!=NULL_PTR)
	{
		Timer1_ptr_Func[3]();
	}
}



















