#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "mySocket.socket"
struct sockaddr_un servername;

int main(int argc, char *argv[]) {
	int down_flag = 0;
	int connection_socket;
	int ret;
	int maxIdx = 0;
	int data_socket;
	char buffer[12];
    memset(&servername, 0, sizeof(servername));

	connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);

	servername.sun_family = AF_UNIX;
	strncpy(servername.sun_path, SOCKET_NAME, sizeof(servername.sun_path) - 1);

	bind(connection_socket, (const struct sockaddr *) &servername, sizeof(servername));

	listen(connection_socket, 100);

	while(1) {
		data_socket = accept(connection_socket, NULL, NULL);

		maxIdx = 0;
		int curIdx = maxIdx;
		while(1) {
            // sleep(1);
			read(data_socket, buffer, sizeof(buffer));
			buffer[sizeof(buffer) - 1] = 0;
			curIdx = buffer[0];
			
			printf("STRING SENT BY CLIENT: ");		
			int i = 1;
			while(i<12){
				printf("%c", buffer[i]);
                i++;
			}

			printf("\n");
			sprintf(buffer, "%d", curIdx);
            int n = atoi(buffer);
			printf("ID SENT BY CLIENT = %d\n", n-1);		

			if(curIdx == maxIdx + 5) {
				maxIdx = curIdx;
				write(data_socket, buffer, sizeof(buffer));
			}	

			if(curIdx >= 50) break;
		}
		
		

		close(data_socket);
        printf("SHUTTING SERVER\n");
        close(connection_socket);
        unlink(SOCKET_NAME);
        exit(EXIT_SUCCESS);
        break;

	}

	return 0;
}