#include "../includes/httptester.h"

int     usage()
{
    printf("usage : ./httptester -d [ip destination]\n");
    printf("\t optional :\n");
    printf("\t\t -p [port] (default 80)\n");
    printf("\t\t -i [interval] (default 1 second)\n");
    printf("\t\t -m [METHODE] (default GET)\n");
    printf("\t\t -u [uri] (default /)\n");
    printf("\t\t -vh [vhost]\n");
    printf("\t\t -c [count] (default 4)\n");
    printf("\t\t -dp  [PostData HTTP]\n");
    printf("\t\t -h display this help.\n");
    return (0);    
}
