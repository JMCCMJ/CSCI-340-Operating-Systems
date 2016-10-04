// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <stdio.h>	// IO functions
#include <stdlib.h> 	// atof function
#include <math.h>	// math functions
#include "utils.h"	// your own functions

// ----------------------------------------------
// Define constants
#define TOTAL_VECS 10	// constant that defines the total number 
			// of vectors, i.e. magnitude,direction 
			// pairs, in the vectors text file.

// -----------------------------------
// Main function 
// Arguments:	argc = number of arguments suppled by user
//		argv = array of argument values
//
//
int main( int argc, char** argv ) {
	
	// --------------------------------
	// Steps to be performed
	//	1. Define variables (including arrays)
	
	char* fileName;
	v_struct v_struct0, v_struct1, v_struct2, v_struct3, v_struct4, v_struct5, v_struct6, v_struct7, v_struct8, v_struct9;
	v_struct* structArray;
	double num;
	int i;
	
	double temp_theta_deg;
	double temp_theta_rad;
	double temp_r;
	double temp_x;
	double temp_y;
	//structPt = &tempStruct;
	//tempStruct.r = 10.2;
	//tempStruct.theta = 20.2;
	
	structArray = malloc(10*sizeof(v_struct));
	structArray[0] = v_struct0;
	structArray[1] = v_struct1;
	structArray[2] = v_struct2;
	structArray[3] = v_struct3;
	structArray[4] = v_struct4;
	structArray[5] = v_struct5;
	structArray[6] = v_struct6;
	structArray[7] = v_struct7;
	structArray[8] = v_struct8;
	structArray[9] = v_struct9;
	
	//structArray[0] = tempStruct;
	//num = tempStruct.theta;
	//printf("%.2f",structArray[0].r);
	//printf("YES\n");
	//printf("%.2f",tempStruct.r);
	//printf("\n");
	//printf(num);
	//scanf("%lf", &num);
	//printf("%s", structArray[0].r);
	//printf("you missed it \n");
	//printf("%s", tempStruct.theta);
	//printf("end\n");
	//I THINK NUM WONT PRINT RIGHT FOR SEGFAULT ERROR OCCURING
	//printf("%s", num);
	//printf("end\n");
	fileName = malloc(10*sizeof(char));
	//DONT FORGET TO FREE
	
	fileName[0] = 'v';
	fileName[1] = 'e';
	fileName[2] = 'c';
	fileName[3] = 't';
	fileName[4] = 'o';
	fileName[5] = 'r';
	fileName[6] = 's';
	fileName[7] = '.';
	fileName[8] = 't';
	fileName[9] = 'x';
	fileName[10] = 't';
	fileName[11] = '\0';
	
	//read(fileName,tempStruct);
	read(fileName,structArray);
	
	free(fileName);
	
	num = structArray[0].theta;
	//printf("%f", structArray[1].r);
	//	2. Using read() function in utils.h, read vectors defined in text file 
	//		- the location of the text file (i.e. vectors.txt) must be defined in argv[1]
	//  	3. Loop through array of vector structs and print to console:
	//		- vector magnitude (using only 2 decimal places)
	//		- vector direction (in radians using only 2 decimal places)
	//		- vector direction (in degrees using only 2 decimal places)
	//		- Using compute_x() function in utils.h, x component value (using only 2 decimal places)
	//		- Using compute_y() function in utils.h, y component value (using only 2 decimal places)
	//	    in the following format
	//		r = <value>, theta = <value> degrees, <value> radians, x_comp = <value>, y_comp = <value>
	//	    For example:
	//		r = 10.00, theta = 180.00 degrees, theta = 3.14 radians, x_comp = -10.00, y_comp = 0.00 
	//

	printf(" Homework Assignment 1 - Have fun!\n" );
	num = M_PI;
	//printf("%f",num);
	//printf("\n");
	
	
	for( i = 0; i < 10; i = i + 1 ){
		temp_r = structArray[i].r;
		temp_theta_deg = structArray[i].theta;
		temp_theta_rad = (temp_theta_deg * M_PI) / 180;
		temp_x = x_component(structArray[i]);
		temp_y = y_component(structArray[i]);
		
		printf("r = %.2f, theta = %.2f degrees, theta = %.2f radians, x_comp = %.2f, y_comp = %.2f",temp_r,temp_theta_deg,temp_theta_rad,temp_x,temp_y);
		printf("\n");
		
		
		
	}
	
	return 0;

} // end main() function
