#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

char** parseCommand(char* input, char* delim){
	char** args = (char**)malloc(100);
	char* temp = input;
	int i = 0;
	while (temp){
		args[i] = strsep(&temp, delim);
		i++;
	}
	args[i] = 0;
	return args;
}

void executeCommand(char** parameters){
	if (strcmp(parameters[0], "exit") == 0){
		printf("exiting shell...\n");
		exit(0);
	}
	if (strcmp(parameters[0], "cd") == 0){
		printf("changing directory...\n"); //todo: throw message if cd doesn't work
		chdir(parameters[1]);
		return;
	}
	else {
		int myPid = fork();
		if (myPid == -1) { //error
			printf("error: %d - %s\n", errno, strerror(errno));
		}
		if (myPid == 0){ //child process
			execvp(parameters[0], parameters);
			printf("error: %d - %s\n", errno, strerror(errno)); //didn't execute, throw error
		}
		else { //parent process
			wait(&myPid);
		}
	}
}

void runProgram(){
	//read command
	char input[256];
  	printf("What would you like to do? ");
  	fgets(input, sizeof(input), stdin);
  	*(strchr(input, '\n')) = NULL;

  	//parse command
  	char** parameters = (char**)malloc(sizeof(char**) * 100);
  	parameters = parseCommand(input, " ");

	//execute command
  	executeCommand(parameters);
}

int main(){
	while(1){
  		runProgram();
	}
	return 0;
}