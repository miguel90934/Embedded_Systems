/**
 * @file    rtc.h
 * @brief   Driver for the LPC17xx real-time clock and its alarm (interrupt driven).
 *
 * The alarm compares day of month, month, year, hour and minute only
 * (seconds, day of week and day of year are masked). It is one-shot: after it
 * fires it must be enabled again with RTC_EnableAlarm().
 *
 * @addtogroup DRIVERS
 * @{
 */
/**
 * @defgroup RTC - RTC management Driver
 * @brief Driver to initiate and manage the Real Time Clock.
 *
 * @{
 */

#ifndef RTC_H_
#define RTC_H_

#include <stdbool.h>
#include <time.h>

/**
 * @brief Initialises the RTC and starts it.
 * @param seconds Initial value, in seconds since 00:00:00 UTC of 1 January 1970.
 */
void RTC_Init(time_t seconds);

/**
 * @brief Reads the current date and time.
 * @param[out] dateTime Receives the current date and time.
 */
void RTC_GetTimeDate(struct tm *dateTime);

/**
 * @brief Sets the RTC date and time.
 * @param[in] dateTime New date and time (tm_wday and tm_yday are recomputed).
 */
void RTC_SetTimeDate(const struct tm *dateTime);

/**
 * @brief Sets the RTC from a number of seconds.
 * @param seconds Seconds since 00:00:00 UTC of 1 January 1970.
 */
void RTC_SetSeconds(time_t seconds);

/**
 * @brief Reads the RTC as a number of seconds.
 * @return Seconds since 00:00:00 UTC of 1 January 1970.
 */
time_t RTC_GetSeconds(void);

/**
 * @brief Programs the alarm time.
 * @param[in] dateTime Alarm instant. Only tm_mday, tm_mon, tm_year, tm_hour and tm_min are used.
 * @note  Does not enable the alarm; call RTC_EnableAlarm().
 */
void RTC_SetAlarm(const struct tm *dateTime);

/**
 * @brief Enables the programmed alarm and its interrupt.
 */
void RTC_EnableAlarm(void);

/**
 * @brief Disables the alarm. Any pending, not yet consulted, alarm indication is discarded.
 */
void RTC_DisableAlarm(void);

/**
 * @brief Tells whether the alarm occurred since the last call.
 * @return true if the alarm occurred since the last call; the internal flag is cleared by this call.
 */
bool RTC_AlarmTriggered(void);

/** @} */
/** @} */

#endif /* RTC_H_ */
