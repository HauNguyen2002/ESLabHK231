/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

#define TIMER_CYCLE_2 1
#define MAX_SOFTWARE_TIMER	10
//software timer variable
uint16_t flag_timer2[MAX_SOFTWARE_TIMER];
uint16_t timer2_counter[MAX_SOFTWARE_TIMER];
uint16_t timer2_MUL[MAX_SOFTWARE_TIMER];

/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */
void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}


/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */

//[0]
void setTimer2(uint16_t duration){
	timer2_MUL[0] = duration/TIMER_CYCLE_2;
	timer2_counter[0] = timer2_MUL[0];
	flag_timer2[0] = 0;
}

//[1]
void setLightAutoTimer(uint16_t duration){
	timer2_MUL[1] = duration/TIMER_CYCLE_2;
	timer2_counter[1] = timer2_MUL[1];
	flag_timer2[1] = 0;
}

//[2]
void setLightManualTimer(uint16_t duration){
	timer2_MUL[2] = duration/TIMER_CYCLE_2;
	timer2_counter[2] = timer2_MUL[2];
	flag_timer2[2] = 0;
}

//[3]
void setButCooldownTimer(uint16_t duration){
	timer2_MUL[3] = duration/TIMER_CYCLE_2;
	timer2_counter[3] = timer2_MUL[3];
	flag_timer2[3] = 0;
}


void timer2Run(){
	for(int i=0;i<MAX_SOFTWARE_TIMER;i++){
		if(timer2_counter[i]>0) timer2_counter[i]--;
		if(timer2_counter[i]==0) flag_timer2[i]=1;
	}
}
/**
  * @brief  Timer interrupt routine
  * @param  htim TIM Base handle
  * @note	This callback function is called by system
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		timer2Run();
	}
}

