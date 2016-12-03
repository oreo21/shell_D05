#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

char* trimCommand(char* input){
	if (input == NULL) return;
	char* temp = input;
	while (isspace(*temp)) temp++; //remove leading
	if (*temp == 0) return temp; //only whitespace remaining
	size_t len = strlen(temp);
	while(isspace(*(temp + len - 1))) len--; //remove trailing
	temp[len] = '\0';
	return temp;
}

char** parseHelper(char* input, char* delim){
	char** args = (char**)malloc(sizeof(char**) * 100);
	int i = 0;
	char* dup = strdup(input);
	// printf("helper temp1:%s\n", input);
	while (dup){
		args[i] = strsep(&dup, delim);
		i++;
	}
	args[i] = 0;
	// printf("helper temp2:%s\n", input);
	free(dup);
	return args;
}

char** parseCommand(char* input, int pos){
	char** allCmd = (char**)malloc(sizeof(char**) *100);
	char* singleCmd = (char*)malloc(sizeof(char*) * 100);
	allCmd = parseHelper(input, ";");
	int x = 0;
/*	while(allCmd[x] != NULL){
		printf("allCmd[%d]: %s\n", x, allCmd[x]);
		x++;
	}*/
	int i = 0;
	while(allCmd[i] != NULL){
		singleCmd = allCmd[i];
		if (i == pos){
			// printf("singleCmd @ pos %d:%s\n", i, singleCmd);
			break;
		}
		i++;
	}
	singleCmd = trimCommand(singleCmd);
	// printf("singleCmd trim:%s\n",singleCmd);	
	char** retCmd = (char**)malloc(sizeof(char**) * 100);
	retCmd = parseHelper(singleCmd, " ");
/*	x = 0;
	while(retCmd[x] != NULL){
		printf("retCmd[%d]:%s\n", x, retCmd[x]);
		x++;
	}*/
	return retCmd;
}

int tallyComand(char* input){
	char** args = (char**)malloc(sizeof(char**) * 100);
	int i = 0;
	char* dup = strdup(input);
	while (dup){
		args[i] = strsep(&dup, ";");
		i++;
	}
	args[i] = 0;
	free(dup);
	return i;
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
	char input[100];
  	printf("What would you like to do? ");
  	fgets(input, sizeof(input), stdin);
  	*(strchr(input, '\n')) = NULL;
  	
  	
  	//parse and execute command(s)
  	int cmdTotal = tallyComand(input);
	int cmdNo = 0;
	int arg;
	char** command = (char**)malloc(sizeof(char**) * 100);
	while (cmdNo < cmdTotal){
		command = parseCommand(input, cmdNo);
		executeCommand(command);
		cmdNo++;
	}
}

int main(){
	while(1)
  		runProgram();
	return 0;
}