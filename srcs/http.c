#include "../includes/httptester.h"

static size_t   parse_status_code(char *server_reply)
{
    char    *ptr;
    size_t  code;

    ptr = strchr(server_reply, ' ');
    if (!ptr)
        return (0);
    code = (size_t)atoi(ptr + 1);
    if (code < 100 || code > 599)
        return (0);
    return (code);
}

size_t    request(t_opts *opts)
{
    int             s;
    struct          sockaddr_in server;
    char            server_reply[512];
    ssize_t         bytes_received;
    size_t          code;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
        return (0);
    server.sin_addr.s_addr = inet_addr(opts->dst);
    server.sin_family = AF_INET;
    server.sin_port = htons(opts->port);
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        close(s);
        return (0);
    }
    send(s, opts->request, strlen(opts->request), 0);
    memset(server_reply, 0, sizeof(server_reply));
    bytes_received = recv(s, server_reply, sizeof(server_reply) - 1, 0);
    close(s);
    if (bytes_received <= 0)
        return (0);
    code = parse_status_code(server_reply);
    return (code);
}