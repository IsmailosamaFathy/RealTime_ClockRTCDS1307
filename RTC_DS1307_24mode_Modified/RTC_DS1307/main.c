/*
 * RTC_DS1307.c
 *
 * Created: 10/28/2020 5:08:52 PM
 * Author : hp
 */ 

#include "Display.h"

int main(void)
{
    /* Replace with your application code */
	Display_Init();
	
    while (1) 
    {
		
		
           Dispaly_Update();
		
    }
}

