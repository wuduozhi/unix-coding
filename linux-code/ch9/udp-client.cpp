#include <stdio.h>              // 标准输入输出 perror函数
#include <string.h>             // 字符数组相关函数 bzero函数 strcmp
#include <stdlib.h>             // 标准库
#include <sys/types.h>          // 基本系统数据类型
#include <sys/socket.h>         // socket函数 bind函数 地址数据结构
#include <netinet/in.h>         // struct sockaddr_in结构所在头文件
#include <arpa/inet.h>          // ip转换函数 inet_ntoa函数
#include <unistd.h>             // 系统调用接口，close函数
#include <errno.h>              // 通过错误码来回报错误资讯的宏

#define BUFFER_LEN 1024

int main(int argc,char* argv[])
{ 
    int sockfd;  
    struct sockaddr_in serverAddr;
    socklen_t addr_len = sizeof(serverAddr);
    char buffer[BUFFER_LEN];
    int n;

    if (argc != 3)
    {
        fputs("Usage: ./Server serverIP serverPORT\n", stderr);
        exit(1);
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)  
    {
        perror("socket");  
        exit(1);  
    }

    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    if (inet_aton(argv[1], &serverAddr.sin_addr) == 0)
    {
        perror("inet_aton");
        exit(1);
    }

    while(1)  
    {
        memset(buffer, 0, BUFFER_LEN);
        printf("Input your world:>");
        gets(buffer);
        printf("\n");
        n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, addr_len);
        if (n == -1)
        {
            perror("fail to send");
            exit(1);
        }
        else
        {
            if(strcmp(buffer, "exit") == 0)
            {
                break;
            }
            else
            {
                memset(buffer, 0, BUFFER_LEN);
                n = recvfrom(sockfd, buffer, BUFFER_LEN, 0, (struct sockaddr*)&serverAddr, &addr_len);
                if (n == -1)
                {
                    perror("fail to receive");
                    exit(1);
                }
                else
                {
                    buffer[n] = '\0';
                    printf("Received data of my world is: %s\n", buffer);
                }
            }
        }
    }  
    if(close(sockfd) == -1)
    {
        perror("fail to close sockfd");
        exit(1);
    }
    puts("UDP Client is closed!");
    return 0;  
}  

