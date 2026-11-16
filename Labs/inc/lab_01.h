/**
 * @file lab_01.h
 * @brief Header file for Lab 01 Application Module (LPC1769).
 *
 * This header defines the public functions and configuration constants
 * for Lab 01, which uses the delay driver to perform timed tasks.
 *
 * @version 1.0
 * @date 28 Sep 2026
 * @author
 *
 * @note Part of the Systems Engineering (SE) Lab Exercises.
 */

#ifndef LAB_01_H_
#define LAB_01_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @addtogroup LABS
 * @{
 */

/**
 * @defgroup LAB_01_MACROS Configuration Macros
 * @{
 */

/* Example LED / Timing Constants for Lab 01 */
#define LAB01_BLINK_PERIOD_MS    500U   /*!< Default LED blink interval in ms */
#define LAB01_PULSE_WIDTH_US     100U   /*!< Microsecond delay pulse width    */

/** @} */ // LAB_01_MACROS

/**
 * @brief Lab 01, Exercises.
 *
 * Lab 01 sequence LED code.
 *
 * @retval 0  Initialization successful
 * @retval -1 Initialization failed
 */
int LAB_01(void);


/** @} */ // LAB_01

#endif /* LAB_01_H_ */
