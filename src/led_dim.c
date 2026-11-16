
#include <cr_section_macros.h>
#include <led.h>
#include <delay.h>
#include <stdio.h>

void LED_On_DIM(LEDTypedef_t led, int percentage, int timems)
{
	if(percentage>100 || percentage < 1 )return;
	DELAY_Init();
	LED_Init(led, false);

	float high,low;
	high = 1000.0f*((float)percentage/100.0f);
	low = 1000.0f - high;


	uint32_t tick = 0U;
	tick = DELAY_GetMillis();
	while(DELAY_GetElapsedMillis(tick)< timems)
	{
		 DELAY_Microseconds(low);
		 LED_On(led);
		 DELAY_Microseconds(high);
		 LED_Off(led);
	}
	LED_Off(led);
}

