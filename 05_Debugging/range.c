#include "range.h"

void range_init(range *i)
{
    i->value = i->start;
};

void range_next(range *i)
{
    i->value += i->step;
};

int range_get(range *i)
{
    return i->value;
};

int range_run(range *i)
{
    return i->value < i->stop;
};