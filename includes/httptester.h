#ifndef HTTPTESTER_H
# define HTTPTESTER_H

# define RED    "\x1b[31m"
# define GRN    "\x1b[32m"
# define YLW    "\x1b[33m"
# define BLU    "\x1b[34m"
# define MGT    "\x1b[35m"
# define CYA    "\x1b[36m"
# define RST    "\x1b[0m"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <float.h>

// OpenSSL
#include <openssl/ssl.h>
#include <openssl/err.h>

typedef struct  s_stats     t_stats;
typedef struct  options     t_opts;

struct      s_stats
{
    char    host[20];
    double  min;
    double  avg;
    double  max;
    double  trm;
    double  rcv;
};

struct      options
{
    char    *dst;
    char    *uri;
    char    *method;
    char    *vhost;
    char    *postdata;
    char    *request;
    int     count;
    int     port;
    double  interval;
    int     help;
    int     ssl;        // 1 = HTTPS activé (flag -ssl ou port 443)
};

extern t_stats		stats;
double      time_diff(struct timeval x, struct timeval y);
void        statistics(double time);
void        handler(int sig);
size_t      intlen(int value);
char        *createRequest(t_opts *opts);
size_t      request(t_opts *opts);
size_t      request_ssl(t_opts *opts);
void        launch(t_opts *opts);
void        initStats(char *dst);
t_opts      *initOpts();
void        getOpts(int ac, char **av, t_opts **opts);
size_t      lengthRequest(t_opts *opts);
char        *copyRequest(t_opts *opts, char *tmp);
char        *createRequest(t_opts *opts);
int         checkOpts(t_opts *opts);
int         usage();

#endif
