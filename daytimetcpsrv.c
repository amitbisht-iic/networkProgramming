#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <strings.h>

#include <arpa/inet.h>
#include <unistd.h>

#include <time.h>

#define MAXLINE 2048

int main(int argc, char const *argv[])
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;

	listenfd=socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(13);

	bind(listenfd,(struct sockaddr*) &servaddr,sizeof(servaddr));

	listen(listenfd,5);

	while(1){
		connfd=accept(listenfd,NULL,NULL);
		ticks=time(NULL);
		snprintf(buff,sizeof(buff), "%.24s\r\n",ctime(&ticks));
		write(connfd, buff, strlen(buff));		

		close(connfd);
	}
	close(listenfd);

	return 0;
}