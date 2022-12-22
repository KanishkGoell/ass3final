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

void getRandStr(char randstrs[][15]) {        
    srand (time(NULL));    
	char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";    
    
    for(int i = 0; i <= 50; i++) {
		randstrs[i][0] = i+1;
		for(int j = 1; j <= 15; j++) {
			randstrs[i][j] = alphabet[rand() % 26];
		}
	}
}

int main() {
    int fd1, fd2;
	int mem_rec[2];


    int ret;
    char buffer[BUFFER_SIZE];
    // FIFO file path
    char * myfifo = "FIFO";
	mkfifo(myfifo, 0666);
    // char * myfifo2 = "FIFO2";
    
    char randStr[51][15] = {{0}};

    getRandStr(randStr);
    
	for(int i = 0; i < 50; i++) {
		int count = 0;
		for(int j = 1; j < 15; j++) {
			if(count ==0 ) printf("%d ", i+1);
			count++;
			printf("%c", randStr[i][j]);
		}
		printf("\n");
	}

	printf("\n%s\n", "The above strings are random strings created");
	
    


	int lastIdx = 0;
	while(1) {
		

		printf("sending Strings Indexed from %d to %d\n", lastIdx, lastIdx + 4);
		
		for(int i = lastIdx; i < lastIdx + 5; i++) {
			fd1 = open(myfifo, O_WRONLY);
			write(fd1, randStr[i], sizeof(randStr[i]) + 1);
			sleep(1);	
			close(fd1);
		}
		fd2 = open(myfifo, O_RDONLY);
		read(fd2, buffer, sizeof(buffer));
		close(fd2);

		int finalIdx = atoi(buffer);
 		printf("MAX ID SENT BACK BY SERVER = %s\n\n", buffer);

		lastIdx = finalIdx + 1;
		if(lastIdx >= 50) exit(EXIT_SUCCESS);
	}

    return 0;
}