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
int strcmp(char* a, char* b){
	int i=0;
	int alert=0;
   
    while(a[i]!='\0' && b[i]!='\0'){
         if(a[i]!=b[i]){
             alert=1;
             break;
         }
         i++;
         }

    if (alert==0)
         return 1;
    else
         return 0;
}


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
	command_t p_cmd;
	char* userString = malloc(200);
	int done = 0;
	char fullpath[200];
	printf("\n#");
	while ((strcmp(fgets(userString, 100, stdin),"exit"))!=1) {
		
		//fgets(userString, 100, stdin);
		//done = strcmp(userString,"exit");
		
		
		
		parse(userString, &p_cmd);
		//printf("p_cmd argv before if statement = %s \n",p_cmd->argv);
		if(is_builtin(&p_cmd)==1){
			printf("VALID command\n");
			do_builtin(&p_cmd);
			//printf("p_cmd argv = %s \n",p_cmd->argv);
		}
		else if(find_fullpath(fullpath,&p_cmd)==1){
			execute(&p_cmd);
		}
		else{
			printf("An error occurred.\n");
		}
		
		cleanup(&p_cmd);
	
		printf("\n#");
	}


	printf("CSCI 340 Homework Assignment 2 - Have Fun!\n");

	return 0;

} // end main function
