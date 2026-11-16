/**
 * @file lab_05.h
 * @brief Header file for Lab 05 module.
 *
 * Provides function declarations for the Lab 05 execution routines.
 *
 * @version 1.0
 * @date 26 Oct 2026
 * @author
 *
 * @note Part of SE Lab Exercises.
 */

#ifndef LAB_06_H_
#define LAB_06_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Executes the LCD manager test loop for Lab 05.
 *
 * Initializes the LCD in 4-bit mode and cyclically runs the following sequence:
 * 1. Displays "TESTE LCD" on the first line for 1 s.
 * 2. Displays "TESTE LCD" on the second line for 1 s.
 * 3. Repeats the alternation between the two lines for 10 s.
 * 4. Clears the display using LCD_CLEAR().
 * 5. Keeps the display blank for 500 ms.
 * 6. Repeats the sequence.
 *
 * @return Does not return (contains an infinite loop).
 */
int LAB_06(void);

#endif /* LAB_05_H_ */
