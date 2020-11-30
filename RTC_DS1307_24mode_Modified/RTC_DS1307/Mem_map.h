/*
 * Mem_map.h
 *
 * Created: 9/18/2020 1:40:45 PM
 *  Author: hp
 */ 


#ifndef MEM_MAP_H_
#define MEM_MAP_H_

#include "Ports_comman_ins.h"
#include "data_types.h"


#define Base_A 0x39
#define Base_B 0x36
#define Base_C 0x33
#define Base_D 0x30

#define OUTPUT_OFFEST  2
#define DIRC_OFFEST	   1
#define INTPUT_OFFEST  0


/*******************************GPIO********************************/


#define  DDRA   Acess_REG_8bit ((Base_A+DIRC_OFFEST))
#define  PORTA  Acess_REG_8bit ((Base_A+OUTPUT_OFFEST))
#define  PINA   Acess_REG_8bit ((Base_A+INTPUT_OFFEST))


#define  DDRC   Acess_REG_8bit ((Base_C+DIRC_OFFEST))
#define  PORTC  Acess_REG_8bit ((Base_C+OUTPUT_OFFEST))
#define  PINC   Acess_REG_8bit ((Base_C+INTPUT_OFFEST))

#define  DDRD   Acess_REG_8bit ((Base_D+DIRC_OFFEST))
#define  PORTD  Acess_REG_8bit ((Base_D+OUTPUT_OFFEST))
#define  PIND   Acess_REG_8bit ((Base_D+INTPUT_OFFEST))


#define  DDRB   Acess_REG_8bit ((Base_B+DIRC_OFFEST))
#define  PORTB  Acess_REG_8bit ((Base_B+OUTPUT_OFFEST))
#define  PINB   Acess_REG_8bit ((Base_B+INTPUT_OFFEST))


/****************************ADC**************************/

#define ADC_SFIOR                   Acess_REG_8bit(0x50)

#define ADC_ADUMX                   Acess_REG_8bit(0x27)

#define ADC_ADCSRA                  Acess_REG_8bit(0x26)

#define ADC_ADCH                    Acess_REG_8bit(0x25)

#define ADC_ADCL                    Acess_REG_8bit(0x24)

#define ADC                         Acess_REG_16bit(0x24)

/* ADCSRA */
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

/* ADMUX */
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0


/*External Interrupt */
#define MCUCSR   (*(volatile unsigned char*)0x54)
#define ISC2 6

#define MCUCR   (*(volatile unsigned char*)0x55)
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define GICR     (*(volatile unsigned char*)0x5B)
#define INT1 7
#define INT0 6
#define INT2 5

#define GIFR    (*(volatile unsigned char*)0x5A)
#define INTF1 7
#define INTF0 6
#define INTF2 5


/*********************************************************************************/
/* Interrupt vectors */
/* External Interrupt Request 0 */
#define INT0_vect			__vector_1
/* External Interrupt Request 1 */
#define INT1_vect			__vector_2
/* External Interrupt Request 2 */
#define INT2_vect			__vector_3
/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect		__vector_4
/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect			__vector_5
/* Timer/Counter1 Capture Event */
#define TIMER1_ICU_vect		__vector_6
/* Timer/Counter1 Compare Match A */
#define TIMER1_OCA_vect		__vector_7
/* Timer/Counter1 Compare Match B */
#define TIMER1_OCB_vect		__vector_8
/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect			__vector_9
/* Timer/Counter0 Compare Match */
#define TIMER0_OC_vect		__vector_10
/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect			__vector_11
/* Serial Transfer Complete */
#define SPI_STC_vect			__vector_12
/* USART, Rx Complete */
#define UART_RX_vect			__vector_13
/* USART Data Register Empty */
#define UART_UDRE_vect			__vector_14
/* USART, Tx Complete */
#define UART_TX_vect			__vector_15
/* ADC Conversion Complete */
#define ADC_vect			   __vector_16
/* EEPROM Ready */
#define EE_RDY_vect			   __vector_17
/* Analog Comparator */
#define ANA_COMP_vect			__vector_18
/* 2-wire Serial Interface */
#define TWI_vect			    __vector_19
/* Store Program Memory Ready */
#define SPM_RDY_vect			__vector_20

#  define BAD_vect __vector_default

/*interrupt functions*/

# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)
# define reti()  __asm__ __volatile__ ("reti" ::)
# define ret()  __asm__ __volatile__ ("ret" ::)

#  define ISR_NOBLOCK    __attribute__((interrupt))
#  define ISR_NAKED      __attribute__((naked))


#define GLOBAL_INTERUPT_ENABLE       sei()
#define GLOBAL_INTERUPT_DISABLE       cli()


#  define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)

/*********************TIMERS***************************/

/**********************TIMER0****************************************/
#define Clear_Register    0x00


#define Timer0_TCCR0     Acess_REG_8bit(0x53)

#define Timer0_TCNT0     Acess_REG_8bit(0x52)

#define Timer0_OCR0      Acess_REG_8bit(0x5C)

#define Timsk     Acess_REG_8bit(0x59)

#define TIMER0_TIFR      Acess_REG_8bit((0x58))

/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0













/************************TIMER1*********************************************/


#define Timer1_TCCR1A      Acess_REG_8bit(0x4F)

#define Timer1_TCCR1B      Acess_REG_8bit(0x4E)



#define Timer1_TCNT1      Acess_REG_16bit(0x4C)

#define Timer1_TCNT1L      Acess_REG_8bit(0x4C)

#define Timer1_TCNT1H      Acess_REG_8bit(0x4D)



#define Timer1_OCR1A      Acess_REG_16bit(0x4A)

#define Timer1_OCR1AL      Acess_REG_8bit(0x4A)

#define Timer1_OCR1AH      Acess_REG_8bit(0x4B)



#define Timer1_OCR1B      Acess_REG_16bit(0x48)

#define Timer1_OCR1BL      Acess_REG_8bit(0x48)

#define Timer1_OCR1BH      Acess_REG_8bit(0x49)


#define TIMER1_ICR1           Acess_REG_16bit((0x46))

#define TIMER1_ICRL           Acess_REG_8bit((0x46))


#define TIMER1_ICRH	           Acess_REG_8bit((0x47))
/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0




/***********************************TIMER2**********************************************/


#define Timer2_TCCR2       Acess_REG_8bit(0x45)

#define Timer2_TCNT2       Acess_REG_8bit(0x44)

#define Timer2_OCR2        Acess_REG_8bit(0x43)

/* TCCR2 */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0












#endif /* MEM_MAP_H_ */