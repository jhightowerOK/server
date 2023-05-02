#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFERSIZE 1024
#define MAX 5

int main(){
	char buffer[BUFFERSIZE];
	int sockfd;

	//********* Client Address ******
	struct sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);

	//********* Server Address ******
	struct sockaddr_in server_addr;
	int server_addr_len = sizeof(server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);   //** hton -> Little Endian(Intel) to Big Endian(Internet)
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//** Create a Socket
	sockfd=socket(AF_INET, SOCK_STREAM, 0);

	//** Bind the Socket to the Server Address
	bind(sockfd, (struct sockaddr *) &server_addr, server_addr_len);

	//** Listen for Connections
	printf("Listening on Port %d\n",PORT);
	listen(sockfd,MAX);

	while(1){
		//** Accept Connection
		int conn = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_len);

		int bytesread = read(conn, buffer, BUFFERSIZE);
		int byteswrite = write(conn, buffer, bytesread);
		close(conn);
	}



	return 0;
}
