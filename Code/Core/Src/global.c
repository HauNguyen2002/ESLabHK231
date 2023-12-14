/*
 * global.c
 *
 *  Created on: Dec 9, 2023
 *      Author: ASUS
 */

#include "global.h"

uint8_t clockvals[]={0,50,20,2,20,11,23};
uint8_t alarmvals[]={15,50,20,2,20,11,23};

uint8_t mode=AUTO_M;

uint8_t flag_inc_press=0;
uint8_t flag_hold_press=0;

void updateAlarm(){
	ds3231_Write(ADDRESS_YEAR , alarmvals[6]);
	ds3231_Write(ADDRESS_MONTH , alarmvals[5]);
	ds3231_Write(ADDRESS_DATE , alarmvals[4]);
	ds3231_Write(ADDRESS_DAY , alarmvals[3]);
	ds3231_Write(ADDRESS_HOUR , alarmvals[2]);
	ds3231_Write(ADDRESS_MIN , alarmvals[1]);
	ds3231_Write(ADDRESS_SEC , alarmvals[0]);
}

void updateTime(){
	ds3231_Write(ADDRESS_YEAR , clockvals[6]);
	ds3231_Write(ADDRESS_MONTH , clockvals[5]);
	ds3231_Write(ADDRESS_DATE , clockvals[4]);
	ds3231_Write(ADDRESS_DAY , clockvals[3]);
	ds3231_Write(ADDRESS_HOUR , clockvals[2]);
	ds3231_Write(ADDRESS_MIN , clockvals[1]);
	ds3231_Write(ADDRESS_SEC , clockvals[0]);
}
void displayTime(){
	lcd_ShowIntNum (70 ,100 , ds3231_hours ,2, GREEN ,BLACK ,24) ;
	lcd_ShowIntNum (110 ,100 , ds3231_min ,2, GREEN ,BLACK ,24) ;
	lcd_ShowIntNum (150 ,100 , ds3231_sec ,2, GREEN ,BLACK ,24) ;
	lcd_ShowIntNum (20 ,130 , ds3231_day ,2, YELLOW ,BLACK ,24) ;
	lcd_ShowIntNum (70 ,130 , ds3231_date ,2, YELLOW ,BLACK ,24) ;
	lcd_ShowIntNum (110 ,130 , ds3231_month ,2, YELLOW ,BLACK ,24) ;
	lcd_ShowIntNum (150 ,130 , ds3231_year ,2, YELLOW ,BLACK ,24) ;
}
