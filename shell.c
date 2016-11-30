#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


char* readCommand(){
	char input[256];
	fgets(input, sizeof(input), stdin);
	*(strchr(input, "\n")) == NULL;
	char* ret = (char*)malloc(sizeof(input));
	ret = input;
	return ret;
}

char** parseCommand(char* input, char* delim){
	char** args = (char**)malloc(1000);
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
		printf("changing directory...\n");
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
			printf("error: %d - %s\n", errno, strerror(errno)); //error, didn't exevp
		}
		else { //parent process
			wait(&myPid);
		}
	}
}

int main(){
	while(1){
    	char input[256];
  		printf("What would you like to do? ");
  		fgets(input, sizeof(input), stdin);
  		//input[strlen(input) - 1] = 0;
  		*(strchr(input, '\n')) = NULL;
  		char** argv = (char**)malloc(sizeof(parseCommand(input, " ")));
  		argv = parseCommand(input, " ");
  		/* int s = 0;
		for (; args[s] != NULL; s++)
			printf("\targs[%d]: %s\n", s, args[s]); */
	    executeCommand(argv);
	    free(argv);
	}
	return 0;
}