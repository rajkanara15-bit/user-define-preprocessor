#include <stdio.h>
#include"myheader.h"
#define NUMBER 100
#define VALUE 50
#define MESSAGE "Hello from preprocessor"
#define printf PF

void main()
{
    // This is a single-line comment

    int a = NUMBER;
    int b = VALUE;

    printf(MESSAGE);

    /* This is a
       multiline comment
       that should be removed */

    int sum = a + b;

    printf("Sum is calculated");

    // Another comment

    int x = 10;
    int y = 20;
    int z = x + y;

    printf("End of program");
}