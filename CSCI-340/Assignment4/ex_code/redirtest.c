#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc, char** argv ) {

	int child_process_status;

	int outfile;

	pid_t cpid1;

	// code is simulating a ls -lrot > test.txt command

	char* pargs[] = { "ls", "-lrot", NULL };

	outfile = open( "test.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP );

	if ( outfile == -1 ) {

		fprintf(stderr, "failed to open file\n");

	} else if ( cpid1 = fork() == 0 ) {

		dup2( outfile, 1 ); 
		execv("/bin/ls", pargs);

	}

	close( outfile );

	waitpid( cpid1, &child_process_status, 0 );

	if ( cpid1 = fork() == 0 ) {

		execv("/bin/ls", pargs);

	}

	waitpid( cpid1, &child_process_status, 0 );

	return 0;

}