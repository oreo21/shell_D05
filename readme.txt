Reo-lly Amazing-ish Shell
by Reo Kimura

Features:
	Forks and executes commands!
	Parses multiple commands on one line!
	Redirects using >, <!
	Guaranteed to do something!

Attempted:
	The following did not end up working, but have been left
		in the code, commented out.
	Could not get pipes to work

Bugs:
	Putting two ;'s next to each other will break the parser
	Redirecting to a file that does not exist occasionally
		does not work.

	
Files & Function Headers:

shell.c & shell.h
	Handles everything: parsing, forking, and executing commands

	/*======== char* trimCommand() ==========
	Inputs:  char* input
    Returns: A pointer to an array of chars

	Removes all leading and trailing whitespaces of input, if applicable.
	Gives a blank return statement if the input points to NULL. Otherwise
	returns a pointer to the modified input.
	
	/*======== char** parseHelper() ==========
	Inputs:  char* input
        	 char* delim 
	Returns: An array of strings where each entry is a token
	separated by delim

	If delim is not provided, bad stuff will happen - delim is a must!
	====================*/

	/*======== char** parseCommand() ==========
	Inputs:  char* input
        	 int pos
	Returns: An array of strings where each entry is a token
	separated by delim

	First separates input by ";" delimeter, then separates pos-th command
	by " " delimeter and returns that array of strings

	If delim is not provided, bad stuff will happen - delim is a must!
	====================*/

	/*======== int tallyCommand() ==========
	Inputs:  char* input
	Returns: An integer representing the number of command line arguments
	provided

	Separates the initial input string by the ";" delimeter and keeps track of
	how many times this occurs
	====================*/

	/*======== void executeCommand() ==========
	Inputs:  char** parameters 
	Returns: Nothing

	Forks and has the child process execute the command(s) while the parent 
	waits. If the provided command line argument(s) don't work, the child will 
	throw an errno message. Special cases "exit" and "cd" are dealt with separately.
	====================*/

	/*======== void runProgram() ==========
	Inputs:  None
	Returns: Nothing

	Combines all the processes involved in running a command. Reads the input, then
	uses the parseCommand() and executeCommand() functions to parse and execute the
	command(s).
	====================*/

