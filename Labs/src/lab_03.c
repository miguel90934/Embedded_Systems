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

int LAB_03(void)
{
	DELAY_Init();
	LED_Init(GREEN, false);
	LED_Init(RED, false);
	LED_Init(BLUE, false);
	uint32_t tick = 0U;
	uint32_t elapsed = 0U;
	while(1)
	{
		 tick = DELAY_GetMillis();
		 DELAY_Microseconds(1000000);
		 elapsed = DELAY_GetElapsedMillis(tick);
		 if(elapsed >= 995 && elapsed <= 1005)LED_On(GREEN);else{LED_On(RED);}
		 DELAY_Milliseconds(2000);
		 LED_Off(GREEN);
		 LED_Off(RED);
	}
}
