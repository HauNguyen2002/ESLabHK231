/*
 * fsm_automatic.c
 *
 *  Created on: Nov 6, 2023
 *      Author: ASUS
 */

#include "lcd.h"
#include "software_timer.h"
#include "fsm_automatic.h"
#include "fsm_global.h"
#include "button.h"

enum Automatic_traffic_light{AUTO_INIT,AUTO_HOLD, AUTO_RG, AUTO_RY, AUTO_GR, AUTO_YR};
enum Automatic_traffic_light lightstate=AUTO_INIT;

int x_road1[]={20,180};
int y_road1[]={100,160,220};
int x_road2[]={40,100,160};
int y_road2[]={20,300};
int radius=20;
int back=0;
int light_duration[3]={5,2,3};
int light_num_display[2]={5,3};
void fsm_automatic(){
	switch(lightstate){
	case AUTO_INIT:
		light_num_display[0]=light_duration[0];
		light_num_display[1]=light_duration[2];
		displayAutoLight();
		lightstate=AUTO_RG;
		back=0;
		setLightAutoTimer(1000);
		break;
	case AUTO_HOLD:
			if(button_count[0]==1 && back==1){
				lightstate=AUTO_INIT;
				setButCooldownTimer(100);
				break;
			}
		break;
	case AUTO_RG:
		if(flag_timer2[3]==1){
			if(button_count[0]==1){
				lightstate=AUTO_HOLD;
				setButCooldownTimer(100);
				break;
			}
		}
		if(flag_timer2[1]==1){
			displayAutoLight();
			if(light_num_display[1]==0){
				lightstate=AUTO_RY;
				light_num_display[1]=light_duration[1];
			}
			setLightAutoTimer(1000);
		}
		break;
	case AUTO_RY:
		if(flag_timer2[3]==1){
			if(button_count[0]==1){
				lightstate=AUTO_HOLD;
				setButCooldownTimer(100);
				break;
			}
		}
		if(flag_timer2[1]==1){
			displayAutoLight();
			if(light_num_display[1]==0){
				lightstate=AUTO_GR;
				light_num_display[0]=light_duration[2];
				light_num_display[1]=light_duration[0];
			}
			setLightAutoTimer(1000);
			}
		break;
	case AUTO_GR:
		if(flag_timer2[3]==1){
			if(button_count[0]==1){
				lightstate=AUTO_HOLD;
				setButCooldownTimer(100);
				break;
			}
		}
		if(flag_timer2[1]==1){
			displayAutoLight();
			if(light_num_display[0]==0){
				lightstate=AUTO_YR;
				light_num_display[0]=light_duration[1];
			}
			setLightAutoTimer(1000);
			}
		break;
	case AUTO_YR:
		if(flag_timer2[3]==1){
			if(button_count[0]==1){
				lightstate=AUTO_HOLD;
				setButCooldownTimer(100);
				break;
			}
		}
		if(flag_timer2[1]==1){
			displayAutoLight();
			if(light_num_display[0]==0){
				lightstate=AUTO_RG;
				light_num_display[0]=light_duration[0];
				light_num_display[1]=light_duration[2];
			}
			setLightAutoTimer(1000);
			}
		break;
	}
}
void displayAutoLight(){
	switch(lightstate){
	case AUTO_INIT:
		lcd_Fill(0, 0, 2000,2000, WHITE);
		lcd_StrCenter(0, 2, "NORMAL", RED, BLUE, 16, 1);

		lcd_DrawCircle(x_road1[0],  y_road1[2], WHITE,  radius, 1);
		lcd_DrawCircle(x_road1[0], y_road1[2], GREEN,  radius, 0);

		lcd_DrawCircle(x_road1[0],  y_road1[0], RED,  radius, 0);
		lcd_DrawCircle(x_road1[0],  y_road1[1], YELLOW,  radius, 0);
		lcd_DrawCircle(x_road1[0], y_road1[2], GREEN,  radius, 0);
//		lcd_DrawCircle(180, 40, GREEN, 20, 1);
//		lcd_DrawCircle(180, 100, RED, 20, 1);
//		lcd_DrawCircle(180, 160, YELLOW, 20, 1);

		lcd_DrawCircle(x_road2[2],y_road2[1], WHITE,  radius, 1);
		lcd_DrawCircle(x_road2[2],y_road2[1], GREEN,  radius, 0);

		lcd_DrawCircle(x_road2[0],y_road2[1], RED,  radius, 0);
		lcd_DrawCircle(x_road2[1],y_road2[1], YELLOW,  radius, 0);
		lcd_DrawCircle(x_road2[2],y_road2[1], GREEN,  radius, 0);
//		lcd_DrawCircle(0, 120, GREEN, 20, 1);
//		lcd_DrawCircle(0, 200, RED, 20, 1);
//		lcd_DrawCircle(0, 280, YELLOW, 20, 1);
		break;
	case AUTO_RG:
		lcd_DrawCircle(x_road1[0],  y_road1[0], RED,  radius, 1);
		lcd_DrawCircle(x_road1[0],  y_road1[1], WHITE,  radius, 1);
		lcd_DrawCircle(x_road1[0],  y_road1[1], YELLOW,  radius, 0);

		lcd_DrawCircle(x_road2[0],y_road2[1], WHITE,  radius, 1);
		lcd_DrawCircle(x_road2[0],y_road2[1], RED,  radius, 0);
		lcd_DrawCircle(x_road2[2],y_road2[1], GREEN,  radius, 1);


		lcd_ShowIntNum(60, 60, light_num_display[0], 8, RED, WHITE, 16);
		lcd_ShowIntNum(120, 120, light_num_display[1], 8, GREEN, WHITE, 16);
		light_num_display[0]--;
		light_num_display[1]--;

		break;
	case AUTO_RY:
		lcd_DrawCircle(x_road2[1],y_road2[1], YELLOW,  radius, 1);
		lcd_DrawCircle(x_road2[2],y_road2[1], WHITE,  radius, 1);
		lcd_DrawCircle(x_road2[2],y_road2[1], GREEN,  radius, 0);

		lcd_ShowIntNum(60, 60, light_num_display[0], 8, RED, WHITE, 16);
		lcd_ShowIntNum(120, 120, light_num_display[1], 8, YELLOW, WHITE, 16);
		light_num_display[0]--;
		light_num_display[1]--;
		break;
	case AUTO_GR:
		lcd_DrawCircle(x_road1[0],  y_road1[0], WHITE,  radius, 1);
		lcd_DrawCircle(x_road1[0],  y_road1[0], RED,  radius, 0);
		lcd_DrawCircle(x_road1[0], y_road1[2], GREEN,  radius, 1);

		lcd_DrawCircle(x_road2[0],y_road2[1], RED,  radius, 1);
		lcd_DrawCircle(x_road2[1],y_road2[1], WHITE,  radius, 1);
		lcd_DrawCircle(x_road2[1],y_road2[1], YELLOW,  radius, 0);

		lcd_ShowIntNum(60, 60, light_num_display[0], 8, GREEN, WHITE, 16);
		lcd_ShowIntNum(120, 120, light_num_display[1], 8, RED, WHITE, 16);
		light_num_display[0]--;
		light_num_display[1]--;
		break;
	case AUTO_YR:
		lcd_DrawCircle(x_road1[0],  y_road1[1], YELLOW,  radius, 1);
		lcd_DrawCircle(x_road1[0], y_road1[2], WHITE,  radius, 1);
		lcd_DrawCircle(x_road1[0], y_road1[2], GREEN,  radius, 0);

		lcd_ShowIntNum(60, 60, light_num_display[0], 8, YELLOW, WHITE, 16);
		lcd_ShowIntNum(120, 120, light_num_display[1], 8, RED, WHITE, 16);
		light_num_display[0]--;
		light_num_display[1]--;
		break;
	}
}

