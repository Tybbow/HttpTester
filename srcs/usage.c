#include "../includes/httptester.h"

int     usage()
{
    printf("usage : ./httptester -d [ip destination]\n");
    printf("\t optional :\n");
    printf("\t\t -p   [port]          (default 80)\n");
    printf("\t\t -i   [interval]      (default 1 second)\n");
    printf("\t\t -m   [METHOD]        (default GET)\n");
    printf("\t\t -u   [uri]           (default /)\n");
    printf("\t\t -vh  [vhost]\n");
    printf("\t\t -c   [count]         (default 4)\n");
    printf("\t\t -dp  [PostData HTTP]\n");
    printf("\t\t -ssl                 (force HTTPS, auto if port 443)\n");
    printf("\t\t -h   display this help.\n");
    return (0);
}
