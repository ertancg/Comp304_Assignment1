#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define MSG_SIZE 16
#define SLEEP_TIME 4

int main(){
	int pipeA[2], nbytes;
	int pipe_to_parent[2];

	char *car_number = malloc(sizeof(int));
	char read_buffer[MSG_SIZE];

	sprintf(car_number, "%d", 1);

	pid_t pidB, pidC, pidD;

	if(pipe(pipeA) < 0){
		printf("Error when creating the pipeA.\n");
		exit(0);
	}
	if(pipe(pipe_to_parent) < 0){
		printf("Error creating pipe_to_parent.\n");
	}

	pidB = fork();

	if(pidB == 0){
		/* Initializing pipeB here so that Parent B and Child C can share it.*/
		int pipeB[2];

		if(pipe(pipeB) < 0){
			printf("Error when creating pipeB.\n");
		}

		pidC = fork();

		if(pidC == 0){
			/* Initializing pipeC here so that Parent C and Child D can share it.*/
			int pipeC[2];

			if(pipe(pipeC) < 0){
				printf("Error when creating pipeC.\n");
			}

			pidD = fork();

			if(pidD == 0){
				/* Process D Functionality */
				/* Reading from pipeC that Parent C sent.*/
				nbytes = read(pipeC[0], read_buffer, MSG_SIZE);
				close(pipeC[0]);
				sleep(SLEEP_TIME);

				printf("Washing the wheels of car %s.\n", read_buffer);

				/* Writing to Main Parent A from pipe_to_parent.*/
				write(pipe_to_parent[1], read_buffer, MSG_SIZE);
				close(pipe_to_parent[1]);
				
				exit(0);
				
			}else if(pidD > 0){
				/* Process C Functionality*/
				/* Reading from pipeB that Parent B sent.*/
				nbytes = read(pipeB[0], read_buffer, MSG_SIZE);
				close(pipeB[0]);
				sleep(SLEEP_TIME);

				printf("Washing the interior of car %s\n", read_buffer);

				/* Writing to Child D from pipeC and closing the pipe.*/
				write(pipeC[1], read_buffer, MSG_SIZE);
				close(pipeC[1]);

				wait(NULL);
				exit(0);
			}else{
				printf("There was a problem when creating process D.\n");
			}

			
		}else if(pidC > 0){
			/* Process B Functionality */
			/* Reading from the Main Process*/
			nbytes = read(pipeA[0], read_buffer, MSG_SIZE);
			close(pipeA[0]);
			sleep(SLEEP_TIME);

			printf("Washing the windows of car %s.\n", read_buffer);

			/* Writing to Child C from pipeB and closing the pipe.*/
			write(pipeB[1], read_buffer, MSG_SIZE);
			close(pipeB[1]);

			wait(NULL);
			exit(0);
		}else{
			printf("There was a problem when creating process C.\n");
		}

		
	}else if(pidB > 0){
		/* Main process */
		car_number = "1";
		printf("Started washing car %s.\n", car_number);

		/* Writing to Child B with pipeA and closing the pipe.*/
		write(pipeA[1], car_number, MSG_SIZE);
		close(pipeA[1]);

		/* Waiting for Child D to terminate.*/
		wait(NULL);

		/* Reading from Child D from pipe_to_parent and closing the pipe.*/
		nbytes = read(pipe_to_parent[0], read_buffer, MSG_SIZE);
		close(pipe_to_parent[0]);

		printf("Finished washing car %s.\n", read_buffer);
	}else{
		printf("There was a problem when creating process B.\n");
	}

	
	return 0;
}