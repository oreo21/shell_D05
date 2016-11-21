#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
  char input[256];
  printf("What would you like to do? ");
  fgets(input, sizeof(input), stdin);
  input[strlen(input) - 1] = 0;

  char *temp = input;
  char *argv[256];
  int i = 0;
  while (temp){
    argv[i] = strsep(&temp, " ");
    i++;
  }
  argv[i] = 0;

  int f = fork();
  wait(&f);
  execvp(argv[0], argv);
 
  return 0;
}
