#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <strings.h>

#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 2048


int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	if (argc != 2){
		printf("usage: a.out <IPaddress>\n");
		exit(0);
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("socket error\n");
		exit(0);
	}

	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13);	/* daytime server */
	//if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	//	printf("inet_pton error for %s\n", argv[1]);

	servaddr.sin_addr.s_addr=INADDR_ANY;	
	if (connect(sockfd, ( struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
		printf("connection error\n");

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			printf("fputs error\n");
	}
	if (n < 0)
		printf("read error\n");
	exit(0);
}