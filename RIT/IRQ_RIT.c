/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h" 

#include "../tamagocy.h"
#include "../joystick/joystick.h"
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern int dead;

extern int seconds,hours,minutes;




void RIT_IRQHandler (void)
{			
	static int select=0;
	static int left = 0;
	static int right=0;	
		
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){ //select
			select++;
		switch(select){
			case 1:
				
				if(left){
					left=0;
					LCD_DrawRectangle_empty(0,270,120,50,Green);
					LCD_DrawRectangle_empty(0,270,120,50,Black);
					NVIC_DisableIRQ(RIT_IRQn);
					
					
					eat_meal();
					add_green_bar_satiety();
					reset_RIT();
					NVIC_EnableIRQ(RIT_IRQn);
					
				}
				if(right){
					right=0;
					LCD_DrawRectangle_empty(120,270,240,50,Green);
					LCD_DrawRectangle_empty(120,270,240,50,Black);
					
					NVIC_DisableIRQ(RIT_IRQn);
					
					eat_snack();
					
					add_green_bar_happy();
					reset_RIT();
					NVIC_EnableIRQ(RIT_IRQn);
					
				}
				if(dead){
					dead=0;
					seconds=minutes=hours=0;
					LCD_DrawRectangle_empty(0,270,240,50,Green);
					LCD_Clear(White);
					create_tamagochy(120,160,90,Black);
					
					reset_timer(TIMER0_IRQn);
				
					NVIC_EnableIRQ(TIMER0_IRQn);
				}
				
				
				break;
			default:
				break;
		}
	}
	else{
			select=0;
	}
	
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){ //left

		left++;
		
		switch(left){
			case 1:
						right=0;
						LCD_DrawRectangle_empty(120,270,240,50,Black);
						LCD_DrawRectangle_empty(0,270,120,50,Red);
			break;
			default:
				break;
		
		}
	}
	
		
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){//right
		right++;
		
		switch(right){
			case 1:
						left=0;
						LCD_DrawRectangle_empty(0,270,120,50,Black);
						LCD_DrawRectangle_empty(120,270,240,50,Red);
			break;
			default:
				break;
		
		}
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){//up
		right=left=0;
		LCD_DrawRectangle_empty(120,270,240,50,Black);
		LCD_DrawRectangle_empty(0,270,120,50,Black);
		
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){//down
		right=left=0;
		LCD_DrawRectangle_empty(120,270,240,50,Black);
		LCD_DrawRectangle_empty(0,270,120,50,Black);
		
	}
	
 reset_RIT();
 LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
