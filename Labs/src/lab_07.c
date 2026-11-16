/**
 * @file    lab_07.c
 * @brief   Lab 07: persistent data in FLASH sector 29.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "LPC17xx.h"
#include "delay.h"
#include "lcd.h"
#include "buttons.h"
#include "Flash.h"
#include "lab_07.h"

#define GROUP_NUMBER    2
#define GROUP_SURNAMES  "Rocha Silvestre"

typedef struct {
    uint32_t group;
    char     surnames[44];
} GroupData;

#define STORED      ((const GroupData *)SECTOR_POS)

static void ShowData(void)
{
    char line[64];

    LCD_CLEAR();
    if (FLASH_VerifyBlankData() != CMD_SUCCESS) {
        snprintf(line, sizeof(line), "G%u %s", (unsigned)STORED->group, STORED->surnames);
        LCD_WRITE_STRING(line);
    } else {
        LCD_WRITE_STRING("Sem dados");
    }
}

int LAB_07(void)
{
    BUTTONS_TypeDef btn;
    GroupData data;

    DELAY_Init();
    LCD_INIT();
    BUTTONS_Init();

    ShowData();

    while (1) {
        btn = BUTTONS_Read();

        if (btn == BUTTONS_A) {
            FLASH_EraseSector(29);
            ShowData();
            while (BUTTONS_Read() != BUTTONS_NONE) { }
        }
        else if (btn == BUTTONS_B) {
            if (FLASH_VerifyBlankData() == CMD_SUCCESS) {
                memset(&data, 0xFF, sizeof(data));
                data.group = GROUP_NUMBER;
                strcpy(data.surnames, GROUP_SURNAMES);

                if (FLASH_WriteData((void *)SECTOR_POS, &data, sizeof(data)) == CMD_SUCCESS){
                	if(FLASH_VerifyData((void *)SECTOR_POS, &data, sizeof(data)) == CMD_SUCCESS){
                		ShowData();
                    }else {
                        LCD_CLEAR();
                        LCD_WRITE_STRING("Erro verify");
                    }
                } else {
                    LCD_CLEAR();
                    LCD_WRITE_STRING("Erro escrita");
                }
            }
            while (BUTTONS_Read() != BUTTONS_NONE) { }
        }
        DELAY_Milliseconds(20);
    }
}
