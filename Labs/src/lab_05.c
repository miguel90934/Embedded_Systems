#include "lcd.h"
#include "delay.h"

int LAB_05(void)
{
	DELAY_Init();
    LCD_INIT();
    while(1) {
        for (int i = 0; i < 5; i++) {       /* 5 x 2 s = 10 s */
            LCD_CLEAR();
            LCD_LOCATE(0, 0);
            LCD_WRITE_STRING("TESTE LAB");
            DELAY_Milliseconds(1000);

            LCD_CLEAR();
            LCD_LOCATE(0, 1);
            LCD_WRITE_STRING("TESTE LAB");
            DELAY_Milliseconds(1000);
        }
        LCD_CLEAR();
        DELAY_Milliseconds(500);
    }
}
