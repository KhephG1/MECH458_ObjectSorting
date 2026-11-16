#include "myutils.h"
TargetStep object_type_to_target_step(ObjectType type)
{
    switch (type)
    {
    case ALUMINIUM:
        return CENTER_ALUMINIUM;
        break;
    case STEEL:
        return CENTER_STEEL;
        break;

    case WHITE:
        return CENTER_WHITE;
        break;
    case BLACK:
        return CENTER_BLACK;
        break;
    default:
        break;
    }
}

int16_t absolute(int16_t val) { return val > 0 ? val : -val; }