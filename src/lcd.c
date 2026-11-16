#include "LPC17xx.h"
#include "lcd.h"
#include "delay.h"

/* ---- private pins: RS=P2.4 , E=P2.5 , DB4..DB7=P2.2..P2.5 (J2-42..45) ---- */
#define LCD_DATA_SHIFT  0
#define LCD_DATA_MASK   (0xFu << LCD_DATA_SHIFT)
#define LCD_RS_MASK     (1u << 4)
#define LCD_E_MASK      (1u << 5)
#define LCD_ALL_MASK    (LCD_RS_MASK | LCD_E_MASK | LCD_DATA_MASK)

/* ---- private HD44780 commands ---- */
#define CMD_CLEAR       0x01    /* 0b0000000001 */
#define CMD_ENTRY_MODE  0x06    /* I/D=1, S=0 */
#define CMD_DISPLAY_OFF 0x08
#define CMD_DISPLAY_ON  0x0E    /* 0b00001110: D=1, C=1, B=0 */
#define CMD_FUNC_4BIT   0x28    /* DL=0, N=1 (2 lines), F=0 */
#define CMD_SET_DDRAM   0x80

static void pulse_enable(void)
{
    LPC_GPIO2->FIOSET = LCD_E_MASK;
    DELAY_Microseconds(1);
    LPC_GPIO2->FIOCLR = LCD_E_MASK;
    DELAY_Microseconds(1);
}

static void write_4bit(unsigned char bits)
{
    LPC_GPIO2->FIOCLR = LCD_DATA_MASK;
    LPC_GPIO2->FIOSET = ((unsigned)(bits & 0xF)) << LCD_DATA_SHIFT;
    pulse_enable();
}


static void write_byte(unsigned char byte, int is_data)
{
    if (is_data) LPC_GPIO2->FIOSET = LCD_RS_MASK;
    else         LPC_GPIO2->FIOCLR = LCD_RS_MASK;
    write_4bit(byte >> 4);
    write_4bit(byte & 0xF);
}

void LCD_CLEAR(void)
{
    write_byte(CMD_CLEAR, 0);
    DELAY_Milliseconds(2);                        /* clear ~1.52 ms */
}

static void write_cmd(unsigned char cmd, int delayus)
{
	if(delayus <1)return; //necessário?
    write_byte(cmd, 0);
    DELAY_Microseconds(delayus);
}

void LCD_INIT(void)
{
    LPC_PINCON->PINSEL4 &= ~0x00000FFF;      /* P2.0..P2.5 as GPIO */
    LPC_PINCON->PINMODE4 &= ~0x00000FFF;     /* pull-ups on, not needed but clean */
    LPC_GPIO2->FIODIR |= LCD_ALL_MASK;
    LPC_GPIO2->FIOCLR  = LCD_ALL_MASK;

    DELAY_Milliseconds(20);                       /* power on: > 15 ms */
    write_4bit(0x3);  DELAY_Milliseconds(5);    /* > 4.1 ms */
    write_4bit(0x3);  DELAY_Microseconds(150);  /* > 100 us */
    write_4bit(0x3);  DELAY_Microseconds(50);
    write_4bit(0x2);  DELAY_Microseconds(50);   /* set 4-bit interface */

    write_cmd(CMD_FUNC_4BIT,50);
    write_cmd(CMD_DISPLAY_OFF,50);
    LCD_CLEAR();
    write_cmd(CMD_ENTRY_MODE,50);
    write_cmd(CMD_DISPLAY_ON,50);
}

void LCD_WRITE_CHAR(char Data)
{
    write_byte((unsigned char)Data, 1);
    DELAY_Microseconds(50);
}

void LCD_WRITE_STRING(char *DATA)
{
	int i = 0;

	if (DATA == 0) return;

	while (DATA[i] != '\0')
	{
		LCD_WRITE_CHAR(DATA[i]);
		i++;
	}

}

void LCD_LOCATE(int posx, int posy)
{
    if (posx < 0 || posx > 15 || posy < 0 || posy > 1) return;
    write_cmd(CMD_SET_DDRAM | ((posy ? 0x40 : 0x00) + posx),50);
}

