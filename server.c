#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define CLNT_MAX 10

int clnt_socks[CLNT_MAX];
int g_clnt_count = 0;

int main(int argc, char** argv)
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in clnt_addr;
    int clnt_addr_size;

    struct sockaddr_in serv_addr;
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(7989);

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        printf("bind error\n");
    }

    if (listen(serv_sock, 5) == -1) {
        printf("listen error\n");
    }

    char buff[200];
    int recv_len = 0;
    while (1) {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr,
            &clnt_addr_size);
        while (1) {
            //g_clnt_socks[g_clnt_count++]  = clnt_sock;
            recv_len = read(clnt_sock, buff, 200);
            printf("recv : ");
            for (int i = 0; i < recv_len; i++) {
                printf("%02x ", (unsigned char)buff[i]);
            }
            printf("\n");
        }
    }
}
