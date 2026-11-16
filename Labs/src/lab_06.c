/**
 * @file    main.c
 * @brief   Lab 06 test program: BUTTONS (Wait/Read) and RTC (clock + alarm).
 */
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "LPC17xx.h"
#include "delay.h"
#include "lcd.h"
#include "buttons.h"
#include "rtc.h"
#include "led.h"


int LAB_06(void)
{
    BUTTONS_TypeDef btn;

	LED_Init(GREEN, false);
	LED_Init(RED, false);
	LED_Init(BLUE, false);
    DELAY_Init();
    LCD_INIT();
    BUTTONS_Init();



    LCD_CLEAR();
    LCD_WRITE_STRING("Prima um botao");
    btn = BUTTONS_Wait();
    LCD_CLEAR();
    LCD_WRITE_STRING("Show");
    int go = 0;
    do{
    	btn = BUTTONS_Read();
		switch (btn) {
		  case BUTTONS_A:
				  LCD_WRITE_STRING("A");
				  break;
		  case BUTTONS_B:
			  	  LCD_WRITE_STRING("B");
			  	  break;
		  case BUTTONS_C:
			  LCD_WRITE_STRING("C");
			  go = 1;
			  break;
		  default:
			  	  LCD_WRITE_STRING("NADA");

		 while (BUTTONS_Read() != BUTTONS_NONE) { }
		 LCD_CLEAR();
		}
    }while(go==0);
    go = 0;
    DELAY_Milliseconds(1500);
    while (BUTTONS_Read() != BUTTONS_NONE) { }

    struct tm start = { .tm_year = 126, .tm_mon = 10, .tm_mday = 2,   /* 2026-11-02 */
                        .tm_hour = 12,  .tm_min = 0,  .tm_sec = 0 };
    time_t t0 = mktime(&start);

    char MY_TIME[50];

    RTC_Init(t0);

    //time_t tAlarm = t0 + (3 * 60);
    time_t tAlarm = t0 + (1 * 20);
    struct tm alarm = *gmtime(&tAlarm);
    RTC_SetAlarm(&alarm);
    RTC_EnableAlarm();

    bool alarmOn = true;

    LCD_CLEAR();
    struct tm now;


    while (1) {


    	RTC_GetTimeDate(&now);
        btn = BUTTONS_Read();

        if ((btn & BUTTONS_C) && alarmOn) {
            RTC_DisableAlarm();
            alarmOn = false;
        }

        if (alarmOn && RTC_AlarmTriggered()) {
            LED_On(GREEN);
            DELAY_Milliseconds(2000);
            LED_Off(GREEN);
            alarmOn = false;
        }

        strftime(MY_TIME, sizeof(MY_TIME), "%d/%m %H:%M:%S", &now);
        LCD_CLEAR();
        LCD_WRITE_STRING(MY_TIME);

        DELAY_Milliseconds(100);
    }
}
