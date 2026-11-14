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