/*
 * DIO.c
 *
 * Created: 9/23/2020 7:43:32 PM
 *  Author: hp
 */ 
#include "DIO_Interface.h"
extern void Pin_Init(DIO_Pin_type pin,DIO_PinStatus_type status )
{
	DIO_Port_type Port=pin/8;
	uint8 pin_num=pin%8;
  switch(status)
  {
	  case OUTPUT:
	  switch(Port)
	  {
		  case (PA):
		  Set_BIT(DDRA,pin_num);
		  break;
		  case (PB):
		  Set_BIT(DDRB,pin_num);
		  break;
		  case (PD):
		  Set_BIT(DDRD,pin_num);
		  break;
		  case (PC):
		  Set_BIT(DDRC,pin_num);
		  break;
	  }
	  break;
	  case INLLUP:
	  	  switch(Port)
	  	  {
		  	  case (PA):
			  CLEAR_BIT(DDRA,pin_num);
		  	  Set_BIT(PORTA,pin_num);
		  	  break;
		  	  case (PB):
			  CLEAR_BIT(DDRB,pin_num);
		  	  Set_BIT(PORTB,pin_num);
		  	  break;
		  	  case (PD):
			  CLEAR_BIT(DDRD,pin_num);
		  	  Set_BIT(PORTD,pin_num);
		  	  break;
		  	  case (PC):
			  CLEAR_BIT(DDRC,pin_num);
		  	  Set_BIT(PORTC,pin_num);
		  	  break;
	  	  }
	  	  break;
	  case INFREE:
	  switch(Port)
	  {
		  case (PA):
		  CLEAR_BIT(DDRA,pin_num);
		  CLEAR_BIT(PORTA,pin_num);
		  break;
		  case (PB):
		  CLEAR_BIT(DDRB,pin_num);
		  CLEAR_BIT(PORTB,pin_num);
		  break;
		  case (PD):
		  CLEAR_BIT(DDRD,pin_num);
		  CLEAR_BIT(PORTD,pin_num);
		  break;
		  case (PC):
		  CLEAR_BIT(DDRC,pin_num);
		  CLEAR_BIT(PORTC,pin_num);
		  break;
	  }
	  break;			



  }


}
extern void Set_Pin(DIO_Pin_type pin,Logic_State state)
{
	DIO_Port_type Port=pin/8;
	uint8 pin_num=pin%8;
		  switch(Port)
		  {
			  case (PA):
			  SET_REGISTER_PIN(PORTA,pin_num,state);
			  break;
			  case (PB):
			  SET_REGISTER_PIN(PORTB,pin_num,state);
			  break;
			  case (PD):
			  SET_REGISTER_PIN(PORTD,pin_num,state);
			  break;
			  case (PC):
			  SET_REGISTER_PIN(PORTC,pin_num,state);
			  break;
		  }
	
}
extern Logic_State Get_Pin_state(DIO_Pin_type pin)
{
	Logic_State ret=LOW;
    DIO_Port_type Port=pin/8;
	uint8 pin_num=pin%8;
	switch(Port)
		{
			case (PA):
			ret =READ_BIT(PINA,pin_num);
			break;
			case (PB):
			 ret=READ_BIT(PINB,pin_num);
			break;
			case (PD):
			ret=READ_BIT(PIND,pin_num);
			break;
			case (PC):
			ret=READ_BIT(PINC,pin_num);
			break;
		}
	
	
	return ret;
}
extern void Toggle_Pin(DIO_Pin_type pin)
{
		DIO_Port_type Port=pin/8;
		uint8 pin_num=pin%8;
		switch(Port)
		{
			case (PA):
			Toggl_BIT(PORTA,pin_num);
			break;
			case (PB):
			Toggl_BIT(PORTB,pin_num);
			break;
			case (PD):
			Toggl_BIT(PORTD,pin_num);
			break;
			case (PC):
			Toggl_BIT(PORTC,pin_num);
			break;
		}
	
	
	
	
}
// PORT FUNC
extern void Port_Init(DIO_Port_type port,uint8 value)
{
	switch(port)
	{
		case (PA):
		PUT_VALUE_8bit(DDRA,value);
		break;
		case (PB):
		PUT_VALUE_8bit(DDRB,value);
		break;
		case (PC):
		PUT_VALUE_8bit(DDRC,value);
		break;		
		case (PD):
		PUT_VALUE_8bit(DDRD,value);
		break;		
		
	}
	
}
extern void Set_Port(DIO_Port_type port ,uint8 value)
{
		switch(port)
		{
			case (PA):
			PUT_VALUE_8bit(PORTA,value);
			break;
			case (PB):
			PUT_VALUE_8bit(PORTB,value);
			break;
			case (PC):
			PUT_VALUE_8bit(PORTC,value);
			break;
			case (PD):
			PUT_VALUE_8bit(PORTD,value);
			break;
			
		}
	
	

	
}

extern uint8 Get_Port_state(DIO_Port_type port)
{
	uint8 ret=0;
	switch(port)
	{
		case (PA):
		ret=PINA;
		break;
		
		case (PB):
		ret=PINB;
		break;
		
		case (PC):
		ret=PINC;
		break;	
			
		case (PD):
		ret=PIND;
		break;		
	}
	
	
	return ret;
	
	
}
extern void DIO_Init(void);

