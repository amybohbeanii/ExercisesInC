/* Example code for Think OS.
Copyright 2014 Allen Downey
License: GNU GPLv3
*/

/* Compile, with assembly code: gcc stack2.c -S */
/* Compile with optimization, with assembly code: gcc -O2 stack2.c -S */
/* Run: ./stack2 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/* 
1. It is intended to print out an array. If it were to work, it is suppose to print out an array of size 5, with each value being the same number as the index.
2. When compiled, there is one warning, stating that the “address of stack memory associated with local variable ‘array’ returned”. This means the pointer will point to something that I don’t want it to point to. I would need to free the allocated space.
3. I get no such file or directory
4. I run into same problem as question3 */

int *foo() {
    int i;
    int array[SIZE];

    //printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
	array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

   // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
	array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
	printf("%d\n", array[i]);
    }

    return 0;
}