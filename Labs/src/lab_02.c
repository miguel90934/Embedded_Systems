/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */



#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "led.h"
#include "delay.h"
#endif

#include <cr_section_macros.h>

int LAB_02(void)
{
	LED_Init(GREEN, false);
	LED_Init(RED, false);
	LED_Init(BLUE, false);
	DELAY_Init();
	uint32_t tick = 0U;
	while(1)
	{
		//1
		tick = DELAY_GetMillis();
		while(DELAY_GetElapsedMillis(tick)< 5000)
		{
			LED_Toggle(RED);
			DELAY_Milliseconds(500);
		}
		//2-
		LED_Off(RED);
		LED_On(GREEN);
		DELAY_Milliseconds(2000);
		//3-
		LED_Off(GREEN);


	}
	/*
	if(LED_GetState(GREEN)==false)
	{
		LED_Init(BLUE, true);
	}*/
	//LED_On(RED);
	//LED_Toggle(GREEN);
}
