#ifndef MYUTILS_H
#define MYUTILS_H
#include "avr/io.h"
#include "stdlib.h"
#define _CONCAT(a, b) a##b
#define PORT(x) _CONCAT(PORT, x)
#define PIN(x) _CONCAT(PIN, x)
#define DDR(x) _CONCAT(DDR, x)

typedef enum
{
    ALUMINIUM,
    STEEL,
    WHITE,
    BLACK
} ObjectType;

typedef enum
{
    CENTER_BLACK = 0,
    CENTER_ALUMINIUM = 150,
    CENTER_WHITE = 100,
    CENTER_STEEL = 50
} TargetStep;

int16_t absolute(int16_t val);
TargetStep object_type_to_target_step(ObjectType type);
#endif
