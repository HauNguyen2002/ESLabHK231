/*
 * global.h
 *
 *  Created on: Dec 9, 2023
 *      Author: ASUS
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"
#include "ds3231.h"
#include "lcd.h"
#include "button.h"

#define AUTO_M	0
#define MANUAL_M	1
#define ALARM_M	2

#define FLAG_AUTO	flag_timer2[0]
#define FLAG_BUT_CD	flag_timer2[1]
#define FLAG_CK		flag_timer2[2]
#define	FLAG_BLINK_NUM	flag_timer2[3]
#define FLAG_AUTO_INC	flag_timer2[4]
#define FLAG_HOLD_BUT_CD	flag_timer2[5]

uint8_t clockvals[];
uint8_t alarmvals[];
uint8_t mode;
uint8_t flag_inc_press,flag_hold_press;

void updateTime();
void updateAlarm();
void displayTime();
#endif /* INC_GLOBAL_H_ */
