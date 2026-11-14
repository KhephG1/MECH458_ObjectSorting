#ifndef MYUTILS_H
#define MYUTILS_H

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
    CENTER_ALUMINIUM = 50,
    CENTER_WHITE = 100,
    CENTER_STEEL = 150
} TargetStep;

TargetStep object_type_to_target_step(ObjectType type);
#endif
