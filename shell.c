#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
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
	while (dup){
		args[i] = strsep(&dup, delim);
		i++;
	}
	args[i] = 0;
	free(dup);
	return args;
}

char* parseCommand(char* input, int pos){
	char** allCmd = (char**)malloc(sizeof(char**) *100);
	char* singleCmd = (char*)malloc(sizeof(char*) * 100);
	allCmd = parseHelper(input, ";");
	int i = 0;
	while(allCmd[i] != NULL){
		singleCmd = allCmd[i];
		if (i == pos) break;
		i++;
	}
	singleCmd = trimCommand(singleCmd);
	return singleCmd;
}

char** chopCommand(char* input){
	char** retCmd = (char**)malloc(sizeof(char**) * 100);
	retCmd = parseHelper(input, " ");
	return retCmd;
}

int tallyCommand(char* input){
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

// string of a single command
int searchIO(char* input){
	if (strchr(input, '<') != NULL)	return 0;
	if (strchr(input, '>') != NULL) return 1;
	return -1;
}

void stdInIO(char* input){
	char* commandStr = (char*)malloc(sizeof(char*) * 100);
	commandStr = strsep(&input, "<"); //separate command and file
	commandStr = trimCommand(commandStr);
	char** commandArr = (char**)malloc(sizeof(char**) * 100);
	commandArr = parseHelper(commandStr, " ");
	input = trimCommand(input); //input = filename

	int fdDupIn = dup(STDIN_FILENO);
	int fdFile = open(input, O_RDONLY, 0644);
	dup2(fdFile, STDIN_FILENO);
	executeCommand(commandArr);
	dup2(fdDupIn, STDIN_FILENO);
	close(fdFile);
}

void stdOutIO(char* input){
	char* commandStr = (char*)malloc(sizeof(char*) * 100);
	commandStr = strsep(&input, ">"); //separate command and file
	commandStr = trimCommand(commandStr);
	char** commandArr = (char**)malloc(sizeof(char**) * 100);
	commandArr = parseHelper(commandStr, " ");
	input = trimCommand(input); //input = filename

	int fdDupOut = dup(STDOUT_FILENO);
	int fdFile = open(input, O_WRONLY|O_CREAT, 0644);
	dup2(fdFile, STDOUT_FILENO);
	executeCommand(commandArr);
	dup2(fdDupOut, STDOUT_FILENO);
	close(fdFile);
}

void executeCommand(char** parameters){
	if (strcmp(parameters[0], "exit") == 0){
		printf("exiting shell...\n");
		exit(0);
	}
	if (strcmp(parameters[0], "cd") == 0){
		if (chdir(parameters[1]) == -1)
			printf("error: %d - %s\n", errno, strerror(errno));
		else {
			printf("changing directory...\n");
			chdir(parameters[1]);
		}
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
  	int cmdTotal = tallyCommand(input);
	int cmdNo = 0;
	char* commandStr = (char*)malloc(sizeof(char*) * 100);
	while (cmdNo < cmdTotal){
		commandStr = parseCommand(input, cmdNo);
		if (searchIO(commandStr) == -1){
			char** commandArr = chopCommand(commandStr);
			executeCommand(commandArr);
		}
		if (searchIO(commandStr) == 0) stdInIO(commandStr);
		if (searchIO(commandStr) == 1) stdOutIO(commandStr);
		cmdNo++;
	}
}

int main(){
	while(1)
  		runProgram();
	return 0;
}