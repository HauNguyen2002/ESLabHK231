///*
// * software_timer.c
// *
// *  Created on: Sep 24, 2023
// *      Author: HaHuyen
// */
//
#include "software_timer.h"

#define TIMER_CYCLE_2	1
#define MAX_SOFTWARETIMER	10

uint16_t flag_timer2[MAX_SOFTWARETIMER];
uint16_t timer2_counter[MAX_SOFTWARETIMER];
uint16_t timer2_MUL[MAX_SOFTWARETIMER];

void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}

void setAutoTimer(uint16_t duration){
	timer2_MUL[0] = duration/TIMER_CYCLE_2;
	timer2_counter[0] = timer2_MUL[0];
	flag_timer2[0] = 0;
}
void setbutCooldownTimer(uint16_t duration){
	timer2_MUL[1] = duration/TIMER_CYCLE_2;
	timer2_counter[1] = timer2_MUL[1];
	flag_timer2[1] = 0;
}

void setClockTimer(uint16_t duration){
	timer2_MUL[2] = duration/TIMER_CYCLE_2;
	timer2_counter[2] = timer2_MUL[2];
	flag_timer2[2] = 0;
}

void setblinkCLKnumTimer(uint16_t duration){
	timer2_MUL[3] = duration/TIMER_CYCLE_2;
	timer2_counter[3] = timer2_MUL[3];
	flag_timer2[3] = 0;
}

void setAutoIncTimer(uint16_t duration){
	timer2_MUL[4] = duration/TIMER_CYCLE_2;
	timer2_counter[4] = timer2_MUL[4];
	flag_timer2[4] = 0;
}

void setHoldButtonTimer(uint16_t duration){
	timer2_MUL[5] = duration/TIMER_CYCLE_2;
	timer2_counter[5] = timer2_MUL[5];
	flag_timer2[5] = 0;
}
void timer2Run(){
	for(int i=0;i<MAX_SOFTWARETIMER;i++){
		if(timer2_counter[i] > 0) timer2_counter[i]--;
		if(timer2_counter[i] == 0) flag_timer2[i] = 1;
	}
}

int counter=50;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
		timer2Run();
		if(counter>0) counter--;
		if(counter==0){
			button_Scan();
			counter=50;
		}
}



