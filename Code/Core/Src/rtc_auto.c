/*
 * auto_rtc_fsm.c
 *
 *  Created on: Nov 20, 2023
 *      Author: ASUS
 */

#include <rtc_auto.h>

enum AUTOCLKSTATE{INIT,HOLD,RUN};
enum AUTOCLKSTATE autoclkstate=INIT;

void rtc_auto_fsm(){
	switch (autoclkstate) {
	case INIT:
		if(FLAG_AUTO==1){
			updateTime();
			autoclkstate=RUN;
			setAutoTimer(100);
		}
		break;
	case HOLD:
		if(mode==AUTO_M) autoclkstate=INIT;
		break;
	case RUN:
		autoButtonHandler();

		if(FLAG_AUTO==1){
			ds3231_ReadTime();
			displayTime();
			clockvals[0]=ds3231_sec;
			clockvals[1]=ds3231_min;
			clockvals[2]=ds3231_hours;
			clockvals[3]=ds3231_day;
			clockvals[4]=ds3231_date;
			clockvals[5]=ds3231_month;
			clockvals[6]=ds3231_year;
			if(checkAlarm()==1){
				lcd_DrawCircle(50, 50,RED,10, RED);
			}
			setAutoTimer(50);
		}
		break;
	}
}

void autoButtonHandler(){
	if(FLAG_BUT_CD==1){
		if(button_count[0]==1){
			mode=MANUAL_M;
			autoclkstate=HOLD;
		}
		setbutCooldownTimer(50);
	}
}

int checkAlarm(){
	for(int i=0;i<7;i++){
		if(clockvals[i]!=alarmvals[i]) return 0;
	}
	return 1;
}



