#include <stdio.h>
#include <stdlib.h>

// to compile:   gcc -Wall ex2.c -o ex2
// to run:       ./ex2

#define DEBUG 1  // useful for turning on/off debugging (see use below)

// a struct is like a class with only public member variables, and no methods
typedef struct {
  // NOTE:  next two declarations are pointers to characters
  char* first; // we don't call these "member variables", but rather fields
  char* last;
  int age;
  int sex;     // 0 = male, 1 = female
} person_struct;

// forward declare a function (NOTE: definition of function is later)
void printPerson(person_struct* p_person);  

int main(int argc, char** argv)
{
  // all variables should be declared at the beginning of the function

  // declare struct variable: person_struct is data type, person is the variable
  person_struct person;

  // create an array of 10 characters DYNAMICALLY allocated on the heap
  char* first = malloc(10*sizeof(char));

  // example of a static initializer (simpler than assigning each char)
  char last[10] = {'l','e','c','l','e','r','c','\0'};

  // put my first name in the "string" (array of characters) variable, first[]
  first[0] = 'T';
  first[1] = 'o';
  first[2] = 'n';
  first[3] = 'y';
  first[5] = '\0';    // this null character terminates the string

  person.first = first;   // NOTE dot notation to specify fields
  person.last = last;
  person.age = 44;
  person.sex = 0;

  printPerson(&person);

  free(person.first);
    
  return 0;
} // end main function


// definition of function printPerson()
void printPerson(person_struct* p_person)
{
  printf("-----------------------------------------------\n");

  // NOTE use of the "->" notation.  What does this mean?  Why am I not
  //    using the "dot" notation instead?
  printf("first %s, last %s, first initial %c, age %d, ",
	 p_person->first, p_person->last, p_person->first[0], p_person->age);

  if (p_person->sex == 0) {
    printf("male\n");
  }
  else {
    printf("female\n");
  }

  p_person->first[3] = 't';
  p_person->last[3] = 'z';

  printf("first %s, last %s\n", p_person->first, p_person->last);
}
