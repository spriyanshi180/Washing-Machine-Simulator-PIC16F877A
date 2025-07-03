/*
 * File:   main.c
 * Author: Priyanshi Singh
 *
 * Created on 11 June, 2025, 7:57 PM
 */


#include "main.h"
#include "digital_keypad.h"

/* simple FSM */
enum { ST_SPLASH, ST_PROG, ST_LEVEL, ST_START } st = ST_SPLASH;

void init_config(void)
{
    init_digital_keypad();
    init_timer2();
    /* CLCD + port setup (use your existing code) */
}

void main(void)
{
    init_config();

    while(1){
        if(!tick_50ms) continue;
        tick_50ms = 0;

        uint8_t key = read_digital_keypad();

        switch(st)
        {
        case ST_SPLASH:
            if(key==SW5){ power_ON_screen(); reset_flag=reset_prog; st=ST_PROG; }
            break;

        case ST_PROG:
            washing_program_screen(key);
            if(key==(SW4|LONG_FLAG)){ reset_flag=reset_level; st=ST_LEVEL; }
            break;

        case ST_LEVEL:
            water_level_screen(key);
            if(key==(SW4|LONG_FLAG)){ set_time(); reset_flag=reset_start; st=ST_START; }
            break;

        case ST_START:
            start_screen(key);
            if(reset_flag==reset_prog) st=ST_PROG;   /* finished */
            break;
        }
    }
}
