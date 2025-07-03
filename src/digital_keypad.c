/*
 * File:   digital_keypad.c
 * Author: Priyanshi Singh
 *
 * Created on 1 July, 2025, 4:28 PM
 */


/* key events now delivered on RELEASE  ----------------------------------
   ? SHORT press emitted once when key goes UP after ?100?ms down
   ? LONG  press (for SW4) after 5?s down, also emitted on key?UP         */

unsigned char read_digital_keypad(void)
{
    static unsigned char prev   = ALL_RELEASED;
    static unsigned char down   = 0;            /* ticks key held down   */
    static unsigned char armed  = 0;            /* 1=short,2=long armed  */

    unsigned char now = PORTB & INPUT_LINES;

    /* ---------- stable? ---------- */
    if (now == prev) {
        if (now != ALL_RELEASED && down < 255) ++down;
    } else {
        prev  = now;
        down  = 0;
        armed = 0;
    }

    /* ---------- key released ---------- */
    if (now == ALL_RELEASED) {
        if (armed) {                      /* event ready */
            unsigned char ret = armed == 1 ? prev : (prev | LONG_FLAG);
            armed = 0;  return ret;
        }
        return 0;
    }

    /* ---------- key still down ---------- */
    if (down == DEBOUNCE_TICKS && armed == 0)          armed = 1;        /* short armed  */
    if (down == LONG_TICKS     && prev == SW4)         armed = 2;        /* long armed   */

    return 0;
}
