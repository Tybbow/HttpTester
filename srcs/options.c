#include "../includes/httptester.h"

void    initStats(char *dst)
{
    stats.min = DBL_MAX;
    stats.avg = 0;
    stats.max = 0;
    stats.trm = 0;
    stats.rcv = 0;
    memset(stats.host, 0, 20);
    strcpy(stats.host, dst);
}

t_opts  *initOpts()
{
    t_opts *opts;

    opts = malloc(sizeof(t_opts));
    if (!opts)
        return (NULL);
    opts->dst = NULL;
    opts->method = NULL;
    opts->uri = NULL;
    opts->vhost = NULL;
    opts->postdata = NULL;
    opts->port = 80;
    opts->count = 4;
    opts->interval = 1;
    opts->help = 0;
    opts->ssl = 0;
    return (opts);
}

void    getOpts(int ac, char **av, t_opts **opts)
{
    int i;

    i = 0;
    while (i < ac)
    {
        if (!strcmp(av[i], "-d"))
            (*opts)->dst = av[i + 1];
        if (!strcmp(av[i], "-u"))
            (*opts)->uri = av[i + 1];
        if (!strcmp(av[i], "-m"))
            (*opts)->method = av[i + 1];
        if (!strcmp(av[i], "-vh"))
            (*opts)->vhost = av[i + 1];
        if (!strcmp(av[i], "-dp"))
            (*opts)->postdata = av[i + 1];
        if (!strcmp(av[i], "-c"))
            (*opts)->count = atoi(av[i + 1]);
        if (!strcmp(av[i], "-p"))
            (*opts)->port = atoi(av[i + 1]);
        if (!strcmp(av[i], "-i"))
            (*opts)->interval = atof(av[i + 1]);
        if (!strcmp(av[i], "-h"))
            (*opts)->help = 1;
        if (!strcmp(av[i], "-ssl"))
            (*opts)->ssl = 1;
        i++;
    }

    if ((*opts)->port == 443 && !(*opts)->ssl)
        (*opts)->ssl = 1;
}

size_t  lengthRequest(t_opts *opts)
{
    size_t requestlength;

    requestlength = 0;
    requestlength += strlen(opts->method);
    requestlength += strlen(" ");
    requestlength += strlen(opts->uri);
    requestlength += strlen(" HTTP/1.1\r\nHost:");
    requestlength += (opts->vhost) ? strlen(opts->vhost) : strlen(opts->dst);
    if (opts->postdata)
    {
        requestlength += strlen("\r\nContent-Length:");
        requestlength += intlen(strlen(opts->postdata));
    }
    requestlength += strlen("\r\n\r\n");
    return (requestlength);
}

char    *itoa(int value)
{
    char    *ret;
    int     tmp_n;
    size_t  size_ret;
    char    sign;

    sign = (value < 0) ? -1 : 1;
    size_ret = 2 + (value < 0);
    tmp_n = value;
    while ((value = value / 10))
        size_ret++;
    value = tmp_n;
    ret = malloc(size_ret--);
    if (!ret)
        return (NULL);
    ret[size_ret--] = '\0';
    ret[size_ret--] = sign * (value % 10) + '0';
    while ((value = value / 10))
        ret[size_ret--] = sign * (value % 10) + '0';
    if (sign < 0)
        ret[size_ret] = '-';
    return (ret);
}

char    *copyRequest(t_opts *opts, char *tmp)
{
    char    *bufContent;

    strcpy(tmp, opts->method);
    strcat(tmp, " ");
    strcat(tmp, opts->uri);
    strcat(tmp, " HTTP/1.1\r\nHost:");
    (opts->vhost) ? strcat(tmp, opts->vhost) : strcat(tmp, opts->dst);
    if (opts->postdata)
    {
        strcat(tmp, "\r\nContent-Length:");
        bufContent = itoa(strlen(opts->postdata));
        strcat(tmp, bufContent);
        strcat(tmp, "\r\n\r\n");
        strcat(tmp, opts->postdata);
        return (tmp);
    }
    strcat(tmp, "\r\n\r\n");
    return (tmp);
}

char    *createRequest(t_opts *opts)
{
    size_t  requestlength;
    char    *tmp;

    requestlength = lengthRequest(opts);
    tmp = malloc(sizeof(char *) * requestlength + 1);
    memset(tmp, 0, (requestlength + 1));
    if (!tmp)
        return (NULL);
    tmp = copyRequest(opts, tmp);
    return (tmp);
}

int     checkOpts(t_opts *opts)
{
    if (opts->postdata && strcmp(opts->method, "POST"))
    {
        printf(RED "[-] Not use postdata with a %s method\n" RST, opts->method);
        return (0);
    }
    if (!opts->dst)
        return (0);
    initStats(opts->dst);
    if (!opts->method)
        opts->method = "GET";
    if (!opts->uri)
        opts->uri = "/";
    opts->request = NULL;
    opts->request = createRequest(opts);
    return (1);
}
