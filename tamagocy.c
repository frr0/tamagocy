/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        High level joystick management functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/


#include "GLCD/GLCD.h"
#include "tamagocy.h"
#include "timer/timer.h"
#include "RIT/RIT.h"

uint16_t bar_lenght=82;
uint16_t bar_height=30;
volatile int dead=0;
volatile uint16_t happines_x_pos,satiety_x_pos,bars_y_pos;

volatile uint16_t radius,xc,yc;

	

extern int flag;
volatile int lingua=0;
uint16_t happy_bar_start;
uint16_t happy_bar_end;
uint16_t satiety_bar_start;
uint16_t satiety_bar_end;





void draw_linguaccia(){
	
	
	if(lingua==0){
		lingua=1;
		LCD_DrawSemiCircle(xc,yc+45+1,25,Red,1);
		LCD_DrawLine(xc,yc+45+1,xc,yc+10+51,Black);
	}
	else{
		LCD_DrawSemiCircle(xc,yc+45+1,25,White,1);
		lingua=0;
		//LCD_DrawLine(xc,yc,160,210,Black);
	}
}

void draw_mouth(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t color){
	LCD_MyDrawLine(x0,y0,x1,y1,color);
}

void draw_eye_rectangle(uint16_t x0,uint16_t y0,uint16_t lenght,uint16_t height,uint16_t color){
	
	LCD_DrawRectangle_empty(x0,y0,lenght,height,color);
	
	LCD_DrawCircle(x0+20,y0+23,5,color);
	
}

void draw_tamagocy(uint16_t Xpos,uint16_t Ypos, uint16_t r,uint16_t color){
	
	LCD_DrawCircle_empty(Xpos,Ypos,radius,color);
	//LCD_DrawSemiCircle(Xpos,Ypos,radius,Red);
	
	draw_mouth(Xpos-40,Ypos+45,Xpos+40,Ypos+45,color);
	
	//eyes
	
	//draw_eye_rectangle(xc-50,yc-60,40,30,color);
	if(dead==0){
		draw_eye_rectangle(Xpos-50,Ypos-50,40,30,color);
		draw_eye_rectangle(Xpos+10,Ypos-50,40,30,color);
	}
	if(dead==1){
			LCD_DrawTriangle(Xpos-50,Ypos-10,Xpos-50,Ypos-40,Xpos-10,Ypos-10,color);
			LCD_DrawTriangle(Xpos+10,Ypos-10,Xpos+50,Ypos-40,Xpos+50,Ypos-10,color);
	}
	
	//mouth
	//LCD_DrawRectangle(80,190,80,30,White);
	
	
	
}


void draw_tamagocy_hungry(uint16_t Xpos,uint16_t Ypos, uint16_t r,uint16_t color){
	
	LCD_DrawCircle_empty(Xpos,Ypos,radius,color);
	//LCD_DrawSemiCircle(Xpos,Ypos,radius,Red);
	
	draw_mouth(Xpos-40,Ypos+45,Xpos+40,Ypos+45,color);
	
	//eyes
	
	LCD_DrawSemiCircle_empty(100,130,20,Black,2);
	
	//mouth
	//LCD_DrawRectangle(80,190,80,30,White);
	
	
	
}

void draw_menu(){
	
	bars_y_pos=41;
	happines_x_pos=20;
	satiety_x_pos=140;
	
	happy_bar_end=happines_x_pos-2+bar_lenght;
	happy_bar_start=happines_x_pos;
	satiety_bar_end=satiety_x_pos-2+bar_lenght;
	satiety_bar_start=satiety_x_pos;
	
	//coomands
	LCD_DrawRectangle_empty(0,270,120,50,Black);
	GUI_Text(15, 280, (uint8_t *) " MEAL  ", Blue,White);
	LCD_DrawRectangle_empty(120,270,240,50,Black);
	GUI_Text(135, 280, (uint8_t *) " SNACK  ", Blue,White);
	
	
	GUI_Text(happines_x_pos, 25, (uint8_t *) "Happiness  ", Blue,White);
	LCD_DrawRectangle_empty(happines_x_pos-1,bars_y_pos-1,bar_lenght,bar_height,Green);
	//add_green_bar_happy();
	//add_green_bar_happy();
	//add_green_bar_happy();
	add_green_bar_happy();
	
	GUI_Text(satiety_x_pos, 25, (uint8_t *) "Satiety  ", Blue,White);
	LCD_DrawRectangle_empty(satiety_x_pos-1,bars_y_pos-1,bar_lenght,bar_height,Green);
	//add_green_bar_satiety();
	//add_green_bar_satiety();
	//add_green_bar_satiety();
	add_green_bar_satiety();


}



