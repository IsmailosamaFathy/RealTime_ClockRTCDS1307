/*
 * Port_h.h
 *
 * Created: 9/27/2020 8:08:04 PM
 *  Author: hp
 */ 


#ifndef PORT_H_H_
#define PORT_H_H_

#include "DIO_Interface.h"



// Board_Clock
#define F_CPU 8000000UL


/*****************PUSH_BUTTON***********************/

#define BACK_BUTTON                    (PINA0)


#define SET_BUTTON                     (PINA1)


#define PLUS_BUTTON                    (PINA2)


#define MINUS_BUTTON                   (PINA3)


/**********************LCD************************/

#define LCD_DATA_DIRC           PB

#define LCD_DATA_PORT           PB

#define EN          PIND0 

#define RS          PIND1

/***********************END_LCD********************************/




/*******************I2C_PINS*********************************/

#define SCL_PIN                   (PINC0)

#define SDA_PIN                   (PINC1)

/*******************TEST_CODE**********************************/

#define TEST_LED1                  (PINA0)

#define TEST_LED2                  (PINA1)

#define TEST_LED3                  (PINA2)

#define TEST_LED4                  (PINA3)

#endif /* PORT_H_H_ */