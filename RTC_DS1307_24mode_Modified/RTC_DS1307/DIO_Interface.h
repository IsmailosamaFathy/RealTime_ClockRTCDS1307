/*
 * DIO_Interface.h
 *
 * Created: 9/23/2020 7:44:20 PM
 *  Author: hp
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "data_types.h"
#include "Mem_map.h"
#include "Ports_comman_ins.h"

typedef enum{
	PINA0=0,
	PINA1=1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
}DIO_Pin_type;

typedef enum{
	OUTPUT,
	INFREE,
	INLLUP
}DIO_PinStatus_type;

typedef enum{
	PA=0,
	PB,
	PC,
	PD
}DIO_Port_type;

typedef enum{
	LOW=0,
	HIGH
	
}Logic_State;


// PIN FUUNC
extern void Pin_Init(DIO_Pin_type pin,DIO_PinStatus_type status);

extern void Set_Pin(DIO_Pin_type pin,Logic_State state);

extern Logic_State Get_Pin_state(DIO_Pin_type pin);

extern void Toggle_Pin(DIO_Pin_type pin);

// PORT FUNC
extern void Port_Init(DIO_Port_type port,uint8 value);

extern void Set_Port(DIO_Port_type port ,uint8 value);

extern uint8 Get_Port_state(DIO_Port_type port);





#endif /* DIO_INTERFACE_H_ */