void create_tamagochy(uint16_t Xpos,uint16_t Ypos, uint16_t r, uint16_t color){
	
	volatile uint16_t xleft,yleft,xright,yright,xtop,ytop,xbotton,ybotton;
		
	xleft=Xpos-radius;
	xright=Xpos+radius;
	xtop=xbotton=Xpos;
	
	yleft=yright=Ypos;
	ytop=Ypos-radius;
	ybotton=Ypos+radius;
	
	xc=Xpos;
	yc=Ypos;
	radius=r;
	//body
	
	
	
	draw_tamagocy(xc,yc,r,color);

	//menu
	draw_menu();
	


}

void delete_tamagocy(uint16_t Xpos,uint16_t Ypos, uint16_t r,uint16_t color){
	
	if(lingua==1){
		draw_linguaccia();
	}
	draw_tamagocy(Xpos,Ypos,r,color);
}

void runaway_sequence(void){
	uint16_t i;
	
	flag=0;
	
	
	NVIC_DisableIRQ(TIMER0_IRQn);
	NVIC_DisableIRQ(RIT_IRQn);
	
	//animazione per l'uscita
	
	delete_tamagocy(xc,yc,radius,White);
	
	
	dead=1;
	for(i=0;i<MAX_X+radius;i+=20){
		
		draw_tamagocy(xc+i,yc,radius,Black);
	
		delete_tamagocy(xc+i,yc,radius,White);
		
	}
	

	
	LCD_DrawRectangle(0,40,240,320-40,White);
	
	
	
	draw_tamagocy(xc,yc,radius,Black);

	
	
	
	LCD_DrawRectangle_empty(0,270,240,50,Red);
	GUI_Text(100, 280, (uint8_t *) " RESET  ", Black,White);
	
	LCD_DrawRectangle_empty(19,bars_y_pos-1,bar_lenght,bar_height,Red);
	GUI_Text(55,50 , (uint8_t *) "!  ", Red,White);
	LCD_DrawRectangle_empty(139,bars_y_pos-1,bar_lenght,bar_height,Red);
	GUI_Text(175,50 , (uint8_t *) "!  ", Red,White);
	
	
	GUI_Text(80,220 , (uint8_t *) "Look my friend has     gone... Not a great job      dont't you think? ", Red,White);
	
	
	
	reset_RIT();
	NVIC_EnableIRQ(RIT_IRQn);
	

	
}


void add_green_bar_happy(){
	
	uint16_t lenght=20;
	uint16_t height=28;
	
	
	if(happines_x_pos<happy_bar_end){
		LCD_DrawRectangle(happines_x_pos,bars_y_pos,lenght,height,Green);
		happines_x_pos+=lenght;
	}
	
	
}
void remove_green_bar_happy(){
	
	uint16_t lenght=20;
	uint16_t height=28;
 
	
	if(happines_x_pos>happy_bar_start){
		happines_x_pos-=lenght;
		LCD_DrawRectangle(happines_x_pos,bars_y_pos,lenght,height,White);
	}
	else{//morto
		runaway_sequence();
		return;
	}
	
	if(happines_x_pos==happy_bar_start){
		LCD_DrawRectangle(happines_x_pos,bars_y_pos,5,height,Yellow);
	}
	
	
}

void add_green_bar_satiety(){
	
	uint16_t lenght=20;
	uint16_t height=28;
	
	
	
	if(satiety_x_pos<satiety_bar_end){
		LCD_DrawRectangle(satiety_x_pos,bars_y_pos,lenght,height,Green);
		satiety_x_pos+=lenght;
	}
	
	
}
void remove_green_bar_satiety(){
	
	uint16_t lenght=20;
	uint16_t height=28;
 
	
	if(satiety_x_pos>satiety_bar_start){
		satiety_x_pos-=lenght;
		LCD_DrawRectangle(satiety_x_pos,bars_y_pos,lenght,height,White);
		
	}
	else{//morto
		runaway_sequence();
		return;
	}
	
	if(satiety_x_pos==satiety_bar_start){
		LCD_DrawRectangle(satiety_x_pos,bars_y_pos,5,height,Yellow);
	}
	
	
	
}


