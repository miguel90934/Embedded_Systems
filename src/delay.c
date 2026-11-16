#include <cr_section_macros.h>
#include <delay.h>
#include <stdio.h>


#define SYSTICK_TICKS_1MS (SystemCoreClock / 1000U)/*!< Define 1MS TickRate            */

static volatile uint32_t tick = 0U; /*!< RunTime Tick            */

/**
 * @brief SysTick Interrupt Service Routine
 * Executes every 1 ms when SysTick counter reaches 0.
 */
void SysTick_Handler(void)
{
    tick++;
}

int DELAY_Init(void)
{
    SystemCoreClockUpdate();
    tick = 0U;
    // Returns 0 on success, -1 if ticks exceed 24-bit max limit (0xFFFFFF)
    if (SysTick_Config(SYSTICK_TICKS_1MS) != 0U) {
        return -1;
    }

    LPC_SC->PCONP |= PCONP_PCTIM2_BIT; /*!< Turn on Peripheral Timer2 */
    LPC_SC->PCLKSEL1 = (LPC_SC->PCLKSEL1 & ~TIMER2_MASK) | Sysclk_div4 ;      /*!< Sets PCLK_peripheral to CCLK/4(25MHz) */
    uint32_t pclk = SystemCoreClock / 4U;
    LPC_TIM2->PR = (pclk / 1000000U) - 1U;/*!< Math based on a given equation for the Prescaler config. PR =(fPCLK/1 MHz)− 1
     	 	 	 	 	 	 	 	 	 	   Sets the PR to 24 which equals to 1us */
    LPC_TIM2->TCR = (1u << RESET_BIT_POS);/*!< Reset the timer to clear the time(opcional) */
    LPC_TIM2->TCR = (1u << ENABLE_BIT_POS);/*!<Begin counter*/
    return 0;
}

uint32_t DELAY_GetMillis(void) {
return tick;
}

uint32_t DELAY_GetElapsedMillis(uint32_t start) {
return tick - start;
}


void DELAY_Milliseconds(uint32_t millis)
{
    uint32_t start = DELAY_GetMillis();

    while (DELAY_GetElapsedMillis(start) <= millis) {
        __WFI();
    }
}

void DELAY_Microseconds(uint32_t waitUs)
{
	uint32_t start;
	if (waitUs <= 0U) return;
	    //LPC_TIM2->TCR = (1u << RESET_BIT_POS);/*!< Reset the timer to clear the time */
		//LPC_TIM2->TCR = (1u << ENABLE_BIT_POS);/*!<Begin counter*/

	start = LPC_TIM2->TC;
	while ((LPC_TIM2->TC - start) <= waitUs) //Timer loop
	{

	}
	//LPC_TIM2->TCR = 0U;/*!<Stops the counter*/
}
