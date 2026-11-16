/**
 * @file    rtc.c
 * @brief   Implementation of the RTC driver for the LPC17xx.
 *
 * Page numbers below refer to UM10360 (LPC176x/5x User manual, Rev. 4.1),
 * Chapter 27 "Real-Time Clock (RTC) and backup registers", pages 569 to 579.
 */
#include "LPC17xx.h"
#include "rtc.h"

/* ---- PCONP ----------------------------------- */
#define RTC_PORT     (1u << 9)    /* bit 9 PCRTC: RTC power/clock control bit */

/* ---- CCR (Table 510) --------------- */
#define CCR_CLKEN      (1u << 0)    /* 1 = time counters enabled; 0 = disabled so they can be initialised */
#define CCR_CTCRST     (1u << 1)    /* 1 = 1 Hz divider held in reset until this bit is cleared */
#define CCR_CCALEN     (1u << 4)    /* 1 = calibration counter disabled */
#define CCR_RUN        (CCR_CLKEN | CCR_CCALEN)

/* ---- ILR (Table 509) -------------- */
#define ILR_RTCCIF     (1u << 0)    /* counter increment interrupt;1 to clear */
#define ILR_RTCALF     (1u << 1)    /*  1 to clear */

/* ---- AMR (Table 512) ------------------ */
/* A bit set to 1 means that field is NOT compared. Bits: 0 SEC, 1 MIN, 2 HOUR,
   3 DOM, 4 DOW, 5 DOY, 6 MON, 7 YEAR. */
#define AMR_ALL        0xFFu                                    /* If all mask bits are set, then the alarm is disabled. */
#define AMR_IGNORED    ((1u << 0) | (1u << 4) | (1u << 5))      /* ignore SEC, DOW, DOY: compare
                                                                   minute, hour, day, month, year */

static volatile bool alarmArmed = false;   /* como nos slides  */
static volatile bool alarmFlag  = false;   /* como nos slides  */

void RTC_Init(time_t seconds)
{
    LPC_SC->PCONP |= RTC_PORT;

    /* 2. Clock (p.569, section 27.1 step 2).
          The only clock source is the 1 Hz output of the dedicated 32.768 kHz RTC
          oscillator (pins RTCX1/RTCX2, p.571), so there is nothing to select and
          the PLL / SystemCoreClock do not matter. Registers are accessed at CCLK/8.
          Table 510 note (p.573): the "NC" (not changed by reset) bits of CCR must be
          initialised when the RTC is first turned on, so we write the whole register:
          counters stopped (CLKEN=0), divider in reset (CTCRST=1), calibration off. */
    LPC_RTC->CCR  = CCR_CTCRST | CCR_CCALEN;

    /* Desligar CIIR */
    LPC_RTC->CIIR = 0;

    /* Alarm off */
    LPC_RTC->AMR  = AMR_ALL;

    /* Clear ILR */
    LPC_RTC->ILR  = ILR_RTCCIF | ILR_RTCALF;

    /* Ligar os interrupts */
    NVIC_EnableIRQ(RTC_IRQn);
    RTC_SetSeconds(seconds);
}

void RTC_GetTimeDate(struct tm *dateTime)
{
    uint32_t c0, c1, c2;

    	c0 = LPC_RTC->CTIME0;
        c1 = LPC_RTC->CTIME1;
        c2 = LPC_RTC->CTIME2;



    dateTime->tm_sec  =  c0        & 0x3F;
    dateTime->tm_min  = (c0 >> 8)  & 0x3F;
    dateTime->tm_hour = (c0 >> 16) & 0x1F;
    dateTime->tm_wday = (c0 >> 24) & 0x07;
    dateTime->tm_mday =  c1        & 0x1F;
    dateTime->tm_mon  = ((c1 >> 8) & 0x0F) - 1;
    dateTime->tm_year = ((c1 >> 16) & 0xFFF) - 1900;
    dateTime->tm_yday = (c2 & 0xFFF) - 1;
    dateTime->tm_isdst = 0;
}

void RTC_SetTimeDate(const struct tm *dateTime)
{
    struct tm t = *dateTime;
    t.tm_isdst = 0; //mete daylight savings a 0
    mktime(&t);

    LPC_RTC->CCR   = CCR_CTCRST | CCR_CCALEN;//parar o clock para podef escrever

    /* Time counter registers (p.578)*/
    LPC_RTC->SEC   = t.tm_sec;
    LPC_RTC->MIN   = t.tm_min;
    LPC_RTC->HOUR  = t.tm_hour;
    LPC_RTC->DOW   = t.tm_wday;
    LPC_RTC->DOM   = t.tm_mday;
    LPC_RTC->DOY   = t.tm_yday + 1;
    LPC_RTC->MONTH = t.tm_mon + 1;
    LPC_RTC->YEAR  = t.tm_year + 1900;

    LPC_RTC->CCR   = CCR_RUN;              /* CLKEN=1, CTCRST=0: começa o clk */
}

void RTC_SetSeconds(time_t seconds)
{
    struct tm t = *gmtime(&seconds);
    RTC_SetTimeDate(&t);
}

time_t RTC_GetSeconds(void)
{
    struct tm t;
    RTC_GetTimeDate(&t);
    return mktime(&t);
}

void RTC_SetAlarm(const struct tm *dateTime)
{
    /* Alarm register group (p.579)*/
    LPC_RTC->ALSEC  = 0;
    LPC_RTC->ALMIN  = dateTime->tm_min;
    LPC_RTC->ALHOUR = dateTime->tm_hour;
    LPC_RTC->ALDOM  = dateTime->tm_mday;
    LPC_RTC->ALDOW  = 0;
    LPC_RTC->ALDOY  = 0;
    LPC_RTC->ALMON  = dateTime->tm_mon + 1;
    LPC_RTC->ALYEAR = dateTime->tm_year + 1900;
}

void RTC_EnableAlarm(void)
{
    LPC_RTC->ILR = ILR_RTCALF;             /* limpa alarme */
    alarmArmed   = true;
    LPC_RTC->AMR = AMR_IGNORED;            /*liga o alarme paara os campos especficos */
}

void RTC_DisableAlarm(void)
{
    LPC_RTC->AMR = AMR_ALL;                /*desliga o alarme */
    alarmArmed   = false;
    alarmFlag    = false;
    LPC_RTC->ILR = ILR_RTCALF;			   /*limpa alarme */
}

bool RTC_AlarmTriggered(void)
{


    bool triggered;
    triggered = alarmFlag;
    alarmFlag = false;

    return triggered;
}

