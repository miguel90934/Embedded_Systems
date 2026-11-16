/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

/**
 * @file main.c
 * @brief Main application entry point for Project 2.
 */

/**
 * @mainpage Embedded Systems Project Documentation
 *
 * @section intro Introduction
 * Welcome to the documentation for the radio (SE 2026/2027).
 * This project implements modular drivers for an LPC1769 microcontroller, featuring:
 * - 4-Bit LCD Driver (HD44780U)
 * - Timing & Delay Driver (SYSTICK / Timer0)
 * - LED Management Driver
 *
 * See the @ref quick_api for a quick reference guide to all driver functions.
 */


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "lab_01.h"
#include "lab_02.h"
#include "lab_03.h"
#include "lab_05.h"
#include "lab_06.h"
#include "lab_07.h"
#include "PWM.h"


#include "led_dim.h"

#endif

#include <cr_section_macros.h>

int main(void)
{
	LAB_07();
}
