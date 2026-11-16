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

#ifndef LAB_02_H_
#define LAB_02_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Executes the Lab 02 application main loop.
 *
 * Initializes LEDs and Delay driver, then enters an infinite loop
 * toggling the RED LED for 5 seconds followed by turning the GREEN LED
 * ON for 2 seconds.
 *
 * @return Does not return (contains an infinite loop).
 */
int LAB_02(void);

#endif /* LAB_02_H_ */
