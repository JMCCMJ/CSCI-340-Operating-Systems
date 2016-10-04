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

// --------------------------------------------
// Currently only two builtin commands for this
// assignment exist, however in future, more could 
// be added to the builtin command array.
// --------------------------------------------
const char* valid_builtin_commands[] = {"cd", "exit", NULL};

// --------------------------------------------
// Implementation for each prototype below
// --------------------------------------------
// void parse(char* line, command_t* p_cmd);
// int execute(command_t* p_cmd);
// int find_fullpath(char* fullpath, command_t* p_cmd);
// int is_builtin(command_t* p_cmd);
// int do_builtin(command_t* p_cmd);
// void cleanup(command_t* p_cmd);

void parse(char* line, command_t* p_cmd) {
	int i = 0, j = 0, k = 0, ct = 0;
	int tok_len;
	int stringPos = 0;
	
	while(line[i] != '\0') {
		if(line[i] == ' ') {
			ct++;

			while(line[i] == ' ')
				i++;
		}
		else if(line[i] == '\n')
			line[i] = '\0';
		i++;
	}
	ct++;

	//Odd "odd" error fix
	if(ct % 2 == 0)
		p_cmd->argv = (char **) malloc(sizeof(char *) * ct);
	else
		p_cmd->argv = (char **) malloc(sizeof(char *) * ct + 1);

	//
	for(i = 0; i < ct; i++) {
		tok_len = 0;

		while(line[stringPos] != ' ' && line[stringPos] != '\0') {
			stringPos++;
			tok_len++;
		}

		//Check cmd not null
		if(tok_len > 0) {
			//Malloc space for each argv
			p_cmd->argv[i] = malloc((tok_len + 1) * sizeof(char));
			k = stringPos - tok_len;
			j = 0;
			while(j < tok_len) {
				p_cmd->argv[i][j] = line[k];
				j++;
				k++;
			}
			//Add null terminating character
			p_cmd -> argv[i][j] = '\0';
		}

		stringPos++; //Skip space
	}
	p_cmd->argv[i] = NULL;
	p_cmd->argc = ct;

	//Malloc pace for and get name
	p_cmd->name = (char*) malloc(32);
	for (i = 0; p_cmd->argv[0][i] != '\0'; i++)
		p_cmd->name[i] = p_cmd->argv[0][i];
	p_cmd->name[i] = '\0';
}

int execute(command_t* p_cmd) {
	int fnd;
	char fullpath[256];
	int status;

	fnd = find_fullpath( fullpath, p_cmd );

	if (fnd) {
		if (fork() == 0) {
			printf("%s", fullpath);
			execv( fullpath, p_cmd->argv );
		}
		wait(&status);
	}
	else {
		printf("Command not found.\n");
		return 0;
	}

	return 1;
}

int find_fullpath(char* fullpath, command_t* p_cmd) {
	//Check if cmd is cmd
	char *path = getenv("PATH\0");
	char *testpath = (char *) malloc(sizeof(char) * 32);
	int i = 0;
	int found = 0;
	int j;
	int k;
	struct stat status;
	while (path[i] != '\0' && path[i - 1] != '\0' && !found) {
		for (j = 0; j < 32; j++)
			testpath[j] = '\0';

		int j = 0;

		while(path[i] != ':' && path[i] != '\0') {
			testpath[j] = path[i];
			i++;
			j++;
		}

		testpath[j] = '/';
		k = 0;

		for (j += 1; p_cmd->name[k] != '\0'; j++) {
			testpath[j] = p_cmd->name[k];
			k++;
		}

		found = stat(testpath, &status) + 1;

		if (found && (status.st_mode & S_IFREG)) {
			//File found
			for (j = 0; testpath[j] != '\0'; j++)
				fullpath[j] = testpath[j];

			fullpath[j] = '\0';

			free(testpath);

			return 1;
		}
		i++;
	}

	free(testpath);

	printf("Command not found.\n");

	return 0;
}

int is_builtin(command_t* p_cmd) {
	int i = 0;

	while(valid_builtin_commands[i] != NULL) {
		if(strcmp(p_cmd->name, valid_builtin_commands[i]) == 0)
			return TRUE;
		i++;
	}

	return FALSE;
}

int do_builtin(command_t* p_cmd) {
	if (strcmp(p_cmd->name, "cd") == 0 && chdir(p_cmd->argv[1]) == 0)
		return SUCCESSFUL;
	else if (strcmp(p_cmd->name, "cd") == 0 && chdir(p_cmd->argv[1]) != 0) {
		printf("Directory not found.\n");
		return SUCCESSFUL;
	}
	else
		return ERROR;
}

void cleanup(command_t* p_cmd) {
	int i;
	free(p_cmd->name);

	for (i = 0; i < p_cmd->argc; i++)
		free(p_cmd->argv[i]);

	free(p_cmd->argv);
}
