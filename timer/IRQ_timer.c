/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 

#include "../tamagocy.h"


/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int seconds=0;
volatile int minutes=0;
volatile int hours=0;
volatile int flag=0;
extern int dead;



void TIMER0_IRQHandler (void)
{
	char a[200];

	
	
	//Match register 0 interrupt service routine 
	if (LPC_TIM0->IR & 01)
	{
		if(seconds>59){
			seconds=0;			
			//reset timer
			if(minutes>59){
				minutes=0;		
				//reset timer
				hours++;
			}
			minutes++;
		
		}
		
		
		sprintf(a,"  Age: %02d:%02d:%02d",hours,minutes,seconds);
		
		GUI_Text(60,0,(uint8_t *)a,Blue,White);
		
		//linguaccia
		draw_linguaccia();
		
		
		//flag usato per non far ridurre la barra all'inizio
		if(seconds%5==0 && flag){
			remove_green_bar_happy();
			if(dead){return;}
			remove_green_bar_satiety();
			if(dead){return;}

		}
		seconds++;
		flag=1;
		
		LPC_TIM0->IR = 1;			/* clear interrupt flag */
	}
	
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void)
{
	
	//matchreg0
	if (LPC_TIM2->IR == 1)
	{
		
		LPC_TIM2->IR = 1;			/* clear interrupt flag */
	}
		/* Match register 1 interrupt service routine */
	else if(LPC_TIM2->IR == 2)
  {
	

		LPC_TIM2->IR =  2 ;			/* clear interrupt flag */	

	

	}
	
  return;
}





/******************************************************************************
**                            End Of File
******************************************************************************/
