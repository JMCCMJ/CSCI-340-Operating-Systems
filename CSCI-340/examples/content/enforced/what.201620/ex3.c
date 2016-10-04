#include <stdio.h>
#include <stdlib.h>

// to compile:   gcc -Wall ex3.c -o ex3
// to run:       ./ex3

#define DEBUG 1

// a struct is like a class with only public member variables, and no methods
typedef struct {
  // NOTE:  next two declarations are pointers to characters
  char* first; // we don't call these "member variables", but rather fields
  char* last;
  int age;
  int sex;     // 0 = male, 1 = female
} person_struct;

// forward declare two functions (NOTE: definition of functions is later)
void initialize(person_struct* person_array, int length);
void printPerson(person_struct* person);

int main(int argc, char** argv)
{
  // all variables should be declared at the beginning of the function    
  int length;
  int i;

  // declare an array of person_struct elements
  person_struct person_array[10]; 

  length = sizeof(person_array)/sizeof(person_struct);

  printf("%d\n", length);

  initialize(person_array, length);

  for (i = 0; i < length; i++) {
    printPerson(&person_array[i]);
  }
  
  return 0;
} // end main function


void initialize(person_struct* person_array, int length)
{
  int i;

  for (i = 0; i < length; i++) {
    person_array[i].first=0;
    person_array[i].last=0;
    person_array[i].age=0;
    person_array[i].sex=0;
  }
}

void printPerson(person_struct* person)
{
  printf("-----------------------------------------------\n");
    
  printf("first %s, last %s, age %d, ",
	 person->first, person->last, person->age);
  
  if (person->sex == 0) {
    printf("male\n");
  }
  else {
    printf("female\n");
  }
}
