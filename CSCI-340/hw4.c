/*
----------------------------------------------
These are the only libraries that can be used. Under no circumstances
can additional libraries be included.
----------------------------------------------
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include "shell.h"

/*
-----------------------------------
  Main function 
  Arguments:	argc = number of arguments suppled by user
                argv = array of argument values
-----------------------------------
*/



int main( int argc, char** argv ) {
  command_t cmd;
  char line[MAXSTRLEN];
  char fullpath[MAXSTRLEN];
  int done = FALSE;

  while (!done) {
    printf(">> ");
    fgets(line, MAXSTRLEN, stdin);
    line[my_strlen(line)-1] = '\0'; // get rid of newline
    parse(line, &cmd);

    if (cmd.argc > 0) {   // fix for no command (ie white space) entered
      if (my_strequal(cmd.name, "exit")) {
	done = TRUE;
      }
      else if (is_builtin(&cmd)) {
	do_builtin(&cmd);
      }
      else if (find_fullpath(fullpath, &cmd)) {
	// NOTE: find_fullpath() is called again in execute
	execute(&cmd);
      }
      else {
	printf("invalid command\n");
      }
    }
    
    cleanup(&cmd);
  }
  
  return 0;
} // end main function

