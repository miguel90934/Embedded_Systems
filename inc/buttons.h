/**
 * @file    buttons.h
 * @brief   Driver for the 3-Button Breakout module (buttons A, B and C), polling based.
 *
 * Pin assignment (GPIO port 0):
 *   - A -> P0.2
 *   - B -> P0.3
 *   - C -> P0.21
 *
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup BUTTONS - Button management Driver
 * @brief Driver to manage the buttons.
 *
 * @{
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#define BUTTONS_ACTIVE_LOW 1

/**
 * @brief Bitmap with the state of the buttons. Several bits may be set at the same time.
 */
typedef enum {
    BUTTONS_NONE = 0U,        /**< No button pressed. */
    BUTTONS_A    = (1U << 0), /**< Button A pressed. */
    BUTTONS_B    = (1U << 1), /**< Button B pressed. */
    BUTTONS_C    = (1U << 2)  /**< Button C pressed. */
} BUTTONS_TypeDef;

/**
 * @brief Initialises the GPIO pins used by buttons A, B and C as inputs.
 */
void BUTTONS_Init(void);

/**
 * @brief Reads the current state of the buttons (non blocking).
 * @return Bitmap of the pressed buttons, or BUTTONS_NONE if none is pressed.
 */
BUTTONS_TypeDef BUTTONS_Read(void);

/**
 * @brief Waits, by polling, until at least one button is pressed (blocking).
 * @note  Returns immediately if a button is already pressed when called.
 * @return Bitmap of the pressed buttons (never BUTTONS_NONE).
 */
BUTTONS_TypeDef BUTTONS_Wait(void);

/** @} */
/** @} */
#endif /* BUTTONS_H_ */

