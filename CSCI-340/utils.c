// -----------------------------------
// CSCI 340 - Operating Systems I 
// Spring 2015 (Tony Leclerc, Brent Munsell)
// utils.c implementation file
// Homework Assignment 1
//
// -----------------------------------

// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <stdio.h>	// IO functions
#include <stdlib.h> 	// atof function
#include <math.h>	// math functions
#include "utils.h"	// your own functions

// Now you put your implementation of the function prototypes here...
#define DEBUG 1
//int read( char* file_name, v_struct* p_vec_array ){
int read( char* file_name, v_struct* p_vec_array ){
    char line[50] = "";
    FILE* my_file;
    char *strCtr;
    char my_char;
    int i;
    int j;
    char front_end = 0;
    int array_counter = 0;
    char temp[50] = "";
    int comma_found = 0;
    double r_num;
    double theta_num;
	//printf("%.2f",p_vec_array[0].r);
	//printf("YES ^^ FROM UTILS.C BOY\n");
    //my_file = fopen("vectors.txt", "r");   // open file, test.txt, for reading
    my_file = fopen(file_name, "r");
    
    //printf("my_file has been read\n");
	
    if (my_file != NULL) {  // check if error occured opening the file
	//printf("YAY not null\n");
    // read lines from the file until we reach end of file
	while (fgets(line, sizeof(line), my_file) != NULL) {
		strCtr = line;
		for( i = 0; i < sizeof(line); i = i + 1 ){
			my_char = strCtr[i];
			
			if(my_char == '\0'){ 
				temp[front_end]=' ';
				theta_num = atof(temp);
				if(theta_num > 360){
					theta_num = theta_num - 360;
				}
				else if(theta_num < -360){
					theta_num = theta_num + 360;
				}

				p_vec_array[array_counter].theta=theta_num;
				for( j = 0; j < i; j = j + 1 ){
					temp[j] = ' ';
				}
				front_end = 0;
				break;
				
			}
			 
			if(my_char == ','){
				comma_found = 1;
				r_num = atof(temp);
				p_vec_array[array_counter].r=r_num;
				r_num=0;
				for( j = 0; j < i; j = j + 1 ){
					temp[j] = ' ';
				}
				front_end = i;
				
					
			}
			temp[i]=line[i];
		}
		array_counter++;
	}
    }
    else{
	
	printf("Oh no didn't read file!\n");
    }
    

    fclose(my_file);   // always remember to close a file you opened
    return array_counter;
	
}

double x_component( v_struct p_vector ){
	double vec_r;
	double vec_theta;
	double conversion;
	double answer;
	
	vec_r = p_vector.r;
	vec_theta = p_vector.theta;
	conversion = (vec_theta * M_PI) / 180;
	answer = vec_r * cos(conversion);
	
	//printf("%f",answer);
	//printf("\n");
	
	return answer;

}

double y_component( v_struct p_vector ){
	double vec_r;
	double vec_theta;
	double conversion;
	double answer;
	
	vec_r = p_vector.r;
	vec_theta = p_vector.theta;
	conversion = (vec_theta * M_PI) / 180;
	answer = vec_r * sin(conversion);
	
	//printf("%f",answer);
	//printf("\n");
	
	
	return answer;
	
}