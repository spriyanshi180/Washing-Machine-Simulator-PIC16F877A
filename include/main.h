/* 
 * File:   main.h
 * Author: Priyanshi Singh
 *
 * Created on 12 June, 2025, 7:15 PM
 */

#ifndef MAIN_H
#define MAIN_H
#include <xc.h>
#include <stdint.h>

/* 20 MHz crystal */
#pragma config FOSC=HS, WDTE=OFF, PWRTE=OFF, BOREN=OFF, LVP=OFF
#define _XTAL_FREQ 20000000UL

/* CLCD helpers (your existing driver) */
#define LINE1(c) (0x80+(c))
#define LINE2(c) (0xC0+(c))
#define LINE3(c) (0x94+(c))
#define LINE4(c) (0xD4+(c))
void clcd_putch(char,uint8_t);
void clcd_print(const char*,uint8_t);
void clcd_write(uint8_t,uint8_t);
#define CLEAR_DISP_SCREEN 0x01
#define INST_MODE 0

/* Peripherals */
#define buzzer RB7
#define fan    RC2
#define on     1
#define off    0

/* 50 ms tick from ISR */
extern volatile uint8_t tick_50ms;

/* reset flags for screen functions */
enum { reset_nil, reset_prog, reset_level, reset_start };
extern volatile uint8_t reset_flag;

/* shared countdown */
extern volatile uint8_t min, sec;

/* prototypes */
void init_config(void);
void power_ON_screen(void);
void washing_program_screen(uint8_t);
void water_level_screen(uint8_t);
void start_screen(uint8_t);
void set_time(void);
void door_status_check(void);
#endif
