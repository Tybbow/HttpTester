#include "../includes/httptester.h"

static size_t   parse_status_code_ssl(char *server_reply)
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

size_t  request_ssl(t_opts *opts)
{
    int                 s;
    struct sockaddr_in  server;
    SSL_CTX             *ctx;
    SSL                 *ssl;
    char                server_reply[512];
    ssize_t             bytes_received;
    size_t              code;

    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx)
    {
        fprintf(stderr, RED "[-] " RST "Failed to create SSL context\n");
        return (0);
    }

    SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        SSL_CTX_free(ctx);
        return (0);
    }

    server.sin_addr.s_addr = inet_addr(opts->dst);
    server.sin_family = AF_INET;
    server.sin_port = htons(opts->port);

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        close(s);
        SSL_CTX_free(ctx);
        return (0);
    }


    ssl = SSL_new(ctx);
    if (!ssl)
    {
        close(s);
        SSL_CTX_free(ctx);
        return (0);
    }
    SSL_set_fd(ssl, s);

    if (opts->vhost)
        SSL_set_tlsext_host_name(ssl, opts->vhost);
    else
        SSL_set_tlsext_host_name(ssl, opts->dst);

    if (SSL_connect(ssl) <= 0)
    {
        fprintf(stderr, RED "[-] " RST "SSL handshake failed\n");
        SSL_free(ssl);
        close(s);
        SSL_CTX_free(ctx);
        return (0);
    }

    SSL_write(ssl, opts->request, strlen(opts->request));

    memset(server_reply, 0, sizeof(server_reply));
    bytes_received = SSL_read(ssl, server_reply, sizeof(server_reply) - 1);

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(s);
    SSL_CTX_free(ctx);

    if (bytes_received <= 0)
        return (0);

    code = parse_status_code_ssl(server_reply);
    return (code);
}
