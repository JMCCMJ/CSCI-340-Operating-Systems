#include <stdio.h>

void makeAllLetterX(char* array)
{
	int iii;
    for (iii = 0; array[iii] != '\0'; ++iii)
    {
        array[iii] = 'X';
    }
}

int main(void)
{
    char string[] = "Hello Wordl!";

    printf("%s\n", string);
    makeAllLetterX(string);
    printf("%s\n", string);

    return 0;
}