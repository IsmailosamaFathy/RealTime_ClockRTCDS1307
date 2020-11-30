/*
 * LCD.c
 *
 * Created: 9/28/2020 6:58:25 PM
 *  Author: hp
 */ 


#include "LCD.h"
#include "Port_h.h"

#include <util/delay.h>


/*commands*/

#define ENTRY_MODE   0x06
#define CLEAR_SCREEN 0x01
#define BIT_4        0x28
#define BIT_8        0x38
#define CURSOR_BLINK 0x0f
#define CURSOR_ON    0x0e
#define CURSOR_OFF   0x0c
#define DISPLAY_OFF  0x08
#define RETURN_HOME  0x02

static void LCD_Cmd(uint8 command);

static void Kick()
{
	Set_Pin(EN,HIGH);
	
	_delay_ms(1);
	
	Set_Pin(EN,LOW);
	
	_delay_ms(2);
}

static void LCD_Cmd(uint8 command)
{
	
	Set_Pin(RS,LOW);
 #if (MOOD==8)

   Set_Port(LCD_DATA_PORT,command);
 
 #else
 /*
 *In Order to work in 4 bit mode in Lm016 (lCD) 16*2
 *First, Send Most Significant bits (command &0xf0)  
 *Then, Send Least Significant bits ((command &0xf0)<<4))
 */
 Set_Port(LCD_DATA_PORT,(command &0xf0));
 
 Kick();
 
 Set_Port(LCD_DATA_PORT,((command &0x0f)<<4)); 
 #endif
	
    Kick();
	
   _delay_ms(2);

}
static void LCD_data(uint8 data)
{
	Set_Pin(RS,HIGH);
	 #if (MOOD==8)

	 Set_Port(LCD_DATA_PORT,data);
	 
	 #else
/*
 *In Order to work in 4 bit mode in Lm016 (lCD) 16*2
 *First, Send Most Significant bits (command &0xf0)  
 *Then, Send Least Significant bits ((command &0xf0)<<4))
*/
	 Set_Port(LCD_DATA_PORT,(0xf0 & data));
	 
	 Kick();
	 
	 Set_Port(LCD_DATA_PORT,((0x0f & data)<<4));
	 
	 #endif	
	
	
     Kick();
 	
	_delay_ms(2);
}





void LCD_Init()
{

	 
	 Pin_Init(EN,OUTPUT);
	 
	 Pin_Init(RS,OUTPUT);
	
	_delay_ms(50);
#if (MOOD==8)

Port_Init(LCD_DATA_DIRC,0xff);
LCD_Cmd(BIT_8);

#else

Port_Init(LCD_DATA_PORT,0xf0);

LCD_Cmd(RETURN_HOME);

LCD_Cmd(0x02);

LCD_Cmd(BIT_4);

#endif
	
	LCD_Cmd(ENTRY_MODE);	
	LCD_Cmd(CURSOR_OFF);
	LCD_Cmd(CLEAR_SCREEN);
	
}





void LCD_Sring(uint8 *str)
{
	while (*str!='\0')
	{
		LCD_data(*str);
	    str++;
	}
	
	
}

void LCD_Number(uint64 num)
{
	uint8 temp[16],i=0;
	uint8 mod;
	
	if (num==0)
	{
		LCD_data('0');
	}
	else if(num<0)
	{
		LCD_Chr(0x2d);
		num=num*-1;
	}
	
		while(num)
		{
			mod=num%10;
			temp[i]=mod;
			num/=10;
			i++;
		}
		
		for (;i>=1;i--)
		{
			LCD_data(temp[i-1]+'0');
		}
		LCD_data(temp[i]);
	
}



void LCD_goto(uint8 row,uint8 col)
{
	if (row==0)
	{
		LCD_Cmd(0x80|col);
	}
	else if (row==1)
	{
		LCD_Cmd(0xc0|col);
	}	
}





void LCD_Digit_Display(uint16 num)
{

    LCD_data( ((num/10)/1)+'0');
   LCD_data( ((num%10))+'0');
  

}



void LCD_Clear()
{
  	LCD_Cmd(CLEAR_SCREEN);
}
void LCD_Chr(uint8 data)
{
	LCD_data(data);
}


void LCD_Num_Binary(uint8 data)
{
	uint8 i;
	for (i=7;i>0;i--)
	{
		if ( (data>>i) & (1) )
		{
			LCD_Chr('1');
		}
		else
		{
               LCD_Chr('0');
		}
		
	}
	if ( (data) & (1>>i) )
		{
				LCD_Chr('1');
		}
		else
		{
		     LCD_Chr('0');
		}
	
	
	
}