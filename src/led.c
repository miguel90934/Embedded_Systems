
#include <cr_section_macros.h>
#include <led.h>
#include <stdio.h>

void LED_Init(LEDTypedef_t led, bool state)
{
	switch (led) {
	  case RED:
			LPC_PINCON->PINSEL1 &= (~(3 << 12));
			LPC_GPIO0->FIODIR |= RED_LED;
			if(state == ON)
			{
				LPC_GPIO0->FIOCLR = RED_LED;
			}else//Liga o LED
			{
				LPC_GPIO0->FIOSET = RED_LED;
			}
	    break;
	  case BLUE:
			LPC_PINCON->PINSEL7 &= (~(3 << 20));
			LPC_GPIO3->FIODIR |= BLUE_LED;
			if(state == ON)
			{
				LPC_GPIO3->FIOCLR = BLUE_LED;
			}else//Liga o LED
			{
				LPC_GPIO3->FIOSET = BLUE_LED;
			}
	    break;
	  case GREEN:
		LPC_PINCON->PINSEL7 &= (~(3 << 18));
		LPC_GPIO3->FIODIR |= GREEN_LED;
		if(state == ON)
		{
			LPC_GPIO3->FIOCLR = GREEN_LED;
		}else//Liga o LED
		{
			LPC_GPIO3->FIOSET = GREEN_LED;
		}
		break;
	  default:
	    // code block
	}
}

bool LED_GetState(LEDTypedef_t led)
{
	switch (led) {
		  case RED:
				if ((LPC_GPIO0->FIOPIN & RED_LED) == 0)
				{
					return true;
				}
				return false;
		    break;
		  case BLUE:
				if ((LPC_GPIO3->FIOPIN & BLUE_LED) == 0)
				{
					return true;
				}
				return false;
		    break;
		  case GREEN:
				if ((LPC_GPIO3->FIOPIN & GREEN_LED) == 0)
				{
					return true;
				}
				return false;
			break;
		  default:
		    // code block
			  return false;
	}
}

void LED_On(LEDTypedef_t led)
{
	switch (led) {
	  case RED:
		  LPC_GPIO0->FIOCLR = RED_LED;
	    break;
	  case BLUE:
		  LPC_GPIO3->FIOCLR = BLUE_LED;
	    break;
	  case GREEN:
		  LPC_GPIO3->FIOCLR = GREEN_LED;
		break;
	  default:
	    // code block
	}
}

void LED_Off(LEDTypedef_t led)
{
	switch (led) {
	  case RED:
		  LPC_GPIO0->FIOSET = RED_LED;
	    break;
	  case BLUE:
		  LPC_GPIO3->FIOSET = BLUE_LED;
	    break;
	  case GREEN:
		  LPC_GPIO3->FIOSET = GREEN_LED;
		break;
	  default:
	    // code block
	}
}

void LED_Toggle(LEDTypedef_t led)
{
	if(LED_GetState(led) == ON)
	{
		LED_Off(led);
	}else{
		LED_On(led);
	}
}
