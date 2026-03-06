#include "../includes/httptester.h"

t_stats	stats;

void    launch(t_opts *opts)
{
    struct  timeval before, after;
    double  time;
    size_t  code;
    int     sequence;

    sequence = 1;
    while (opts->count)
    {
        gettimeofday(&before, NULL);
        stats.trm++;

        if (opts->ssl)
            code = request_ssl(opts);
        else
            code = request(opts);

        stats.rcv++;
        gettimeofday(&after, NULL);
        time = time_diff(before, after);
        statistics(time);
        printf("from (%s): response: (%ld) http_seq=%d time=%.2f ms\n",
            opts->dst, code, sequence, time);
        usleep(1000000 * opts->interval);
        sequence++;
        if (opts->count > 0)
            opts->count--;
    }
}

int     main(int ac, char **av)
{
    t_opts  *opts;

    opts = NULL;
    opts = initOpts();
    getOpts(ac, av, &opts);
    if (!opts->dst || opts->help || !checkOpts(opts))
        return (usage());
    signal(SIGINT, (void (*)(int))handler);

    if (opts->ssl)
        printf(GRN "[+] " RST "Mode: HTTPS (port %d)\n\n", opts->port);
    else
        printf(GRN "[+] " RST "Mode: HTTP  (port %d)\n\n", opts->port);

    launch(opts);
    handler(SIGINT);
    free(opts);
    return (0);
}
