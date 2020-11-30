/*
 * LCD.h
 *
 * Created: 9/28/2020 6:58:16 PM
 *  Author: hp
 */ 


#ifndef LCD_H_
#define LCD_H_


#include "DIO_Interface.h"
#include "LCD_Pcfg.h"





void LCD_Init();

void LCD_Chr(uint8 data);

void LCD_Sring(uint8 *str);

void LCD_Num_Binary(uint8 data);

void LCD_Number(uint64 num);

void LCD_goto(uint8 row,uint8 col);

void LCD_Digit_Display(uint16 num);

void LCD_Clear();




#endif /* LCD_H_ */