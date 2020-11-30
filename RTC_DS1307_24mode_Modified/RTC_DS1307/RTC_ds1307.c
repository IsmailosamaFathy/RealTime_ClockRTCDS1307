/*
 * RTC_ds1307.c
 *
 * Created: 10/28/2020 5:26:06 PM
 *  Author: hp
 */
#include "Port_h.h"
#include "DIO_Interface.h" 
#include "I2C.h"
#include "RTC_ds1307.h"
#include "LCD.h"

#define F_CPU 8000000UL							/* Define CPU clock Frequency e.g. here its 8MHz */

#include <math.h>								/* Include math function */

#define SCL_CLK 100000L							/* Define SCL clock frequency */

#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) /* Define bit rate */





#define INITIAL_POSITION                (0)

#define LAST_CLOCK_POSTION              (3)



#define Device_Write_address	0xD0				/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address		0xD1				/* Make LSB bit high of slave address for read operation */

#define SECOND_REG               (0)

#define WEEK_DAY_REG             (3)




static uint8 pRTCArray[MAX_ARRAY_SIZE]={0};

static t_RTC_time RTC_Readings;

static t_Time_Mode state;



static void Convert_BCD(t_RTC_time *ptr)
{
	

     //Time 
	(ptr->Seconds)=(((unsigned char)((ptr->Seconds)/10))<<4)|((unsigned char)((ptr->Seconds)%10));
	 
	(ptr->Minutes)=(((unsigned char)((ptr->Minutes)/10))<<4)|((unsigned char)((ptr->Minutes)%10)); 
	
	(ptr->Hours)=(((unsigned char)((ptr->Hours)/10))<<4)|((unsigned char)((ptr->Hours)%10)); 
	
	//Date
	(ptr->Weekday)=(((unsigned char)((ptr->Weekday)/10))<<4)|((unsigned char)((ptr->Weekday)%10)); 
	
	(ptr->date)=(((unsigned char)((ptr->date)/10))<<4)|((unsigned char)((ptr->date)%10)); 
	
    (ptr->Month)=(((unsigned char)((ptr->Month)/10))<<4)|((unsigned char)((ptr->Month)%10)); 
	
	(ptr->Year)=(((unsigned char)((ptr->Year)/10))<<4)|((unsigned char)((ptr->Year)%10)); 
 
	
}


static uint8 BCD_Decimal(uint8 bcd)
{
	uint8 Decimal;
	Decimal=bcd>>4;
	return(Decimal=Decimal*10+(bcd&=0x0F));
}




	
//=============================================================
// Set time to DS1307 register
//
// Mode  : TIME_MODE_AM, TIME_MODE_PM, TIME_MODE_24H
// Hours : 0-23
// Minutes  : 0-59
// Secs  : 0-59
//=============================================================
	
//=============================================================
// Set date to DS1307 register
//
// weekday : 1-7 (Saturday - Sunday)
// date    : 1-31
// month   : 1-12
// year    : 0-99
//=============================================================	
	

void RTC_DS1307_Init(t_Time_Mode mod,t_RTC_time *int_Ptr)
{


   Convert_BCD(int_Ptr);

	switch(mod)
	{
		case TIME_MODE_AM:
		
		RTC_Readings.Hours|=0x40;
		
		break;
		
		case TIME_MODE_PM:
		
		RTC_Readings.Hours|=0x60;
		
		break;
		
		case CLK_24_MODE:
		
		
		// DO nothing

		break;		
	}
	
	

	I2C_Start();
	
	I2C_Write(Device_Write_address);
	
	I2C_Write(SECOND_REG);
    
	// Time Date Initial Settings
	I2C_Write(int_Ptr->Seconds);
	
	I2C_Write(int_Ptr->Minutes);
	
	I2C_Write(int_Ptr->Hours);
	
	I2C_Write(int_Ptr->Weekday);
	
	I2C_Write(int_Ptr->date);
	
	I2C_Write(int_Ptr->Month);
	
	I2C_Write(int_Ptr->Year);
	
	I2C_Stop();
	

	
state=mod;
	
}

t_Time_Mode Get_Time_Mode()
{
	t_Time_Mode ret=state;
 return ret;

}




void RTC_DS1307_GetDateTime(t_RTC_time *rtc)
{
	t_RTC_time temp; 
	
	I2C_Start();
	
	I2C_Write(Device_Write_address);
	
	I2C_Write(SECOND_REG);					/* Write address to read */
	I2C_Start();
	I2C_Write(Device_Read_address);
	
	
	(temp.Seconds)= I2C_ReadWithACK();			      			/* Read second */

	(temp.Minutes)= I2C_ReadWithACK();						    /* Read minute */

	(temp.Hours)= I2C_ReadWithNACK();							/* Read hour with Nack */

    



	I2C_Stop();
	/* Stop i2C communication */


	(rtc->Seconds)= BCD_Decimal(temp.Seconds);			      			/* Read second */

	(rtc->Minutes)= BCD_Decimal(temp.Minutes);

	(rtc->Hours)= BCD_Decimal(temp.Hours);							/* Read hour with Nack */

	if ((temp.Hours)&0x40)
	{
		if ((rtc->Hours)&0x20)
		{
			state =TIME_MODE_PM;
		}
		else
		{
			state=TIME_MODE_AM;
		}
		
	}
	else
	{
		state =CLK_24_MODE;
	}
	
	

	
	I2C_Start();
	
	I2C_Write(Device_Write_address);
	
	I2C_Write(WEEK_DAY_REG);					/* Write address to read */
	I2C_Start();
	I2C_Write(Device_Read_address);

	temp.Weekday= I2C_ReadWithACK();						/* Read second */
	temp.date= I2C_ReadWithACK();						/* Read second */
	temp.Month = I2C_ReadWithACK();						/* Read minute */
	temp.Year = I2C_ReadWithNACK();							/* Read hour with Nack */

	(rtc->Weekday)= BCD_Decimal(temp.Weekday);						/* Read second */
	(rtc->date)= BCD_Decimal(temp.date);						/* Read second */
	(rtc->Month) = BCD_Decimal(temp.Month);						/* Read minute */
	(rtc->Year) = BCD_Decimal(temp.Year);							/* Read hour with Nack */
	I2C_Stop();										/* Stop i2C communication */
	
}