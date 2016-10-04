// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

// -----------------------------------
// Main function 
// Arguments:	argc = number of arguments suppled by user
//				argv = array of argument values
//
//
int main(int argc, char** argv) {

	// ----------------------------------
	// Pseudocode
	// ----------------------------------
	// while (!done)
	//		print the prompt (i.e. >, #, or $ ... your choice)
	//		read command line
	//		parse the command line
        //      if (parsed command is "exit")
        //      	done = true
	//  	else if (is _builtin(...))
	//			do_builtin(...)
	//		else if (find_fullpath(...))
	//  		execute(...)
	//		else
	//			error()
	// 		cleanup(...)
	//
	char line[128];
	char fullpath[256];
	command_t cmd;
	int done = 0;

	while(!done) {
		printf("~$ ");
		fgets(line, 128, stdin);
		if(line[0] != '\n') {
			parse(line, &cmd);
			if(strcmp(cmd.name, "exit") == 0)
				done = 1;
			else if(is_builtin(&cmd))
				do_builtin(&cmd);
			else if(find_fullpath(fullpath, &cmd))
				execute(&cmd);
			//else
				//printf("Error.\n");
			cleanup(&cmd);
		}
	}

	//printf("CSCI 340 Homework Assignment 2 - Have Fun!\n");

	return 0;

} // end main function
