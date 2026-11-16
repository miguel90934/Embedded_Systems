/**
 * @file led.h
 * @brief Delay Driver API for LPC1769.
 *
 * This module provides functions to generate time delays with millisecond
 * and microsecond resolution. It uses the SYSTICK timer for millisecond
 * delays and TIMER0 for microsecond delays.
 *
 * @version 1
 * @date 28 Sep 2026
 * @author Mike Rocha
 *
 * @note This is for the second project of SE
 * @warning Busy-wait delays block CPU execution.
 */

#ifndef LED_H_
#define LED_H_

#include <stdint.h>
#include <stdbool.h>

#include "LPC17xx.h"



/**
 * @page quick_api Quick API Reference
 *
 *  ### LED Management Driver (`led.h`)
 * | Function | Description | Example |
 * | :--- | :--- | :--- |
 * | @ref LED_Init | Configures the chosen LED with a starting state. | `LED_Init(RED, ON);` |
 * | @ref LED_On | Turns the specified LED on. | `LED_On(GREEN);` |
 * | @ref LED_Off | Turns the specified LED off. | `LED_Off(BLUE);` |
 * | @ref LED_Toggle | Switches the current state of the LED. | `LED_Toggle(RED);` |
 * | @ref LED_GetState | Returns `true` if ON, `false` if OFF. | `bool state = LED_GetState(GREEN);` |
 */
/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup LED - LED management Driver
 * @brief Driver to manage the built-in LED's
 *
 * Provides acess to turn off and on the choosen LED color/s
 * @{
 */

/*
 * ==========================================================================
 * ---------------------- LED MANAGEMENT DEFENITIONS ------------------------
 * ==========================================================================
 */
typedef enum {
RED = 0, /*!< Red LED Enumarator                    */
GREEN,   /*!< Green LED Enumarator                  */
BLUE     /*!< Blue LED Enumarator                   */
} LEDTypedef_t;

/* Defenitions for states */
#define ON true    /*!< ON State Definition             */
#define OFF false  /*!< OFF State Definition            */

static const int GREEN_LED = 1u << 25; /*!< Green LED Bit Shift for Data Block             */
static const int BLUE_LED = 1u << 26;  /*!< Blue LED Bit Shift for Data Block              */
static const int RED_LED = 1u << 22;   /*!< Red LED Bit Shift for Data Block               */



/**
 * @brief Initializes the indicated LED, with a starting state.
 *
 * @param led - indicate the choosen led color to acess its specific data block.
 *
 * @param state - indicate the state in which the led will be initialized in.
 */
void LED_Init(LEDTypedef_t led, bool state);


/**
 * @brief checks the current state of the chosen LED.
 *
 * @param led - indicate the chosen led colour to access its specific data block.
 * @return Returns Bool state of the LED, in which true equals ON and false OFF.
 */
bool LED_GetState(LEDTypedef_t led);


/**
 * @brief Turns ON the chosen LED.
 *
 * @param led - indicate the chosen led colour to access its specific data block.
 *
 */
void LED_On(LEDTypedef_t led);

/**
 * @brief Turns OFF the chosen LED.
 *
 * @param led - indicate the chosen led colour to access its specific data block.
 */
void LED_Off(LEDTypedef_t led);

/**
 * @brief Switches the state of the chosen LED.
 *
 * @param led - indicate the chosen led colour to access its specific data block.
 */
void LED_Toggle(LEDTypedef_t led);

/** @} */
/** @} */

#endif /* LED_H_ */
