#include "../includes/httptester.h"

size_t    request(t_opts *opts)
{
    int     s;
    struct  sockaddr_in server;
    char    server_reply[200];

    s = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = inet_addr(opts->dst);
    server.sin_family = AF_INET;
    server.sin_port = htons(opts->port);
    connect(s, (struct sockaddr *)&server, sizeof(server));
    send(s, opts->request, strlen(opts->request), 0);
    recv(s, server_reply, 200, 0);
    close(s);
    return (200);
}
