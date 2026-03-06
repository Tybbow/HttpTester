#include "../includes/httptester.h"

double time_diff(struct timeval x, struct timeval y)
{
    double x_ms, y_ms, diff;

    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
    diff = (double)y_ms - (double)x_ms;
    return ((diff / 1000));
}

void    statistics(double time)
{
    if (stats.min > time)
        stats.min = time;
    if (stats.max < time)
        stats.max = time;
    stats.avg = (stats.avg * (stats.trm - 1) + time) / stats.trm;
}

size_t  intlen(int value)
{
    size_t  i;

    i = 0;
    while (value)
    {
        value /= 10;
        i++;
    }
    return (i);
}

