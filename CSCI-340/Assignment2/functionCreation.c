#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"


int main(int argc, char** argv) {
	char myStr[100] = "Hello Word"; 
	printf("%s",myStr);



}




char** stringSplit(char* string, char splitter){
	char** splitStringsArray;

	int subCharCounter = 0;
	int arrayCounter = 0;
	char tmp[100];
	int i;
	int j;
	
	
	
	for(i=0; i < sizeof(string);i++){
		if(string[i]!=splitter{
			tmp[subCharCounter]=string[i];
			subCharCounter++;
		}
		else if(string[i]==splitter){
			tmp[subCharCounter]='\0'
			splitStringArray[arrayCounter]=tmp;
			arrayCounter++;
			for(j=0;j<sizeof(tmp);j++){
				tmp[j]='\0';
			}
			subCharCounter=0;
		}
		else if(string[i]=='\0'){
			splitStringArray[arrayCounter]=tmp;
		}
		
		
	}
	

}