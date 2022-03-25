#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	

	pid_t parentID = getpid();
	pid_t pid;
	static int level = 0;

	printf("Main Process ID: %d, level %d\n", parentID, level);
	int count = atoi(argv[argc-1]);

	for(int i = 0; i < count; i++){

		pid = fork();
		
		if(pid == 0){
			level++;
			printf("Process ID: %d, ParentID: %d, level %d\n", getpid(), parentID, level);
			parentID = getpid();
		}else if(pid > 0){

		}
	}
		
	exit(0);
	

	
	return 0;
}