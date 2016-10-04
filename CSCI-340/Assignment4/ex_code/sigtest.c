#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

static void sig_child_handler( int sig );
static void sig_int_handler( int sig );

int main( int argc, char** argv ) {

	pid_t pid;

	char* pargs[] = { "ls", NULL };

	if ( signal( SIGCHLD, sig_child_handler ) == SIG_ERR ) {
		printf("signal for child \n");
		perror("Unable to create new child signal handler!");
		exit(-1);

	}

	if ( signal( SIGINT, sig_int_handler ) == SIG_ERR ) {
		printf("signal for int \n");
		perror("Unable to create new signal handler!");
		exit(-1);

	}

	pid = fork();

	if ( pid == 0 ) {
		printf("pid is 0 \n");
		execv("/bin/ls", pargs);
		perror("Child process terminated in error condition!");
		exit(-1);

	}

	//waitpid( pid, 0, WNOHANG ); This will cause a defunct (or zombie) child process.

	// endless loop that sleeps every second
	while ( 1 ) {
		//sleep(2);
		printf("parent is working ... la la la ...\n");
		//sleep(2);
		sleep(4);

	}

	return 0;

}

static void sig_int_handler( int sig ) {

	printf("In SIGINT handler\n");

	exit( sig );

}

static void sig_child_handler( int sig ) {

	printf("In SIGCHLD handler\n");

	int status;
	int p;

	while ((p=waitpid(-1, &status, WNOHANG)) != -1)
	  {
	    printf("Child Process (%d) has Terminated\n", p);
	  }

	//printf("Child Process (%d) has Terminated\n", waitpid(-1, &status, 0) );

}
