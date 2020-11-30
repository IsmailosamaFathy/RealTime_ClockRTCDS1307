/*
 * PB.c
 *
 * Created: 11/10/2020 3:04:46 PM
 *  Author: hp
 */ 
#include "PB.h"
#include "DIO_Interface.h"
#include "Port_h.h"
#include "LCD.h"

static uint8 PTR_ARR[7]={0,0,0,1,1,1,20}; 
	
typedef enum
{
SET_SECs=0,
SET_MINs,
SET_HOURs,	
SET_DAYs,
SET_DATEs,
SET_MONTHs,
SET_YEARs,	
FINISHED	
}t_Set_state;

static t_Set_state state=SET_SECs;

void PB_Init()
{
	Pin_Init(BACK_BUTTON,INLLUP);
	Pin_Init(SET_BUTTON,INLLUP);
	Pin_Init(PLUS_BUTTON,INLLUP);
	Pin_Init(MINUS_BUTTON,INLLUP);
	
}

void PB_Update()
{
	
	uint8 count[7]={0,0,0,1,1,1,20};;
	LCD_Sring("Seconds");
	LCD_Digit_Display(count[state]);	
	while(state<FINISHED)
	{
		if (!(Get_Pin_state(BACK_BUTTON)))
		{
			while( (!(Get_Pin_state(BACK_BUTTON))) );
			if (state>SET_SECs)
			{
				LCD_Clear();
				state--;
				
			}
			switch(state)
			{
				case SET_SECs:
				LCD_Sring("Second:");
				break;
				case SET_MINs:
				LCD_Sring("MINUTE:");
				break;	
				case SET_HOURs:
				LCD_Sring("HOUR:");
				break;	
				case SET_DAYs:
				LCD_Sring("DAY:");
				break;
				case SET_DATEs:
				LCD_Sring("DATE:");
				break;
				case SET_MONTHs:
				LCD_Sring("MONTH:");
				break;
				case SET_YEARs:
				LCD_Sring("YEAR:");
				break;
				default:
				// Do nothing
				break;				
																				
			}
			if (state==SET_DAYs)
			{
					switch(count[SET_DAYs])
					{
						case (1):
						LCD_Sring("Sunday");
						break;
						
						case (2):
						LCD_Sring("Monday");
						break;
						
						case (3):
						LCD_Sring("Tuesday");
						break;
						
						case (4):
						LCD_Sring("Wendsday");
						break;
						
						case (5):
						LCD_Sring("Thursday");
						break;
						
						case (6):
						LCD_Sring("Friday");
						break;
						case (7):
						LCD_Sring("Saturday");
						break;
						
						
					}
				
			}
			else
			{
	               LCD_Digit_Display(count[state]);
			}
			

			
		}
		
		
		
		else if (!(Get_Pin_state(SET_BUTTON)))
		{
			while( (!(Get_Pin_state(SET_BUTTON)))  );
			if (state<=FINISHED)
			{
			
				LCD_Clear();
				state++;
				switch(state)
				{
					case SET_SECs:
					LCD_Sring("Second:");
					break;
					case SET_MINs:
					LCD_Sring("MINUTE:");
					break;
					case SET_HOURs:
					LCD_Sring("HOUR:");
					break;
					case SET_DAYs:
					LCD_Sring("DAY:");
					break;
					case SET_DATEs:
					LCD_Sring("DATE:");
					break;
					case SET_MONTHs:
					LCD_Sring("MONTH:");
					break;
					case SET_YEARs:
					LCD_Sring("YEAR:");
					break;
					default:
					// Do nothing
					break;
					
				}
			
				if (state==SET_DAYs)
				{
					switch(count[SET_DAYs])
					{
						case (1):
						LCD_Sring("Sunday");
						break;
						
						case (2):
						LCD_Sring("Monday");
						break;
						
						case (3):
						LCD_Sring("Tuesday");
						break;
						
						case (4):
						LCD_Sring("Wendsday");
						break;
						
						case (5):
						LCD_Sring("Thursday");
						break;
						
						case (6):
						LCD_Sring("Friday");
						break;
						case (7):
						LCD_Sring("Saturday");
						break;
						
						
					}
					
				}
				else
				{
					LCD_Digit_Display(count[state]);
				}
						
			}
		}
		
		
		
		
		else if (!(Get_Pin_state(PLUS_BUTTON)))
		{
			
			while((!(Get_Pin_state(PLUS_BUTTON))));
			switch(state)
			{
				case SET_HOURs:
				
				LCD_Clear();
				LCD_Sring("Hour:");		
				
				if (PTR_ARR[state]<23)
				{
		
		            count[state]++;

				}
				else
				{
				
			    count[state]=0;	
				
				}
				
				LCD_Digit_Display(count[state]);
						
				PTR_ARR[state]=count[state];			
				
				break;
				
				case  SET_MINs:
				LCD_Clear();
				LCD_Sring("MINUTE:");
				if (PTR_ARR[state]<59)
				{
					
					count[state]++;
			
				}
				else
				{
					count[state]=0;
		
		
				}
				LCD_Digit_Display(count[state]);
				
				PTR_ARR[state]=count[state];				
				break;
				case  SET_SECs:
				LCD_Clear();
				LCD_Sring("SECOND:");
			
				if (PTR_ARR[state]<59)
				{
					
					count[state]++;

				}			
				else
				{
		           count[state]=0;
		                 
			    }
					LCD_Digit_Display(count[state]);
					
					PTR_ARR[state]=count[state];		
				break;
				
				case  SET_DAYs:
				
				LCD_Clear();
				LCD_Sring("Day:");
				if (PTR_ARR[SET_DAYs]<7)
				{
					
					count[SET_DAYs]++;
					
				}
				else
				{
		          count[SET_DAYs]=1;    
				}
				
				switch(count[SET_DAYs])
				{
					case (1):
					LCD_Sring("Sunday");
					break;
					
					case (2):
					LCD_Sring("Monday");
					break;
					
					case (3):
					LCD_Sring("Tuesday");
					break;
					
					case (4):
					LCD_Sring("Wendsday");
					break;
					
					case (5):
					LCD_Sring("Thursday");
					break;
					
					case (6):
					LCD_Sring("Friday");
					break;
					case (7):
					LCD_Sring("Saturday");
					break;
					
				}	
			PTR_ARR[SET_DAYs]=count[SET_DAYs];		
				break;
				
				case  SET_DATEs:
				
				LCD_Clear();
				LCD_Sring("Date:");
				if (PTR_ARR[SET_DATEs]<31)
				{
				
					count[SET_DATEs]+=1;

				}
				else
				{
					count[SET_DATEs]=1;
				
				}
					LCD_Digit_Display(count[SET_DATEs]);
					PTR_ARR[SET_DATEs]=count[SET_DATEs];			
				break;
				
				case  SET_MONTHs:
				LCD_Clear();
				LCD_Sring("Month:");
				if (PTR_ARR[SET_MONTHs]<12)
				{
					
					count[SET_MONTHs]++;
		
				}
				else
				{
				count[SET_MONTHs]=1;
				}
					LCD_Digit_Display(count[SET_MONTHs]);
					PTR_ARR[SET_MONTHs]=count[SET_MONTHs];
				break;
				
				case  SET_YEARs:
				
				LCD_Clear();
				LCD_Sring("Year:");
				if (PTR_ARR[SET_YEARs]<99)
				{
			
					count[SET_YEARs]++;
				}
				else
				{
				count[SET_YEARs]=20;
				}
				
				
					LCD_Digit_Display(count[SET_YEARs]);
					PTR_ARR[SET_YEARs]=count[SET_YEARs];				
		
				break;
				default:
				// Do nothing
				break;
			}
		}
		
		
	//MINUS BUTTON	
		else if (!(Get_Pin_state(MINUS_BUTTON)))
		{
			while((!(Get_Pin_state(MINUS_BUTTON))));
			switch(state)
			{
				case SET_HOURs:
				LCD_Clear();
				LCD_Sring("Hour:");
				if (PTR_ARR[SET_HOURs]==0)
				{
					count[SET_HOURs]=12;
				}
				else
				{
					count[SET_HOURs]--;
				}
				
				PTR_ARR[SET_HOURs]=count[SET_HOURs];
				LCD_Digit_Display(count[SET_HOURs]);
					
									
				break;
				
				case  SET_MINs:
				LCD_Clear();
				LCD_Sring("MINUTE:");
				if (PTR_ARR[SET_MINs]==0)
				{
					count[SET_MINs]=59;			
				}
				else
				{
					
					count[SET_MINs]--;
				}
				PTR_ARR[SET_MINs]=count[SET_MINs];	
				LCD_Digit_Display(count[SET_MINs]);
				break;
				
				case  SET_SECs:
				LCD_Clear();
				LCD_Sring("SECOND:");
				if (PTR_ARR[SET_SECs]==0)
				{
					count[SET_SECs]=59;
				}
				else
				{
					count[SET_SECs]--;
				}
				PTR_ARR[SET_SECs]=count[SET_SECs];
				LCD_Digit_Display(count[SET_SECs]);
				break;
				
				case  SET_DAYs:
				LCD_Clear();
				LCD_Sring("Day:");
				if (PTR_ARR[SET_DAYs]==1)
				{
				
					count[SET_DAYs]=7;		
				}
					else
					{
					count[SET_DAYs]--;		
					}
					switch(count[SET_DAYs])
					{
						case (1):
						LCD_Sring("Sunday");
						break;
						
						case (2):
						LCD_Sring("Monday");
						break;
						
						case (3):
						LCD_Sring("Tuesday");
						break;
						
						case (4):
						LCD_Sring("Wendsday");
						break;
						
						case (5):
						LCD_Sring("Thursday");
						break;
						
						case (6):
						LCD_Sring("Friday");
						break;
						case (7):
						LCD_Sring("Saturday");
						break;
					PTR_ARR[SET_DAYs]=count[SET_DAYs];
				}
				break;
				
				case  SET_DATEs:
					LCD_Clear();
					LCD_Sring("Date:");				
				if (PTR_ARR[SET_DATEs]==1)
				{

					count[SET_DATEs]=31;

				}
				else
				{
					count[SET_DATEs]--;
				}
				PTR_ARR[SET_DATEs]=count[SET_DATEs];
				LCD_Digit_Display(count[SET_DATEs]);
									
				break;
				
				case  SET_MONTHs:
					LCD_Clear();
					LCD_Sring("Month:");				
				if (PTR_ARR[SET_MONTHs]==1)
				{
					count[SET_MONTHs]=12;
				}
				else
				{
					count[SET_MONTHs]--;		
				}
		        PTR_ARR[SET_MONTHs]=count[SET_MONTHs];			
				LCD_Digit_Display(count[SET_MONTHs]);
							
				break;
				
				case  SET_YEARs:
				if (PTR_ARR[SET_YEARs]>=20)
				{
					LCD_Clear();
					LCD_Sring("Year:");
					count[SET_YEARs]--;
					LCD_Digit_Display(count[SET_YEARs]);
					PTR_ARR[SET_YEARs]=count[SET_YEARs];
				}
				
				break;
				default:
				// Do nothing
				break;
			}
			
			
		}
		
		
		
		
		
	}
	
	
}
	


void PB_Get_RTC_ARR(t_RTC_time *parr)
{

	(parr->Seconds)=PTR_ARR[SET_SECs];
	(parr->Minutes)=PTR_ARR[SET_MINs];
	(parr->Hours)=PTR_ARR[SET_HOURs];
	
	(parr->Weekday)=PTR_ARR[SET_DAYs];
	(parr->date)=PTR_ARR[SET_DATEs];
	(parr->Month)=PTR_ARR[SET_MONTHs];
	(parr->Year)=PTR_ARR[SET_YEARs];
		
}