#include <stdio.h>
#include <stdlib.h>

// to compile:   gcc -Wall ex1.c -o ex1
// to run:       ./ex1

#define DEBUG 1   // useful for turning on/off debugging (see use below)

// a struct is like a class with only public member variables, and no methods
typedef struct {
  // NOTE:  next two declarations are pointers to characters
  char* first;  // we don't call these "member variables", but rather fields
  char* last;
  int   age;
  int   sex;    // 0 = male, 1 = female
} person_struct;

int main(int argc, char** argv)
{
  /* all variables should be declared at the beginning of a function
     NOTE:  main() is a function.  NOTE two ways to use comments.
  */

  // declare struct variable: person_struct is data type, person is the variable
  person_struct person;
  
  int i;          // loop control variable
  int* p;         // a variable that "points to" an integer
  int* pp;        // another variable that "points to" an integer
  FILE* fhnd;     // a pointer to a FILE structure (used for file I/O)
  char first[10]; // array of 10 characters STATICALLY allocated (on stack)
  char line[50];  // used for reading in lines of data from a file

  // put my first name in the "string" (array of characters) variable, first[]
  first[0] = 'T';
  first[1] = 'o';
  first[2] = 'n';
  first[3] = 'y';
  first[4] = '\0';  // this null character terminates the string

  // How would we create an array that holds 10 person_struct elements?

  printf("-----------------------------------------------\n");

  // sizeof() function returns the size of the variable
  printf("Number of elements in first = %lu\n", sizeof(first)); 

  for (i = 0; i < sizeof(first); i++)
    printf("first[%d]=%c\n", i, first[i]);

  person.first = first;
  person.last = "leclerc";
  person.age = 44;
  person.sex = 0;

  printf("-----------------------------------------------\n");

  if (person.sex == 0) {
    printf("first %s, last %s, first initial %c, age %d, male\n",
	   person.first, person.last, person.first[0], person.age);
  }
  else {
    printf("first %s, last %s, first initial %c, age %d, female\n",
	   person.first, person.last, person.first[0], person.age);
  }
  
  person.first[3] = 't';

  printf("first %s\n", person.first);

  /*
    Concept of a pointer:

    pointer "points to" (contains the address of) a memory location
    where a value is stored

    you de-reference the pointer by writing, *p.  Doing so allows you
    to manipulate (access, change) the value to which the pointer
    points
  */
  
  printf("-----------------------------------------------\n");

  p = malloc(sizeof(int));

  printf("(p) Memory Location [%p] has value = %d\n", p, *p);

  *p = 42;

  printf("(p) Memory Location [%p] has value = %d\n", p, *p);

  (*p)++;   // NOTE:  why do I use parantheses here?

  printf("(p) Memory Location [%p] has value = %d\n", p, *p);

  pp = p;

  (*pp)++;  // NOTE:  why do I use parantheses here?

  printf("(pp) Memory Location [%p] has value = %d\n", pp, *pp);
  printf("(p) Memory Location [%p] has value = %d\n", p, *p);
    
  // What do you think p++ does (ie.  what's the meaning of p++, p a pointer)?

  // -----------------------------------
  // Open a file and loop through each line
  // -----------------------------------

  printf("-----------------------------------------------\n");

  fhnd = fopen("test.txt", "r");   // open file, test.txt, for reading

  if (fhnd != NULL) {  // check if error occured opening the file

    // read lines from the file until we reach end of file
    while (fgets(line, sizeof(line), fhnd) != NULL) {
      if (DEBUG)
	printf("%s", line);  // if only one statement in body, don't need { }
    }
  }

  fclose(fhnd);   // always remember to close a file you opened

  return 0;

} // end main function
