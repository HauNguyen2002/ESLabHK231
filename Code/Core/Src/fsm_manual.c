/*
 * fsm_manual.c
 *
 *  Created on: Nov 6, 2023
 *      Author: ASUS
 */
#include "lcd.h"
#include "software_timer.h"
#include "fsm_manual.h"
#include "fsm_global.h"
#include "button.h"


enum Manual_traffic_light{INIT,WAIT,HOLD, MAN_RED, MAN_YELLOW, MAN_GREEN};
enum Manual_traffic_light man_lightstate=HOLD;

int blink=0;
int temp_add_duration=0;
void fsm_manual()
{
	switch(man_lightstate){
	case INIT:
		displayManLight();
		man_lightstate=MAN_RED;
		setLightManualTimer(100);
		break;
	case HOLD:
			if(button_count[0]==1){
				man_lightstate=INIT;
				break;
			}
		break;
	case WAIT:
		if(flag_timer2[3]==1) man_lightstate=HOLD;
		break;
	case MAN_RED:
		if(flag_timer2[3]==1){
			if(button_count[0]==1){
				temp_add_duration=0;
				man_lightstate=MAN_YELLOW;
				setButCooldownTimer(100);
				break;
			}
			if(button_count[1]==1){
				temp_add_duration+=1;
				setButCooldownTimer(100);
				break;
			}
			if(button_count[2]==1){
				light_duration[0]+=temp_add_duration;
				setButCooldownTimer(100);
				break;
			}
		}
		if(flag_timer2[2]==1)
		{
			displayManLight();
			setLightManualTimer(1000);
		}
		break;
	case MAN_YELLOW:
		if(flag_timer2[3]==1){
			if(button_count[0]==1){
				temp_add_duration=0;
				man_lightstate=MAN_GREEN;
				setButCooldownTimer(100);
				break;
			}
			if(button_count[1]==1){
				temp_add_duration+=1;
				setButCooldownTimer(100);
				break;
			}
			if(button_count[2]==1){
				light_duration[1]+=temp_add_duration;
				setButCooldownTimer(100);
				HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
				break;
			}
		}
		if(flag_timer2[2]==1)
		{
			displayManLight();
			setLightManualTimer(1000);
		}
		break;
	case MAN_GREEN:
		if(flag_timer2[3]==1){
			if(button_count[0]==1){
				temp_add_duration=0;
				man_lightstate=WAIT;
				setButCooldownTimer(100);
				back=1;
			}
			if(button_count[1]==1){
				temp_add_duration+=1;
				setButCooldownTimer(100);
				break;
			}
			if(button_count[2]==1){
				light_duration[2]+=temp_add_duration;
				setButCooldownTimer(100);
				HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
				break;
			}
		}
		if(flag_timer2[2]==1){
			displayManLight();
			setLightManualTimer(1000);
		}
		break;
	}
}
void displayManLight()
{
	switch(man_lightstate){
	case INIT:
		lcd_Fill(0, 0, 900,20, WHITE);
		lcd_StrCenter(0, 2, "MODIFICATION", RED, BLUE, 16, 1);

		lcd_DrawCircle(x_road1[0],  y_road1[0], RED,  radius, 1);

		lcd_DrawCircle(x_road1[0],  y_road1[1], WHITE,  radius, 1);
		lcd_DrawCircle(x_road1[0],  y_road1[1], YELLOW,  radius, 0);

		lcd_DrawCircle(x_road1[0],  y_road1[2], WHITE,  radius, 1);
		lcd_DrawCircle(x_road1[0],  y_road1[2], GREEN,  radius, 0);

		lcd_DrawCircle(x_road2[0],y_road2[1], RED,  radius, 1);

		lcd_DrawCircle(x_road2[1],y_road2[1], WHITE,  radius, 1);
		lcd_DrawCircle(x_road2[1],y_road2[1], YELLOW,  radius, 0);

		lcd_DrawCircle(x_road2[2],  y_road2[1], WHITE,  radius, 1);
		lcd_DrawCircle(x_road2[2],y_road2[1], GREEN,  radius, 0);
		break;
	case HOLD:
		break;
	case MAN_RED:
		if(blink==0){
			lcd_DrawCircle(x_road1[0],  y_road1[0], RED,  radius, 1);
			lcd_DrawCircle(x_road2[0],y_road2[1], RED,  radius, 1);
			blink=1;
		}
		else if(blink==1){
			lcd_DrawCircle(x_road1[0],  y_road1[0], WHITE,  radius, 1);
			lcd_DrawCircle(x_road2[0],y_road2[1], WHITE,  radius, 1);

			lcd_DrawCircle(x_road1[0],  y_road1[0], RED,  radius, 0);
			lcd_DrawCircle(x_road2[0],y_road2[1], RED,  radius, 0);
			blink=0;
		}
		lcd_ShowIntNum(60, 120, light_duration[0]+temp_add_duration, 8, RED, WHITE, 16);
		break;
	case MAN_YELLOW:

		lcd_DrawCircle(x_road1[0],  y_road1[0], WHITE,  radius, 1);
		lcd_DrawCircle(x_road2[0],y_road2[1], WHITE,  radius, 1);

		lcd_DrawCircle(x_road1[0],  y_road1[0], RED,  radius, 0);
		lcd_DrawCircle(x_road2[0],y_road2[1], RED,  radius, 0);

		if(blink==0){
			lcd_DrawCircle(x_road1[0],  y_road1[1], YELLOW,  radius, 1);
			lcd_DrawCircle(x_road2[1],y_road2[1], YELLOW,  radius, 1);
			blink=1;
		}
		else if(blink==1){
			lcd_DrawCircle(x_road1[0],  y_road1[1], WHITE,  radius, 1);
			lcd_DrawCircle(x_road2[1],y_road2[1], WHITE,  radius, 1);

			lcd_DrawCircle(x_road1[0],  y_road1[1], YELLOW,  radius, 0);
			lcd_DrawCircle(x_road2[1],y_road2[1], YELLOW,  radius, 0);
			blink=0;
		}
		lcd_ShowIntNum(60, 120, light_duration[1]+temp_add_duration, 8, RED, WHITE, 16);
		break;
	case MAN_GREEN:
		lcd_DrawCircle(x_road1[0],  y_road1[1], WHITE,  radius, 1);
		lcd_DrawCircle(x_road2[1],y_road2[1], WHITE,  radius, 1);

		lcd_DrawCircle(x_road1[0],  y_road1[1], YELLOW,  radius, 0);
		lcd_DrawCircle(x_road2[1],y_road2[1], YELLOW,  radius, 0);
		if(blink==0){
			lcd_DrawCircle(x_road1[0],  y_road1[2], GREEN,  radius, 1);
			lcd_DrawCircle(x_road2[2],y_road2[1], GREEN,  radius, 1);
			blink=1;
		}
		else if(blink==1){
			lcd_DrawCircle(x_road1[0],  y_road1[2], WHITE,  radius, 1);
			lcd_DrawCircle(x_road2[2],y_road2[1], WHITE,  radius, 1);

			lcd_DrawCircle(x_road1[0],  y_road1[2], GREEN,  radius, 0);
			lcd_DrawCircle(x_road2[2],y_road2[1], GREEN,  radius, 0);
			blink=0;
		}
		lcd_ShowIntNum(60, 120, light_duration[2]+temp_add_duration, 8, RED, WHITE, 16);

		break;
	}
}
