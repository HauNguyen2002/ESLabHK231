/*
 * rtc_adj.c
 *
 *  Created on: Dec 9, 2023
 *      Author: ASUS
 */

#include "rtc_adj.h"

enum MANUALCLOCKSTATE{SEC,MIN,HOUR,DAY,DATE,MONTH,YEAR,INIT,HOLD};
enum MANUALCLOCKSTATE manclkstate=HOLD;

#define ON	0
#define OFF	1

uint8_t ledstate=OFF;

void rtc_manual_fsm(){
	switch(manclkstate){
	case INIT:
		manclkstate=SEC;
		break;
	case HOLD:
		if(mode==MANUAL_M) manclkstate=INIT;
		break;
	case SEC:
		manButtonHandler(SEC, MIN);
		lcd_ShowIntNum (150 ,130 , clockvals[YEAR] ,2, YELLOW ,BLACK ,24);
		manBlinkCLKHandler(150 ,100 , clockvals[SEC] ,2, GREEN ,BLACK ,24);
		break;
	case MIN:
		manButtonHandler(MIN, HOUR);
		lcd_ShowIntNum (150 ,100 , clockvals[SEC] ,2, GREEN ,BLACK ,24);
		manBlinkCLKHandler(110 ,100 , clockvals[MIN] ,2, GREEN ,BLACK ,24);
		break;
	case HOUR:
		manButtonHandler(HOUR, DAY);
		lcd_ShowIntNum (110 ,100 , clockvals[MIN] ,2, GREEN ,BLACK ,24);
		manBlinkCLKHandler(70 ,100 ,clockvals[HOUR] ,2, GREEN ,BLACK ,24) ;
		break;
	case DAY:
		manButtonHandler(DAY, DATE);
		lcd_ShowIntNum (70 ,100 , clockvals[HOUR] ,2, GREEN ,BLACK ,24);
		manBlinkCLKHandler(20 ,130 , clockvals[DAY] ,2, YELLOW ,BLACK ,24) ;
		break;
	case DATE:
		manButtonHandler(DATE, MONTH);
		lcd_ShowIntNum (20 ,130 , clockvals[DAY] ,2, YELLOW ,BLACK ,24);
		manBlinkCLKHandler(70 ,130 , clockvals[DATE] ,2, YELLOW ,BLACK ,24) ;
		break;
	case MONTH:
		manButtonHandler(MONTH, YEAR);
		lcd_ShowIntNum (70 ,130 , clockvals[DATE] ,2, YELLOW ,BLACK ,24);
		manBlinkCLKHandler(110 ,130 , clockvals[MONTH] ,2, YELLOW ,BLACK ,24) ;
		break;
	case YEAR:
		manButtonHandler(YEAR, SEC);
		lcd_ShowIntNum (110 ,130 , clockvals[MONTH] ,2, YELLOW ,BLACK ,24);
		manBlinkCLKHandler(150 ,130 , clockvals[YEAR] ,2, YELLOW ,BLACK ,24) ;
		break;
	}
}

void manButtonHandler(enum MANUALCLOCKSTATE curState,enum MANUALCLOCKSTATE nextState){
	if(FLAG_BUT_CD==1){
		if(button_count[0]==1){
			mode=ALARM_M;
			manclkstate=HOLD;
		}
		else if(button_count[12]==1){
			manclkstate=nextState;
		}
		else if(button_count[3]==1){
			flag_inc_press=1;
		}
		else if(button_count[3]==0 && flag_inc_press==1){
			flag_inc_press=0;
			clockvals[curState]++;
			manTimeDurationHandler();
			updateTime();
		}
		setbutCooldownTimer(50);
	}
}

void manBlinkCLKHandler(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey){
	switch(ledstate){
	case ON:
		if(FLAG_BLINK_NUM==1){
			ledstate=OFF;
			lcd_ShowIntNum (x,y,num,len,fc,bc,sizey);
			setblinkCLKnumTimer(250);
		}
		break;
	case OFF:
		if(FLAG_BLINK_NUM==1){
			ledstate=ON;
			lcd_ShowIntNum (x,y,num,len,BLACK,bc,sizey);
			setblinkCLKnumTimer(250);
		}
		break;
	}
}
void manTimeDurationHandler(){
	switch(manclkstate){
	case INIT:
		break;
	case HOLD:
		break;
	case SEC:
		if(clockvals[SEC]>60) clockvals[SEC]=0;
		break;
	case MIN:
		if(clockvals[MIN]>60) clockvals[MIN]=0;
		break;
	case HOUR:
		if(clockvals[HOUR]>60) clockvals[HOUR]=0;
		break;
	case DAY:
		if(clockvals[DAY]>8) clockvals[DAY]=2;
		break;
	case DATE:
		if(clockvals[DATE]>31) clockvals[DATE]=1;
		break;
	case MONTH:
		if(clockvals[MONTH]>12) clockvals[MONTH]=1;
		break;
	case YEAR:
		break;
	}
}
