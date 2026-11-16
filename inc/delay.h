/**
 * @file delay.h
 * @brief Delay Driver API for LPC1769.
 *
 * This module provides functions to generate time delays with millisecond
 * and microsecond resolution. It uses the SYSTICK timer for millisecond
 * delays and TIMER0 for microsecond delays.
 *
 * @version 1
 * @date 28 Sep 2026
 * @author Mike
 *
 * @note This is for the second project of SE
 * @warning Busy-wait delays block CPU execution.
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>
#include <stdbool.h>

#include "LPC17xx.h"

/**
 * @page quick_api Quick API Reference
 *
 * ### Timing and Delay Driver (`delay.h`)
 * | Function | Description | Example |
 * | :--- | :--- | :--- |
 * | @ref DELAY_Init | Initializes the SYSTICK and TIMER0 modules. | `DELAY_Init();` |
 * | @ref DELAY_Milliseconds | Blocks execution for a specified number of ms. | `DELAY_Milliseconds(50);` |
 * | @ref DELAY_Microseconds | Blocks execution for a specified number of us. | `DELAY_Microseconds(100);` |
 * | @ref DELAY_GetMillis | Returns total system uptime in milliseconds. | `uint32_t t = DELAY_GetMillis();` |
 * | @ref DELAY_GetElapsedMillis | Calculates time passed since a start timestamp. | `uint32_t elapsed = DELAY_GetElapsedMillis(start);` |
 */

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup DELAY - Timing and Delay Driver
 * @brief Driver to generate delays
 *
 * Provides millisecond and microsecond delay functions.
 * @{
 */


/**
 * @defgroup DELAY_MACROS Timer Register Macros
 * @brief Bit position definitions for Timer Registers.
 * @{
 */

/* Bit Map for TCR */
#define ENABLE_BIT_POS    0u  /*!< Bit 0: Counter Enable                   */
#define RESET_BIT_POS     1u  /*!< Bit 1: Counter Reset/                   */

/* Bit Map for MCR */
#define MR0I_BIT_POS      0u  /*!< Bit 0: Interrupt on MR0                    */
#define MR0R_BIT_POS      1u  /*!< Bit 1: Reset on MR0                  */

/* Definitions for clock choice*/
#define Default_Sysclk  (1u << 12)  /*!< Sets Bits to 01 for the 100MHz clk   	*/
#define Sysclk_div4     (0u << 12)  /*!< Sets Bits to 00 for the 100MHz/4 clk	*/
#define Sysclk_div2     (2u << 12)  /*!< Sets Bits to 10 for the 100MHz/2 clk 	*/
#define TIMER2_MASK  	(3u << 12)	/*!< Mask to Select only the Bits for the Timer2(Bits 12:13)	*/

/* Bit Map for PCON */
#define PCONP_PCTIM0_BIT  1u  /*!< Bit 1: Timer0 Power/Clock Enable                    */
#define PCONP_PCTIM2_BIT  (1u << 22) /*!< Bit 22: Timer2 Power/Clock Enable.(Pag.65 Doc)      */
/** @} */ // DELAY_MACROS


/**
 * @brief Initializes the delay system.
 *
 * Configures the SYSTICK timer for 1 ms an 1us resolution delays.
 *
 * @retval 0  Initialization successful
 * @retval -1 Initialization failed
 */
int DELAY_Init(void);

/**
 * @brief Waits for a specified number of milliseconds.
 * @note changed the condition from < millis to <= millis, now its more accurate.
 * @param millis Delay time in milliseconds.
 */
void DELAY_Milliseconds(uint32_t millis);

/**
 * @brief Gets elapsed time in milliseconds.
 *
 * @param start - Start time (pass 0 to get current time).
 * @return Elapsed time in milliseconds.
 */
uint32_t DELAY_GetElapsedMillis(uint32_t start);

/**
 * @brief Gets time in milliseconds.
 *
 *
 * @return Elapsed time in milliseconds.
 */
uint32_t DELAY_GetMillis(void);

/**
 * @brief Waits for a specified number of Microseconds.
 * @note changed the condition from < waitUs to <= waitUs, now its more accurate.
 * @param waitUs Delay time in Microseconds.
 */
void DELAY_Microseconds(uint32_t waitUs);



/** @} */  // DELAY
/** @} */  // DRIVERS


#endif /* DELAY_H_ */
