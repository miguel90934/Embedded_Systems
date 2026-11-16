#include "LPC17xx.h"
#include "buttons.h"

#define BTN_A_PIN   (1u << 2)    /* P0.2  */
#define BTN_B_PIN   (1u << 3)    /* P0.3  */
#define BTN_C_PIN   (1u << 21)   /* P0.21 */
#define BTN_MASK    (BTN_A_PIN | BTN_B_PIN | BTN_C_PIN)

#define PIN02_03_MASK  (0xFu << 4)   /* PINSEL0/PINMODE0 bits 7:4  (P0.2, P0.3) */
#define PIN21_MASK     (0x3u << 10)  /* PINSEL1/PINMODE1 bits 11:10 (P0.21)     */

void BUTTONS_Init(void)
{
    LPC_PINCON->PINSEL0 &= ~PIN02_03_MASK;       /* GPIO function */
    LPC_PINCON->PINSEL1 &= ~PIN21_MASK;

    LPC_PINCON->PINMODE0 &= ~PIN02_03_MASK;       /* 00 = pull-up */
    LPC_PINCON->PINMODE1 &= ~PIN21_MASK;

    LPC_GPIO0->FIODIR &= ~BTN_MASK;              /* inputs */
}

BUTTONS_TypeDef BUTTONS_Read(void)
{
    uint32_t pins = ~LPC_GPIO0->FIOPIN;
    uint32_t state = BUTTONS_NONE;

    if (pins & BTN_A_PIN) state |= BUTTONS_A;
    if (pins & BTN_B_PIN) state |= BUTTONS_B;
    if (pins & BTN_C_PIN) state |= BUTTONS_C;
    return (BUTTONS_TypeDef)state;
}

BUTTONS_TypeDef BUTTONS_Wait(void)
{
    BUTTONS_TypeDef state;
    do {
        state = BUTTONS_Read();
    } while (state == BUTTONS_NONE);
    return state;
}
