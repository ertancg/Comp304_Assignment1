#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
	int fd[2], nbytes;


	if (argc != 2) {
    	printf("Usage: %s <command-to-run>\n", argv[0]);
    	exit(-1);
  	}

  	if(pipe(fd) == -1){
  		printf("Pipe failed.\n");
  	}


	char *command_name = argv[1];

	pid_t child;

	child = fork();

	if(child == 0){
		close(fd[0]);
		struct timeval start;

		gettimeofday(&start, NULL);

		write(fd[1], &start, sizeof(start));
		close(fd[1]);
		
		execlp(command_name, "", NULL);
		
		exit(0);
	}else if(child > 0){
		wait(NULL);
		close(fd[1]);

		struct timeval end, start;
		
		gettimeofday(&end, NULL);

		nbytes = read(fd[0], &start, sizeof(start));
		close(fd[0]);

		
		int second = (end.tv_sec - start.tv_sec);
		float micro_sec = (end.tv_usec - start.tv_usec) / 1e+6;

		printf("Elapsed time: %0.4f ms\n", second + micro_sec);
		
	}else{
		printf("There was a problem when creating child.\n");
	}
	return 0;
}