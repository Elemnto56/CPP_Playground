#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string.h>

int main() {
    struct addrinfo hints = {0}, *res;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    char in[512]={}, domain[128]={}, full_uri[523] = "gemini://gemini.circumlunar.space/\r\n";
    // printf("> ");
    // if (!fgets(in, 512, stdin)) return -1;

    // strcat(full_uri, in);
    // for (int i={}; in[i] != '/' && i < strlen(in); i++) domain[i] = in[i];

    getaddrinfo("gemini.circumlunar.space", "1965", &hints, &res);

    int sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(sfd, res->ai_addr, res->ai_addrlen);

    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    SSL* ssl = SSL_new(ctx);

    SSL_set_fd(ssl, sfd);
    SSL_connect(ssl);

    SSL_write(ssl, full_uri, strlen(full_uri));

    char buff[4090]={};
    int n;

    while ((n = SSL_read(ssl, buff, 4096)) > 0){
        fwrite(buff, 1, n, stdout);
    }
    
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sfd);
    freeaddrinfo(res);
}