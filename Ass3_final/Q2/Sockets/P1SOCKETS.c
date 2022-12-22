#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<time.h>

#define SOCKET_NAME "mySocket.socket"
struct sockaddr_un addr;

void getRandStr(char randstrs[][12]) {        
    srand (time(NULL));    
	char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";    
    int i = 0;
    while(i<=50) {
		int j = 1;
		randstrs[i][0] = i;
		while(j<=12) {
			randstrs[i][j] = alphabet[rand() % 26];
			j++;
		}
		i++;
	}
}
int main(int argc, char* argv[]) {
	
	int ret;
	int data_socket;
	char buffer[10];
	memset(&addr, 0, sizeof(addr));

	data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
	connect(data_socket, (const struct sockaddr *) &addr, sizeof(addr));

	char randStr[50][12] = {{0}};
	getRandStr(randStr);
	int i = 1;
	
	while(i<=50) {
		int j = 0;
		while(j<12) {
			if(j == 0) {
				printf("%d ", i-1);
			}
			else printf("%c", randStr[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}

		int lastIdx = 1;
		for(;;){
			printf("sending Strings Indexed from %d to %d\n", lastIdx-1, lastIdx + 3);
			for(int i = lastIdx; i < lastIdx + 5; i++) {
				write(data_socket, randStr[i], strlen(randStr[i]) + 1);
				
			}
			read(data_socket, buffer, sizeof(buffer));
			

			buffer[sizeof(buffer) - 1] = 0;
			int finalIdx = atoi(buffer);
			
			printf("MAX ID SENT BACK BY SERVER = %d\n\n", finalIdx-1);
			if(finalIdx == 50) {
				printf("Successfully sent all Strings\n");
				write(data_socket, buffer, sizeof(buffer));
				close(data_socket);
				exit(EXIT_SUCCESS);
				break;
			}
			else {
				lastIdx = finalIdx + 1;
			}
		}
}