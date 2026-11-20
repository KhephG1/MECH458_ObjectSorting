/* lcd.h
 *  Character LCD driver (HD44780 compatible, 2 lines) for the ATmega2560
 * - 4 bit interface on PORTC: data on PC0-PC3 (LCD D4-D7), RS on PC6, RW on PC5
 *   and E on PC7, set by the LCD_* defines below
 * - Every byte sent polls the LCD busy flag (LCDBusyLoop) instead of using
 *   fixed delays
 * - Helpers to write a string or an integer at the cursor, or at an x, y
 *   position through the LCDWriteStringXY and LCDWriteIntXY macros
 * - Uses the PORT, PIN and DDR macros from myutils.h and the _delay_us and
 *   _delay_ms functions from util/delay.h (their timing depends on F_CPU)
 *
 * MECH 458, Fall 2026, Khephren Gould & Clifton Tollefson  */

#ifndef _LCD_H
#define _LCD_H
#include "myutils.h"
#include <avr/io.h>
#include <util/delay.h>
#ifndef F_CPU
//	#define F_CPU 12000000UL
//	#define F_CPU 1000000UL		//Frequency of uC - AT90USB1287
#define F_CPU 16000000UL // Frequency of uC - ATmega2560
#endif
/*_________________________________________________________________________________________*/

/************************************************
        LCD CONNECTIONS
   Uses PORTD.7 - Strobe, PORT.6 - RS, PORT.5 - RW, DataNibble PORTC.4 - PORTC.7
   Code Modified to use PORTC Only
*************************************************/

#define LCD_DATA C // Port PC0-PC3 are connected to D4-D7

#define LCD_E C       // Enable OR strobe signal
#define LCD_E_POS PC7 // Position of enable in above port

#define LCD_RS C
#define LCD_RS_POS PC6

#define LCD_RW C
#define LCD_RW_POS PC5

//************************************************

/* Cursor style flags for InitLCD(). LS_BLINK makes the cursor blink and
 * LS_ULINE shows the cursor as an underline. OR them together to use both.
 */
#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010

/***************************************************
                        F U N C T I O N S
****************************************************/

/* InitLCD
 * Initializes the LCD. Must be called once before any other LCD function.
 * Waits 30 ms for the LCD to power up, sets the data, E, RS and RW pins as
 * outputs, switches the LCD to 4 bit mode, turns the display on with the
 * requested cursor style, and sets the function to 4 bit, 2 line, 5x7 dots.
 *
 * style: LS_BLINK, LS_ULINE, or both OR'ed together
 *
 * The display is not cleared, so call LCDClear() afterwards if you need that.
 * It waits on the LCD busy flag, so it never returns if no LCD is connected.
 */
void InitLCD(uint8_t style);

/* LCDWriteString
 * Writes a string to the LCD starting at the current cursor position. The
 * cursor moves right after each character, and the text does not wrap onto
 * the next line.
 *
 * msg: A null terminated string
 */
void LCDWriteString(const char *msg);

/* LCDWriteInt
 * Writes a non-negative integer at the current cursor position, right
 * aligned in a field of field_length characters and padded on the left with
 * zeros (LCDWriteInt(7, 3) prints 007).
 *
 * val: Value to print, 0 to 32767. Negative values are not supported and
 *      print garbage characters.
 * field_length: Number of characters to print, 1-5. If the value has more
 *               digits than this, only the lowest field_length digits are
 *               printed. Passing -1 prints just the digits of the value with
 *               no padding, but do not use -1 with val = 0 (it reads past the
 *               end of the digit buffer).
 */
void LCDWriteInt(int val, unsigned int field_length);

/* LCDGotoXY
 * Moves the cursor so the next character written appears at column x of
 * line y.
 *
 * x: Column, 0-39 (a 16 character display shows columns 0-15). A value of 40
 *    or more is ignored and the cursor is not moved.
 * y: Line. 0 selects the first line and any non-zero value selects the
 *    second line.
 */
void LCDGotoXY(uint8_t x, uint8_t y);

// Low level

/* LCDByte
 * Sends one byte to the LCD in 4 bit mode, high nibble first and then low
 * nibble, and waits until the LCD has finished processing it (it calls
 * LCDBusyLoop() before returning). Normally used through LCDCmd() and
 * LCDData().
 *
 * c: The byte to send (a command code or a character)
 * isdata: 0 sends c as a command (RS low), non-zero sends it as character data
 *         (RS high)
 */
void LCDByte(uint8_t, uint8_t);

/* LCDCmd, LCDData
 * LCDCmd(c) sends the command code c to the LCD. LCDData(d) sends the
 * character d to be displayed at the cursor. Both wait for the LCD to finish.
 */
#define LCDCmd(c) (LCDByte(c, 0))
#define LCDData(d) (LCDByte(d, 1))

/* LCDBusyLoop
 * Waits until the LCD is no longer busy. Switches the data pins to inputs,
 * sets RW high and RS low to read the status, and reads the busy flag (as two
 * nibbles) until it clears. Then it sets RW low and puts the data pins back
 * to outputs. Called by LCDByte() after every byte, so there is rarely a
 * reason to call it directly.
 *
 * There is no timeout: if the LCD is missing, miswired or not powered, this
 * function never returns.
 */
void LCDBusyLoop();

/***************************************************
                        F U N C T I O N S     E N D
****************************************************/

/***************************************************
        M A C R O S
***************************************************/

/* LCDClear
 * Clears the whole display and moves the cursor to the first position.
 */
#define LCDClear() LCDCmd(0b00000001)

/* LCDHome
 * Moves the cursor back to the first position of line 1 without clearing the
 * display.
 */
#define LCDHome() LCDCmd(0b00000010);

/* LCDWriteStringXY
 * Moves the cursor to column x of line y (see LCDGotoXY) and writes the string
 * msg there.
 */
#define LCDWriteStringXY(x, y, msg)                                            \
    {                                                                          \
        LCDGotoXY(x, y);                                                       \
        LCDWriteString(msg);                                                   \
    }

/* LCDWriteIntXY
 * Moves the cursor to column x of line y (see LCDGotoXY) and writes the
 * integer val there with field length fl (see LCDWriteInt).
 */
#define LCDWriteIntXY(x, y, val, fl)                                           \
    {                                                                          \
        LCDGotoXY(x, y);                                                       \
        LCDWriteInt(val, fl);                                                  \
    }
/***************************************************/

/*_________________________________________________________________________________________*/
#endif