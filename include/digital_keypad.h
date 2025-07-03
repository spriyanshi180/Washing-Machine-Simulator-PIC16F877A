/* 
 * File:   digital_keypad.h
 * Author: Priyanshi Singh
 *
 * Created on 15 June, 2025, 8:22 PM
 */

#ifndef DIGITAL_KEYPAD_H
#define DIGITAL_KEYPAD_H
#define INPUT_LINES  0x3F
#define ALL_RELEASED 0x3F
#define SW1 0x3E
#define SW2 0x3D
#define SW3 0x3B
#define SW4 0x37
#define SW5 0x2F
#define SW6 0x1F
#define LONG_FLAG 0x40                 /* used only for SW4 hold */
void init_digital_keypad(void);
unsigned char read_digital_keypad(void);
#endif
