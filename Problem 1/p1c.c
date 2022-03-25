#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(){

	pid_t pid;


	pid = fork();


	if(pid == 0){
		printf("Child created with pid %d.\n", getpid());
		exit(0);
	}else if(pid > 0){
		sleep(6);
		wait(NULL);
		printf("Process finished.\n");
	}else{
		printf("Error creating process.\n");
	}





	return 0;
}