// server.c
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#define BUF_SIZE 1024
int main(int argc, char *argv[])
{
    // create socket
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("create socket fail");
    }

    int status;

    // 設定 Server IP & port 資訊
    // for IP
    struct in_addr addr;
    addr.s_addr = inet_addr("0.0.0.0");

    // 拿前面的 in_addr struct 資訊(IP)來設定 struct sockaddr_in
    // struct sockaddr_in 是要丟給 bind() 使用
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr = addr;

    // 拿前面設定的 sockaddr_in 結構(server IP & port) 來 bind server
    status = bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (status == -1)
    {
        perror("bind failed");
    }

    // 設定 listen
    // $ man 2 listen
    //      listen — listen for socket connections and limit the queue of incoming connections
    listen(sock, 5);

    // 宣告 buffer, peer 等變數
    int peer_sock;
    struct sockaddr peer_addr;
    socklen_t addr_len = sizeof(peer_addr);
    char *buffer = (char *)malloc(BUF_SIZE);

    // while loop 重複接收新的 client 連線
    while (1)
    {
        peer_sock = accept(sock, &peer_addr, &addr_len);
        printf("1 client connected...\n");

        // 接收 client 送的一筆資料 & print
        ssize_t recv_size;
        recv_size = recv(peer_sock, buffer, BUF_SIZE, 0);
        printf("recv: %s \n", buffer);

        // close peer_socket
        // 重新一個迴圈等待 sock 接收到新的 client
        close(peer_sock);
        printf("wait ... \n");
    }

    // 釋放 buffer 記憶體 & close socket
    free(buffer);
    close(sock);

    return 0;
}
