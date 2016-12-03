#ifndef SHELLUTILS_H
#define SHELLUTILS_H

char* trimCommand(char* input);
char** parseHelper(char* input, char* delim);
char* parseCommand(char* input, int pos);
char** chopCommand(char* input);
int tallyCommand(char* input);
void executeCommand(char** parameters);
int searchIO(char* input);
void stdInIO(char* input);
void stdOutIO(char* input);
void pipeIO(char* input);
void runProgram();

#endif 

