/*
 * File:   washing_machine_function_def.c
 * Author: Priyanshi Singh
 *
 * Created on 1 July, 2025, 4:33 PM
 */


#include "main.h"
#include <xc.h>

/* global countdown */
volatile uint8_t min = 0, sec = 0;

/* tables */
static const char * const prog_tbl[] = {
 "Daily","Heavy","Delicates","Whites","Stain wash","Eco cottons",
 "Woolens","Bed sheets","Rinse+Dry","Dry only","Wash only","Aqua store"
};
static const char * const lvl_tbl[]={"AUTO","LOW","MEDIUM","HIGH","MAX"};
static const uint16_t time_tbl[12][5]={
{41,33,41,45,45},{50,40,50,57,57},{26,26,26,31,31},{76,76,76,76,76},
{96,96,96,96,96},{31,31,31,36,36},{29,29,29,29,29},{53,46,53,60,60},
{20,18,20,20,20},{6,6,6,6,6},{21,16,21,21,21},{50,50,50,50,50}
};

/* state vars */
static uint8_t prog_no=0, lvl_no=0;
static uint16_t total_s, wash_s, rinse_s, spin_s;

/* helpers */
static inline void lcd_clr(void){ clcd_write(CLEAR_DISP_SCREEN,INST_MODE); __delay_us(500); }

/* door message: waits till door closed 2 s, then lingers 1 s */
void door_status_check(void)
{
    if (RB0 == 0) {                                 /* door open */
        fan = off;  TMR2ON = 0;  buzzer = on;

        lcd_clr();
        clcd_print("DOOR : OPEN", LINE1(0));        /* 12 chars  */
        clcd_print("Please close", LINE2(0));       /* 12 chars  */

        /* wait until RB0 is HIGH for 2 full seconds */
        uint8_t stable = 0;
        while (stable < 40) {                       /* 40 × 50?ms */
            if (RB0) ++stable; else stable = 0;
            __delay_ms(50);
        }
        __delay_ms(1000);                           /* linger 1?s */

        buzzer = off;  fan = on;  TMR2ON = 1;
        lcd_clr();                                  /* caller will redraw */
    }
}


/* animation */
void power_ON_screen(void)
{
    const char blk=0xFF;
    for(uint8_t i=0;i<16;i++){clcd_putch(blk,LINE1(i));__delay_ms(70);}
    clcd_print("Powering ON",LINE2(3));
    clcd_print("Washing Machine",LINE3(1));
    for(uint8_t i=0;i<16;i++){clcd_putch(blk,LINE4(i));__delay_ms(70);}
}

/* screen 2 */
void washing_program_screen(uint8_t key)
{
    door_status_check();
    if(reset_flag==reset_prog){ lcd_clr(); reset_flag=reset_nil; }
    if(key==SW4){ prog_no=(prog_no+1)%12; lcd_clr(); }
    clcd_print("WASHING PROGRAM",LINE1(0));
    clcd_putch('*',LINE2(0));
    clcd_print(prog_tbl[prog_no],LINE2(1));
    clcd_print(prog_tbl[(prog_no+1)%12],LINE3(1));
    clcd_print(prog_tbl[(prog_no+2)%12],LINE4(1));
}

/* screen 3 */
void water_level_screen(uint8_t key)
{
    door_status_check();
    if(reset_flag==reset_level){ lcd_clr(); reset_flag=reset_nil; }
    if(key==SW4){ lvl_no=(lvl_no+1)%5; lcd_clr(); }
    clcd_print("WATER LEVEL",LINE1(0)); clcd_putch('*',LINE2(0));
    clcd_print(lvl_tbl[lvl_no],LINE2(1));
    clcd_print(lvl_tbl[(lvl_no+1)%5],LINE3(1));
    clcd_print(lvl_tbl[(lvl_no+2)%5],LINE4(1));
}

/* set initial time */
void set_time(void){ uint16_t s=time_tbl[prog_no][lvl_no]; min=s/60; sec=s%60; }

/* screen 4 / 5 */
void start_screen(uint8_t key)
{
    door_status_check();

    static uint8_t started=0;
    if(reset_flag==reset_start){
        lcd_clr(); started=0;
        clcd_print("Prog:",LINE2(0)); clcd_print(prog_tbl[prog_no],LINE2(6));
        clcd_print("TIME:",LINE3(0)); clcd_putch(min/10+'0',LINE3(6));
        clcd_putch(min%10+'0',LINE3(7)); clcd_putch(':',LINE3(8));
        clcd_putch(sec/10+'0',LINE3(9)); clcd_putch(sec%10+'0',LINE3(10));
        __delay_ms(1500); lcd_clr();
        clcd_print("FUNCTION:",LINE1(0)); clcd_print("Time",LINE2(0));
        clcd_print("SW5:START",LINE3(0)); clcd_print("SW6:PAUSE",LINE4(0));
        reset_flag = reset_nil;
    }

    /* single short press to start */
    if(!started && key==SW5){
        total_s=min*60+sec;
        wash_s=total_s*46/100; rinse_s=total_s*12/100; spin_s=total_s-wash_s-rinse_s;
        TMR2ON=1; fan=on; started=1;
    }

    if(started){
        uint16_t elapsed=total_s-(min*60+sec);
        const char *ph="wash ";
        if(prog_no<=7){
            if(elapsed>=wash_s+rinse_s) ph="spin ";
            else if(elapsed>=wash_s) ph="rinse";
        }else if(prog_no==8) ph=(elapsed<total_s*40/100)?"rinse":"spin ";
        else if(prog_no==9) ph="spin ";
        clcd_print(ph,LINE1(10));

        clcd_putch(min/10+'0',LINE2(6)); clcd_putch(min%10+'0',LINE2(7));
        clcd_putch(':',LINE2(8)); clcd_putch(sec/10+'0',LINE2(9)); clcd_putch(sec%10+'0',LINE2(10));

        if(key==SW6){ fan=off; TMR2ON=0; started=0; }

        if(min==0&&sec==0&&started){
            lcd_clr(); fan=off; buzzer=on; clcd_print("Program complete", LINE1(0));   /* 16 chars */
clcd_print("Remove clothes",   LINE2(0));   /* 14 chars */
 __delay_ms(2000); buzzer=off;
            reset_flag=reset_prog; started=0;
        }
    }
}
