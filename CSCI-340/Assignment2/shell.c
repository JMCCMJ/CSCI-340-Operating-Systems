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

int strLength(char* string){
	int count = 0;
	while(string[count] != '\0'){
		count++;
	}
	return count;
}

int arrayLength(const char** test){
	int counter = 0;
	int i;
	for(i=0;i<999;i++){
		if(test[i]==NULL){
			break;
		}
		else{
			counter++;
		}
	}
	return counter;
	
}
/*
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
*/
void parse(char* line, command_t* p_cmd){
	
	int argCounter = 0;
	int charCounter = 0;
	int i;
	int actualArgCounter = 0;
	char* temp = malloc(200);
	//char** myStringArray = malloc(200);
	char**argv=malloc(200);
	char* name = malloc(200);
	argv[argCounter]=malloc(200);
	
	//printf("NICE %s ", line);
	//printf("is your text \n");
	for(i = 0;i<200;i++){
		if(line[i]==' '){
			argv[argCounter][charCounter]='\0';
			argCounter++;
			charCounter=0;
			argv[argCounter]=malloc(200);
		}
		else if(line[i]=='\0'){
			argv[argCounter][charCounter]='\0';
			argCounter++;
			argv[argCounter]=NULL;
			break;
		}
		else if(line[i]=='\n'){
			argv[argCounter][charCounter]='\0';
			argCounter++;
			argv[argCounter]=NULL;
			break;
		}
		else if(line[i]!=' '){
			argv[argCounter][charCounter]=line[i];
			charCounter++;
		}
		
	}
	
	p_cmd->argv = argv;
	p_cmd->name = argv[0];
	p_cmd->argc = argCounter-1;
	
	//printf("%s hi \n",argv[0]);
	for(i=0;i<100;i++){
		if (p_cmd->argv[i]==NULL){
			//printf("argv is : %s \n",p_cmd->argv[i]);
			break;
		}
		//printf("argv is : %s \n",p_cmd->argv[i]);
	}
	//printf("the name is: %s \n",p_cmd->name);
	//printf("the count is: %d \n",p_cmd->argc);
	//printf("the argv is: %s \n",p_cmd->argv[1]);
	
	//free(name);
	//free(argv);	
}

int is_builtin(command_t* p_cmd){
	//char name[100] = p_cmd->name;
	//printf("You are in is_builtin\n");
	int i;
	//printf("Name is: %s \n",p_cmd->name);
	for(i=0;i<arrayLength(valid_builtin_commands);i++){
		//printf("The constant is: %s \n",valid_builtin_commands[i]);
		if(strcmp(p_cmd->name,valid_builtin_commands[i])==1){
			return 1;
		}
	}
	
	
	return 0;
	
	
}

int do_builtin(command_t* p_cmd){
	//printf("You are in do_builtin\n");
	int return_val;
	//char *const parmList[]=p_cmd->argv;
	//execv(p_cmd->name,parmList);
	//printf("argv: %s \n",p_cmd->argv);
	//printf("argv1: %s \n",p_cmd->argv[1]);
	return_val = chdir(p_cmd->argv[1]);
	//printf("return_val is: %d \n",return_val);
}






int find_fullpath(char* fullpath, command_t* p_cmd){
	//printf("You are in find_fullpath\n");
	char* path_env_variable;
	char* file_or_dir = malloc(300);
	int i=0;
	int exists = 10;
	struct stat buffer;
	int j;
	int c;
	int d;
	int restartCounter = 0;
	int fullNum;
	fullpath = malloc(300);
	
	
	path_env_variable = getenv("PATH");
	//printf("PATH = %s\n", path_env_variable);
	
	while(path_env_variable[i] != '\0'){
		while(path_env_variable[i]!=':'){
			/*if(file_or_dir[i]=' '){
				i++;
				restartCounter++;
				break;
			}*/
		//printf("%c\n",path_env_variable[i]);
		file_or_dir[restartCounter]=path_env_variable[i];
		
		restartCounter++;
		i++;
		}
		d = restartCounter;
		c=0;
		file_or_dir[d]='/';
		d++;
		for(c=0;c<strLength(p_cmd->name)+1;c++){
			
			file_or_dir[d]=p_cmd->name[c];
			//printf("p_cmd name letter : %c \n",p_cmd->name[c]);
			d++;
		}
		
		
		file_or_dir[d]='\0';
		//printf("FILE IS %s \n",file_or_dir);
		if(strcmp(file_or_dir,"/usr/games")){
			printf("FILE NOT FOUND\n");
			return 0;
		}
		//fullpath=file_or_dir;
		//printf("THIS IS THE FULL PATH: %s \n",fullpath);
		exists = stat(file_or_dir,&buffer);
		
		//printf("Exists returned: %d \n",exists);
		if(exists == 0 && (S_IFDIR & buffer.st_mode)){
			printf("FILE FOUND\n");
			//printf("THIS IS THE FULL PATH: %s \n",fullpath);
			
			//fullpath=file_or_dir;
			for(fullNum=0;file_or_dir[fullNum]!='\0';fullNum++){
				//printf("HI\n");
				fullpath[fullNum]=file_or_dir[fullNum];
			}
			//fullNum++;
			//printf("HI\n");
			fullpath[fullNum]='\0';
			
			return 1;
		}
		else if(exists == 0 && (S_IFREG & buffer.st_mode)){
			printf("FILE FOUND\n");
			for(fullNum=0;file_or_dir[fullNum]!='\0';fullNum++){
				//printf("HI\n");
				fullpath[fullNum]=file_or_dir[fullNum];
			}
			//printf("HI\n");
			//fullNum++;
			fullpath[fullNum]='\0';
			//printf("THIS IS THE FULL PATH: %s \n",fullpath);
			//fullpath=file_or_dir;
			return 1;
		}
		for(j=0;j<300;j++){
			file_or_dir[i]='\0';
		}
		restartCounter=0;
		i++;
		
	}
	printf("NOT FOUND\n");
	//run through and checking each, do not store in char**
}


int execute(command_t* p_cmd){
	//printf("You are in Execute!\n");
	int fnd = 0;
	char* fullpath;
	int buffer;
	
	fnd = find_fullpath(fullpath, p_cmd);
	//printf("We are past fnd!\n");
	//printf("HERE WE GO %s \n",fullpath);
	//printf("fnd is: %d \n",fnd);
	//printf("full path is: %s \n",fullpath);
	if (fnd = 1) {
		if (fork() == 0) {
			//printf("PREPARE TO EXECUTE\n");
			//printf("HERE WE GO %s",fullpath);
			execv(fullpath, p_cmd->argv);
			perror("Execute terminated as parent \n");
			exit(1);
			//printf("EXECUTE IS COMPLETE\n");
		}
		wait(&buffer);
		} else {
				// display to user cmd not found
				printf("Command Not Found!\n");
		}
	
	
}


void cleanup(command_t* p_cmd){
	int i;
	free(p_cmd->name);
	for(i=0;i<200;i++){
		if(p_cmd->argv[i]==NULL){
			break;		
		}
		free(p_cmd->argv[i]);
	}
	
	
}



