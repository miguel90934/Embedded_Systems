/**
 * @file lab_02.h
 * @brief Header file for Lab 02 module.
 *
 * Provides function declarations for the Lab 02 execution routines.
 *
 * @version 1.0
 * @date 28 Sep 2026
 * @author
 *
 * @note Part of Systems Engineering (SE) Lab Exercises.
 */

#ifndef LED_DIM_H_
#define LED_DIM_H_

#include <stdint.h>
#include <stdbool.h>
#include "led.h"
#include "delay.h"

/**
 * @brief Dimmer on a Led_on with timer.

 */

void LED_On_DIM(LEDTypedef_t led, int percentage, int timems);

#endif /* LED_DIM_H_ */
