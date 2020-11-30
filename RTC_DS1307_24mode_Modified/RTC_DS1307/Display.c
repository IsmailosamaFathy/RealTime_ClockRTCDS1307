/*
 * Display.c
 *
 * Created: 11/8/2020 1:12:55 AM
 *  Author: hp
 */ 
#define F_CPU       8000000UL
#include "DIO_Interface.h"
#include "RTC_ds1307.h"
#include <util/delay.h>
#include "LCD.h"
#include "Port_h.h"
#include "PB.h"

static t_RTC_time RTC_time;
static	t_Time_Mode Clk_state;

void Display_Init()
{
	      
	        t_RTC_time Str_Time={0,0,0,1,1,1,20};
	        Pin_Init(SDA_PIN,INFREE);
			Pin_Init(SCL_PIN,INFREE);
			
			PB_Init();
			
			LCD_Init();
			
			PB_Update();
			
			PB_Get_RTC_ARR(&Str_Time);
			
			LCD_Clear();
			
			LCD_Sring("CLK:");
			
	
			RTC_DS1307_Init(CLK_24_MODE,&Str_Time);
}
void Dispaly_Update()
{
			
			_delay_ms(100);
							
           RTC_DS1307_GetDateTime(&RTC_time);
			

			LCD_goto(0,4);
			LCD_Digit_Display(RTC_time.Hours);
			LCD_Chr(':');
			LCD_Digit_Display(RTC_time.Minutes);
			LCD_Chr(':');
			LCD_Digit_Display(RTC_time.Seconds);
			LCD_Sring(" ");
			
			switch(Clk_state)
			{
				case TIME_MODE_AM:
				LCD_Sring("AM");
				break;
				
				case  TIME_MODE_PM:
				LCD_Sring("PM");
				break;
				
				case  CLK_24_MODE:
				// Do nothing
				break;
				
				
			}

			
			LCD_goto(1,0);
			switch(RTC_time.Weekday)
			{
				case Sunday:
				LCD_Sring("Sunday");
				break;
				
				case Monday:
				LCD_Sring("Monday");
				break;
				
				case Tuesday:
				LCD_Sring("Tuesday");
				break;
				
				case Wendsday:
				LCD_Sring("Wendsday");
				break;

				case  Thursday:
				LCD_Sring("Thursday");
				break;
				
				case Friday:
				LCD_Sring("Friday");
				break;
				
				case Saturday:
				LCD_Sring("Saturday");
				break;

			}
			LCD_goto(1,8);
			LCD_Digit_Display(RTC_time.date);
			LCD_Chr('/');
			LCD_Digit_Display(RTC_time.Month);
			LCD_Chr('/');
			LCD_Digit_Display(RTC_time.Year);
			



}