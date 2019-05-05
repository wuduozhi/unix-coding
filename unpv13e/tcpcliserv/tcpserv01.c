#include "unp.h"
#include <time.h>

int main(int argc,char **argv)
{
	int listenfd,connfd;
	pid_t childpid;
	socklen_t chilen;
	struct sockaddr_in servaddr,cliaddr;

	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));

	Listen(listenfd,LISTENQ);

	for(;;){
		chilen = sizeof(cliaddr);
		connfd = Accept(listenfd,(SA*)&cliaddr,&chilen);
		if((childpid = Fork()) == 0){
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		
		Close(connfd);
	}
}

/*
gcc tcpserv01.c -o tcpserv01 -lunp
*/