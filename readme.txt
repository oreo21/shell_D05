Reo-lly Amazing-ish Shell
by Reo Kimura

Features:
	Forks and executes commands!
	Parses multiple commands on one line!
	Redirects using >, <!
	Guaranteed to do something!
	But can it summon a good grade?

Attempted:
	The following did not end up working, but have been left
		in the code, commented out.
	Could not get pipes to work
	Tried to implement >>, but it kept overwriting the file
	Looked at replacing ~/ with home directory, got seg faults
	Was unable to have the "puppy" command produce a puppy and
		eject it from the optical drive.

Bugs:
	Putting two ;'s next to each other will break the parser
	Redirecting to a file that does not exist occasionally
		does not work.
	Hair regrowth function may result in a seg fault.
	Occasionally, the unicorn command will fail, opening a
		great chasm in the earth and summoning the demon 
		Beelzebub, who will proceeded to unleash his wrath 
		and begin his reign of terror.
	
Files & Function Headers:

shell.c & shell.h
	Handles everything: parsing, forking, and executing commands

	/*======== char* trimCommand() ==========
	Inputs:  char* input
    Returns: A pointer to an array of chars

	Removes all leading and trailing whitespaces of input, if applicable.
	Gives a blank return statement if the input points to NULL. Otherwise
	returns a pointer to the modified input.
	/*======== char** parseCommand() ==========
	Inputs:  char* input
        	 char* delim 
	Returns: An array of strings where each entry is a token
	separated by delim

	If delim is not provided, bad stuff will happen - delim is a must!
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

