/* myutils.h
 *  Shared helper definitions for the ATmega2560 sorting project
 * - PORT(x), PIN(x) and DDR(x) macros that build a register name from a port
 *   letter, so PORT(A) expands to PORTA
 * - State enum for the main state machine (polling, reflective, bucket,
 *   paused, rampdown)
 * - ObjectType enum for the four object classes (black, aluminium, white,
 *   steel), numbered 0 to 3 to match the row and column order of
 *   rotation_table
 * - table_entry struct holding the step count and direction of one move in
 *   rotation_table
 *
 * MECH 458, Fall 2026, Khephren Gould & Clifton Tollefson  */

#ifndef MYUTILS_H
#define MYUTILS_H
#include "avr/io.h"
#include <stdlib.h>
#define _CONCAT(a, b) a##b
#define PORT(x) _CONCAT(PORT, x)
#define PIN(x) _CONCAT(PIN, x)
#define DDR(x) _CONCAT(DDR, x)

typedef enum
{
    POLLING = 0,
    REFLECTIVE,
    BUCKET,
    PAUSED,
    RAMPDOWN
} State;

typedef enum
{
    BLACK = 0,
    ALUMINIUM,
    WHITE,
    STEEL
} ObjectType;

typedef struct
{
    uint8_t steps;
    uint8_t dir;
} table_entry;

#endif
