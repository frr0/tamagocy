/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include "LPC17xx.h"
#include "GLCD/GLCD.h"
#include "tamagocy.h"
#include "timer/timer.h"

#include "joystick/joystick.h"
#include "RIT/RIT.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif




int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	joystick_init();											/* Joystick Initialization            */
  LCD_Initialization();
//XMAX=240  YMAX=320
	LCD_Clear(White);
	

	create_tamagochy(120,160,80,Black);
	
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       */
	//init_RIT(0x1DCD6500);					      //5 secondi
	enable_RIT();												/* enable RIT to count 50ms				 */
	
	
	
	init_timer(0, 0, 0, 3,0x017D7840);   //1 secondo
	enable_timer(0);
	
	

	
	
	
	
	
	
	
	
  while (1)	
  {
		
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
