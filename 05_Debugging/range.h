#ifndef RANGE_H
#define RANGE_H

typedef struct range
{
    int start;
    int stop;
    int step;

    int value;

} range;

void range_init(range *);
void range_next(range *);
int range_run(range *);
int range_get(range *);

#endif