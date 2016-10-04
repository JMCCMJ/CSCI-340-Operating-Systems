#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"






char** stringSplit(char* string, char splitter){
	char** splitStringsArray = malloc(120*sizeof(char));
	
	int subCharCounter = 0;
	int arrayCounter = 0;
	char tmp[100];
	int i;
	int j;
	int a;
	
	printf("pointer string is: %s \n",string);
	printf("%c",string[1]);
	printf("\n");
	printf("%d",sizeof(string));
	for(i=0; i < sizeof(tmp);i++){
		printf("WHAT\n");
		printf("The char now is: %c",string[i]);
		printf("\n");
		if(string[i]=='\0'){
			printf("NULL term hit\n");
			char ptr_tmp[100];
						
			for(a=0;a<sizeof(tmp);a++){
				ptr_tmp[a]=tmp[a];
			}
			//ptr_tmp[sizeof(tmp)+1]='\0';
			splitStringsArray[arrayCounter]=ptr_tmp;
			printf("THE POINTER TEMP = %s \n",ptr_tmp);
			printf("DID IT WORK?? : %s \n", splitStringsArray[arrayCounter]);
			//printf("PRE: %s \n",splitStringsArray[arrayCounter-2]);
			arrayCounter++;
			break;
		}
		else if(string[i]!=splitter){
			printf("no splitter hit\n");
			tmp[subCharCounter]=string[i];
			subCharCounter++;
			printf("%s \n",tmp);
			
		}
		else if(string[i]==splitter){
			printf("splitter hit i = : %d \n",i);
			tmp[subCharCounter]='\0';
			
			char ptr_tmp[100];
			for(a=0;a<sizeof(tmp);a++){
				ptr_tmp[a]=tmp[a];
			}
			//ptr_tmp[sizeof(tmp)+1]='\0';
			splitStringsArray[arrayCounter]=ptr_tmp;
			printf("THE POINTER TEMP = %s \n",ptr_tmp);
			printf("DID IT WORK?? : %s \n", splitStringsArray[arrayCounter]);
			printf("WDASD %s",splitStringsArray[arrayCounter]);
			printf("YES\n");
			arrayCounter++;
			printf("ARRAY COUNTER: %d",arrayCounter);
			for(j=0;j<sizeof(tmp);j++){
				tmp[j]='\0';
			}
			subCharCounter=0;
			printf("%s \n",tmp);
			printf("END BOY i = %d size of is : %d\n",i,sizeof(tmp));
			
		}
		
		
		
	}
	printf("PRE EXIT CHAR IS : %c \n",tmp[i]);
	printf("exiting\n");
	printf("%s",splitStringsArray[0]);
	printf("Should have printed splitStringArray[0]\n");
	
	for(i=0;i<sizeof(splitStringsArray);i++){
		printf("arrays part is: %s \n",splitStringsArray[i]);
	}
	
	return splitStringsArray;

}


int main(int argc, char** argv) {
	char myStr[100] = "Hello my world\0"; 
	char * p_myStr=myStr;
	char** subArray;
	int i;
	
	printf("pointer is: %s",p_myStr);
	printf("%s",myStr);
	subArray=stringSplit(p_myStr,' ');
	printf("PRINTING ARRAY \n");
	for(i=0;i<sizeof(subArray);i++){
		printf("%s",subArray[i]);
		
	}

}