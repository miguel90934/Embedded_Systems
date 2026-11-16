/**
 * @file lcd.h
 * @brief Display Driver to communicate with the HD44780U.
 *
 * @details This module provides functions to manage the LCD Display,operating in 4-bit mode.
 * By using a 4-bit interface instead of 8 bits, it reduces the required
 * microcontroller I/O pin count.
 * This driver cointains functions that enable writing and clearing the LCD.
 *
 * @version 1
 * @date 27 OCT 2026
 * @author Mike
 *
 *
 * @warning This driver is for 4-Bit use of the HD44780U.
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <stdbool.h>

#include "LPC17xx.h"
#include "lcd.h"
#include "delay.h"

/**
 * @page quick_api Quick API Reference
 *
 * ### 4-Bit LCD Driver Quick Reference
 *
 * | Function | Description | Example |
 * | :--- | :--- | :--- |
 * | @ref LCD_INIT | Initializes the LCD peripheral[cite: 60]. | `LCD_INIT();` |
 * | @ref LCD_CLEAR | Clears all content from the screen[cite: 60]. | `LCD_CLEAR();` |
 * | @ref LCD_LOCATE | Positions cursor at `(posx, posy)`[cite: 60]. | `LCD_LOCATE(0, 0);` |
 * | @ref LCD_WRITE_CHAR | Writes a single character[cite: 60]. | `LCD_WRITE_CHAR('A');` |
 * | @ref LCD_WRITE_STRING| Writes a null-terminated string[cite: 60]. | `LCD_WRITE_STRING("Hello");` |
 */

/**
 * @addtogroup DRIVERS
 * @{
 */


/**
 * @defgroup LCD - 4-bit LCD Driver
 * @brief Driver to display char, or strings.
 *
 * @code
 * // Example usage in main.c:
 *LCD_INIT();
    while(1) {
        for (int i = 0; i < 5; i++) {
            LCD_CLEAR();
            LCD_LOCATE(0, 0);
            LCD_WRITE_STRING("TESTE LCD");
            DELAY_ms(1000);

            LCD_CLEAR();
            LCD_LOCATE(0, 1);
            LCD_WRITE_STRING("TESTE LCD");
            DELAY_ms(1000);
        }
        LCD_CLEAR();
        DELAY_ms(500);
    }
 * @endcode
 *
 * @details Provides basic functions to utilize the LCD.
 * @{
 */

/**
 * @brief Allows for communication with the LCD.
 * @details This function switches the Enable bit of the LCD
 * to use the lcd with 4bits
 */
static void pulse_enable(void);

/**
 * @brief Writes 4bits to the LCD.
 * @details This function is intended to be used in sucession.
 *
 * @param bits - half the bits to send.
 * @return Void.
 */
static void write_4bit(unsigned char bits);

/**
 * @brief This function is used to send entire 8 bit commands.
 *
 * @param byte - the command to send.
 * 		  is_data - to confirm if we are sending data or sending instructions.
 * @return VOID.
 */
static void write_byte(unsigned char byte, int is_data);

/**
 * @brief Initializes the LCD peripheral.
 *
 * @details Executes a specific startup sequence necessary to start the peripheral
 * Configures the pins as outputs, sets the 4-bit interface,
 * then turns the display on, making it ready to accept data.
 * @pre Must have initializzed the delay beforehand.
 */
void LCD_INIT(void);

/**
 * @brief Writes one character at the current cursor position.
 * @details Sends the character byte to the LCD's Data Register in two sequencial 4-bit transfers.
 * @param Data Character to be written.
 */
void LCD_WRITE_CHAR(char Data);

/**
 * @brief Writes a complete text string to the display.
 * @details Takes a pointer to a null-terminated string and iterates each char sequentially.
 * @param DATA Pointer to the string.
 */
void LCD_WRITE_STRING(char *DATA);

/**
 * @brief Positions the cursor so that writing starts at that point.
 * @details Uses the Set DDRAM Address command (line 1 = 0x00, line 2 = 0x40)
 * @param posx Column (0..15).
 * @param posy Line (0..1). Out-of-range values are ignored.
 */
void LCD_LOCATE(int posx, int posy);

/**
 * @brief Clears all content from the Display.
 * @details anything elseIssues the Clear Display instruction
 */
void LCD_CLEAR(void);

/** @} */
#endif
