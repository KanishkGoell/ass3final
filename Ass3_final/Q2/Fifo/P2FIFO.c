#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/un.h>
#define BUFFER_SIZE 100


int main() {
    int fd1, fd2;

    int ret;
    char buffer[BUFFER_SIZE];
	int maxIdx = 0;
	maxIdx = 0;
	int curIdx = maxIdx;
	while(1) {
		while(curIdx < maxIdx + 5) {
			sleep(2);
			fd1 = open("FIFO", O_RDONLY);
			read(fd1, buffer, sizeof(buffer));
			close(fd1);
			curIdx = buffer[0];
			printf("String sent: ");		
			int i =1;
			while(i<15) {
				printf("%c", buffer[i]);
				i++;
			}
			printf("\n");
			
			sprintf(buffer, "%d", curIdx-1);
			printf("ID sent: %s\n", buffer);	
		}
		
		maxIdx = curIdx;
		fd2 = open("FIFO", O_WRONLY);
		write(fd2, buffer, sizeof(buffer));
		close(fd2);
		if(maxIdx >= 50) exit(EXIT_SUCCESS);
	}
    return 0;
}