#include "../includes/httptester.h"

void    handler(int sig)
{
    signal(sig, SIG_IGN);
    if (!stats.rcv)
        stats.min = 0;
    printf("\n\n--- %s HTTPtester statistics ---\n", stats.host);
    printf("%.0f packets transmitted, %.0f received, %.2f%% packets loss\n", 
        stats.trm, stats.rcv, ((stats.trm - stats.rcv) / stats.trm) * 100);
    printf("rtt min/avg/max = %.2f/%.2f/%.2f ms\n", stats.min, stats.avg, stats.max);
    exit(1337);
}