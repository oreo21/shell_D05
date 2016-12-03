A C Shell, D C Shell
by Reo Kimura

Features:
	Forks and executes commands!
	Eliminates surrounding whitespace!
	Parses multiple commands on one line!
	Redirects using > and < !
	Does Pipe-y stuff using | !
	Guaranteed to do something! Probably!

Attempted:
	The following did not end up working, but have been left
		in the code, commented out.
	N/A

Bugs:
	Putting two ;'s next to each other will break the parser
	'exit' occasionally does not work
	Redirection is limited to one character per command
	Piping is limited to a single character per command
	All items within a single command must be separated by a single space character 
	When entering commands, th up/down buttons register as (funky) characters, don't do anything
		(input history feature not included)
	

Files & Function Headers:

shellUtils.c & shellUtils.h
	Handles everything: parsing, forking, and executing commands + IO cases

	/*======== char* trimCommand() ==========
	Inputs:  char* input
    Returns: A pointer to an array of chars

	Removes all leading and trailing whitespaces of input, if applicable.
	Returns NULL if the input points to NULL. Otherwise
	returns a pointer to the modified input.
	====================*/
	
	/*======== char** parseHelper() ==========
	Inputs:  char* input
        	 char* delim 
	Returns: An array of strings where each entry is a token
	separated by delim

	If delim is not provided, bad stuff will happen - delim is a must!
	Returns NULL if the input points to NULL.
	====================*/

	/*======== char* parseCommand() ==========
	Inputs:  char* input
        	 int pos
	Returns: A trimmed string of pos-th command line argument 

	Pos must be less than the total number of commands inputted.
	Returns NULL if the input points to NULL.
	====================*/

	/*======== char** chopCommand() ==========
	Inputs:  char* input
	Returns: An array of strings where each entry is a token
	separated by delim

	Breaks up a command string it a series of strings for each parameter.
	If delim is not provided, bad stuff will happen - delim is a must!
	Returns NULL if the input points to NULL.
	====================*/

	/*======== int tallyCommand() ==========
	Inputs:  char* input
	Returns: An integer representing the number of command line arguments
	provided

	Separates the initial input string by the ";" delimeter and keeps track of
	how many times this occurs.
	Returns NULL if the input points to NULL.
	====================*/

	/*======== void executeCommand() ==========
	Inputs:  char** parameters 
	Returns: Nothing

	Forks and has the child process execute the command(s) while the parent 
	waits. If the provided command line argument(s) don't work, the child will 
	throw an errno message. Special cases "exit" and "cd" are dealt with separately.
	For each command, checks if an IO character is included; if so, calls upon special
	function to take care of operation
	====================*/

	/*======== void searchIO() ==========
	Inputs:  char* input
	Returns: An integer that indicates what type of IO operation is being requested, if at all (0-2)

	Returns -1 if no IO character is provided.
	Returns NULL if the input points to NULL.
	====================*/

	/*======== void stdInIO() ==========
	Inputs:  char* input
	Returns: Nothing

	Creates duplicate of StdIn file descriptor, allowing inputted commands to read files.
	====================*/

	/*======== void stdOutIO() ==========
	Inputs:  char* input
	Returns: Nothing

	Creates duplicate of StdOut file descriptor, allowing inputted commands to create/write files.
	====================*/

	/*======== void pipeIO() ==========
	Inputs:  char* input
	Returns: Nothing

	Uses duplicates of both StdIn + StdOut file descriptors and forks to simulate piping: transferring the
	output of one command and using it as the input of another.
	====================*/				

	/*======== void runProgram() ==========
	Inputs:  None
	Returns: Nothing

	Combines all the processes involved in running a command. Uses all the functions to carry out 
	basic shell functionality: reading input, parsing and executing commands + IO cases.
	====================*/

shellApp.c

	/*======== int main() ==========
	Inputs:  None
	Returns: A meaningless integer :(

	Runs the shell! Calls upon runProgram within an endless while loop, keeping the shell active 
	until an exit command/signals is used
	====================*/