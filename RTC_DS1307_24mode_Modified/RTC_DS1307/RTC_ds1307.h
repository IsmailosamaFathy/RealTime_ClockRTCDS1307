/*
 * RTC_ds1307.h
 *
 * Created: 10/28/2020 5:25:41 PM
 *  Author: hp
 */ 


#ifndef RTC_DS1307_H_
#define RTC_DS1307_H_
#include "data_types.h"

#define MAX_ARRAY_SIZE                  (7)

typedef enum
{

 Sunday=1,	
 Monday,
 Tuesday,
 Wendsday,
 Thursday,
 Friday,
 Saturday
}t_days;

typedef enum
{
	TIME_MODE_AM=0x40,
	TIME_MODE_PM=0x60,
	CLK_24_MODE,
  
}t_Time_Mode;

typedef enum
{
	_Seconds=0,
	_Minutes,
	_Hours,
	_Days=3,
	_date,
	_Month,
	_Year,
}t_time;

// We will Work on 24h mode but our driver is generic  
typedef struct
{
	
	uint8 Seconds;
	uint8 Minutes;
	uint8 Hours;
	
	uint8 Weekday;
    uint8 date;
	uint8 Month;
	uint8 Year;
    

}t_RTC_time;




void RTC_DS1307_Init(t_Time_Mode mod,t_RTC_time *int_Ptr);

void RTC_DS1307_GetDateTime(t_RTC_time *rtc);





t_Time_Mode Get_Time_Mode();


#endif /* RTC_DS1307_H_ */