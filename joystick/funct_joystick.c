/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        High level joystick management functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"
#include "../GLCD/GLCD.h"
#include "../RIT/RIT.h"
#include "../tamagocy.h"

extern uint16_t xc,yc,radius;

void draw_snack(void){
	
	LCD_DrawRectangle(20,210,20,10,Blue);
	LCD_DrawTriangle(10,207,10,223,20,215,Black);
	LCD_DrawTriangle(50,207,50,223,40,215,Black);
}



void eat_snack(void){
	
	uint16_t i;
	
	draw_snack();
	
	
	/*delete_tamagocy(xc,yc,radius,White);
	draw_tamagocy_hungry(xc,yc,radius,Black);

	for(i=1;i<50;i++){
		draw_snack();
		draw_tamagocy(xc-i,yc,radius,Black);
		delete_tamagocy(xc-i,yc,radius,White);
	}
	*/
	
	
}
void eat_meal(void){
	
}
