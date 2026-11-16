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
#include "led_dim.h"

#endif

#include <cr_section_macros.h>
/*
int PWM(void)
{
	DELAY_Init();
	LED_Init(GREEN, false);
	LED_Init(RED, false);
	LED_Init(BLUE, false);
	uint32_t tick = 0U;
	uint32_t elapsed = 0U;
	while(1)
	{
		 DELAY_Microseconds(990);
		 LED_On(GREEN);
		 DELAY_Microseconds(10);
		 LED_Off(GREEN);
	}
}*/

int PWM_TEST(void)
{
	LED_Init(GREEN, false);
	LED_Init(RED, false);
	LED_Init(BLUE, false);

	while(1)
	{


		LED_On_DIM(GREEN, 100, 500);

		LED_On_DIM(GREEN, 75, 500);

		LED_On_DIM(GREEN, 50, 500);

		LED_On_DIM(GREEN, 10, 500);

		LED_On_DIM(GREEN, 1, 500);

		LED_On_DIM(RED, 100, 500);

		LED_On_DIM(RED, 75, 500);

		LED_On_DIM(RED, 50, 500);

		LED_On_DIM(RED, 10, 500);

		LED_On_DIM(RED, 1, 500);

		LED_On_DIM(BLUE, 100, 500);

		LED_On_DIM(BLUE, 75, 500);

		LED_On_DIM(BLUE, 50, 500);

		LED_On_DIM(BLUE, 10, 500);

		LED_On_DIM(BLUE, 1, 500);
	}
}
