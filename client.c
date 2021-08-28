// client.c
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
int main(int argc, char *argv[])
{
    // 建立 socket 
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        printf("create socket failed");

    // 同 server.c 
    // 設定連線的 Server IP & Port
    struct in_addr addr;
    addr.s_addr = inet_addr("127.0.0.1");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr = addr;

    // 連線
    int status;
    socklen_t addr_len = sizeof(server_addr);
    status = connect(sock, (struct sockaddr *)&server_addr, addr_len);
    if (status == -1)
        printf("connected failed \n");
    else
        printf("OK.\n");

    // 連線後送出一筆訊息
    char message[] = "Test for transporting.";
    ssize_t send_len;
    send_len = send(sock, message, sizeof(message), 0);

    // close socket
    close(sock);
}
