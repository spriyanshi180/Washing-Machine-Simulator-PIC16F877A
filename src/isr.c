/*
 * File:   isr.c
 * Author: Priyanshi Singh
 *
 * Created on 1 July, 2025, 4:29 PM
 */


/* isr.c ? stable countdown + 50?ms tick */

#include <xc.h>
#include "main.h"

volatile uint8_t tick_50ms = 0;
volatile uint8_t reset_flag = reset_prog;

void init_timer2(void)
{
    T2CON = 0x7C; PR2 = 249; TMR2 = 0;     /* 50 ms base */
    TMR2IE = 1; PEIE = 1; GIE = 1; TMR2ON = 1;
}

void __interrupt() isr(void)
{
    static uint8_t t50 = 0;    /* 0?3 */
    static uint16_t s_cnt = 0; /* 0?19 */
    extern volatile uint8_t min, sec;

    if (TMR2IF) {
        TMR2IF = 0;
        if (++t50 == 4) { t50 = 0; tick_50ms = 1;
            if (++s_cnt == 20) { s_cnt = 0;
                if (min || sec) {
                    if (sec == 0) { sec = 59; --min; }
                    else --sec;
                }
            }
        }
    }
}
