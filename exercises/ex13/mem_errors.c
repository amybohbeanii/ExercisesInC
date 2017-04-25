/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

Modified by: Jiaxuan (Amy) Wu
Date 4/24/17

Learning Goal: Fix the errors using valgrind

gcc -g -O0 mem_errors.c -o memerrors
valgrind --leak-check=yes ./memerrors
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
void free_anything(int *p) {
    free(p);
}
*/

int read_element(int *array, int index) {
    int x = array[index];
    return x;
}

/*Reorganized main to catch memory errors and leaks*/
int main ()
{
    int never_allocated;
    int *free_twice = malloc (sizeof (int));
    int *use_after_free = malloc (sizeof (int));
    int *never_free = malloc (sizeof (int));
    int array1[100];
    int *array2 = malloc (100 * sizeof (int));

    // valgrind does not bounds-check static arrays
    read_element(array1, 0);
    read_element(array1, 99);

    // but it does bounds-check dynamic arrays
    read_element(array2, 0);
    read_element(array2, 99);
    free(array2);

    // and it catches use after free
    *use_after_free = 17;
    free(use_after_free);

    // never_free is definitely lost
    *never_free = 17;
    free(never_free);
    // the following line would generate a warning
    // free(&never_allocated);

    // but this one doesn't
	// free_anything(&never_allocated);
    
    free(free_twice);
	// free(free_twice);

    return 0;
}
