/*
 * alarm_fsm.c
 *
 *  Created on: Dec 9, 2023
 *      Author: ASUS
 */

#include "alarm_fsm.h"
enum ALARMCLOCKSTATE{SEC,MIN,HOUR,DAY,DATE,MONTH,YEAR,INIT,HOLD};
enum ALARMCLOCKSTATE alarmclkstate=HOLD;

#define ON	0
#define OFF	1

uint8_t alarmledstate=OFF;

void alarm_fsm(){
	switch(alarmclkstate){
	case INIT:
		updateAlarm();
		ds3231_ReadTime();
		displayTime();
		alarmclkstate=SEC;
		break;
	case HOLD:
		if(mode==ALARM_M) alarmclkstate=INIT;
		break;
	case SEC:
		alarmButtonHandler(SEC, MIN);
		lcd_ShowIntNum (150 ,130 , alarmvals[YEAR] ,2, YELLOW ,BLACK ,24);
		alarmBlinkCLKHandler(150 ,100 , alarmvals[SEC] ,2, GREEN ,BLACK ,24);
		break;
	case MIN:
		alarmButtonHandler(MIN, HOUR);
		lcd_ShowIntNum (150 ,100 , alarmvals[SEC] ,2, GREEN ,BLACK ,24);
		alarmBlinkCLKHandler(110 ,100 , alarmvals[MIN] ,2, GREEN ,BLACK ,24);
		break;
	case HOUR:
		alarmButtonHandler(HOUR, DAY);
		lcd_ShowIntNum (110 ,100 , alarmvals[MIN] ,2, GREEN ,BLACK ,24);
		alarmBlinkCLKHandler(70 ,100 ,alarmvals[HOUR] ,2, GREEN ,BLACK ,24) ;
		break;
	case DAY:
		alarmButtonHandler(DAY, DATE);
		lcd_ShowIntNum (70 ,100 , alarmvals[HOUR] ,2, GREEN ,BLACK ,24);
		alarmBlinkCLKHandler(20 ,130 , alarmvals[DAY] ,2, YELLOW ,BLACK ,24) ;
		break;
	case DATE:
		alarmButtonHandler(DATE, MONTH);
		lcd_ShowIntNum (20 ,130 , alarmvals[DAY] ,2, YELLOW ,BLACK ,24);
		alarmBlinkCLKHandler(70 ,130 , alarmvals[DATE] ,2, YELLOW ,BLACK ,24) ;
		break;
	case MONTH:
		alarmButtonHandler(MONTH, YEAR);
		lcd_ShowIntNum (70 ,130 , alarmvals[DATE] ,2, YELLOW ,BLACK ,24);
		alarmBlinkCLKHandler(110 ,130 , alarmvals[MONTH] ,2, YELLOW ,BLACK ,24) ;
		break;
	case YEAR:
		alarmButtonHandler(YEAR, SEC);
		lcd_ShowIntNum (110 ,130 , alarmvals[MONTH] ,2, YELLOW ,BLACK ,24);
		alarmBlinkCLKHandler(150 ,130 , alarmvals[YEAR] ,2, YELLOW ,BLACK ,24) ;
		break;
	}
}

void alarmButtonHandler(enum ALARMCLOCKSTATE curState,enum ALARMCLOCKSTATE nextState){
	if(FLAG_BUT_CD==1){
		if(button_count[0]==1){
			mode=AUTO_M;
			alarmclkstate=HOLD;
		}
		else if(button_count[12]==1){
			alarmclkstate=nextState;
		}
		else if(button_count[3]==1){
			flag_inc_press=1;
		}
		else if(button_count[3]==0 && flag_inc_press==1){
			flag_inc_press=0;
			alarmvals[curState]++;
			alarmTimeDurationHandler();
			updateAlarm();
		}
		setbutCooldownTimer(50);
	}
}

void alarmBlinkCLKHandler(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey){
	switch(alarmledstate){
	case ON:
		if(FLAG_BLINK_NUM==1){
			alarmledstate=OFF;
			lcd_ShowIntNum (x,y,num,len,fc,bc,sizey);
			setblinkCLKnumTimer(250);
		}
		break;
	case OFF:
		if(FLAG_BLINK_NUM==1){
			alarmledstate=ON;
			lcd_ShowIntNum (x,y,num,len,BLACK,bc,sizey);
			setblinkCLKnumTimer(250);
		}
		break;
	}
}
void alarmTimeDurationHandler(){
	switch(alarmclkstate){
	case INIT:
		break;
	case HOLD:
		break;
	case SEC:
		if(alarmvals[SEC]>60) alarmvals[SEC]=0;
		break;
	case MIN:
		if(alarmvals[MIN]>60) alarmvals[MIN]=0;
		break;
	case HOUR:
		if(alarmvals[HOUR]>60) alarmvals[HOUR]=0;
		break;
	case DAY:
		if(alarmvals[DAY]>8) alarmvals[DAY]=2;
		break;
	case DATE:
		if(alarmvals[DATE]>31) alarmvals[DATE]=1;
		break;
	case MONTH:
		if(alarmvals[MONTH]>12) alarmvals[MONTH]=1;
		break;
	case YEAR:
		break;
	}
}
