#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>


struct command
{
	char *command_name;
	char *arg;
};

int main(int argc, char *argv[]){
	
	pid_t process;
	struct command *given_command = malloc(sizeof(struct command));
	given_command->command_name = argv[1];
	if(argc > 2){
		given_command->arg = argv[2];
	}else{
		given_command->arg = NULL;
	}
	
	process = fork();

	if(process == 0){
		if(given_command->arg != NULL){
			execlp(given_command->command_name, given_command->arg, NULL);
		}else{
			execlp(given_command->command_name, "", NULL);
		}
		exit(0);
	}else if(process > 0){
		wait(NULL);
		printf("Child finished executing %s\n", given_command->command_name);
	}else{
		printf("Error creating the process.\n");
	}

	return 0;
}

