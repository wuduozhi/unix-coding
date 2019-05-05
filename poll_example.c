#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <poll.h>

#define MAXBUF 256

void child_process(void){
	sleep(2);
	char msg[MAXBUF];
	struct sockaddr_in addr = {};
	int n,sockfd,num = 1;
	srandom(getpid());
	/* Create socket and connect to server */
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	printf("htons : %d\n",htons(2000));

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	printf("child {%d} connected \n", getpid());
  	while(1){
        int sl = (random() % 10 ) +  1;
        num++;
     	sleep(sl);
  		sprintf (msg, "Test message %d from client %d", num, getpid());
  		n = write(sockfd, msg, strlen(msg));	/* Send message */
  	}
}

int main(){
	char buffer[MAXBUF];
	struct pollfd pollfds[5];
	struct sockaddr_in addr;
	struct sockaddr_in client;

	int addrlen,n,i,max=0;
	int sockfd,commfd;

	for(i=0;i<5;i++){
		if(fork() == 0){
			child_process();
			exit(0);
		}
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&addr ,sizeof(addr));
	listen (sockfd, 5); 

	for (i=0;i<5;i++) 
	{
		memset(&client, 0, sizeof (client));
		addrlen = sizeof(client);
		pollfds[i].fd = accept(sockfd,(struct sockaddr*)&client, &addrlen);
		pollfds[i].events = POLLIN;
	}
	sleep(1);
	while(1){
		puts("round again");
		poll(pollfds, 5, 50000);

		for(i=0;i<5;i++) {
			if (pollfds[i].revents & POLLIN){
				pollfds[i].revents = 0;
				memset(buffer,0,MAXBUF);
				read(pollfds[i].fd, buffer, MAXBUF);
				puts(buffer);
			}
		}
	}

	return 0;

}