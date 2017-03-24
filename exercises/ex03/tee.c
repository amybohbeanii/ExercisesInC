/* 
Author: Amy Wu 
Purpose: Assignment3 Olin College Software Systems course
Functionality: Program is an implementation of tee command
Assumptions: I implemented without any options
	
Answer to question 3: What slowed me down was trying to fully understand what UNIX command tee does.

Answer to question 4: The StackOverflow code looks similar
 
To run: gcc tee.c -o tee && ./tee
*/

#include <stdio.h>
#include <string.h>

/*
Tee implementation of writing to files and standard output
*/
int main(int argc, char *argv[]){
	char string1[4];
	strcpy(string1, "tee");
	
	for(int i=0; i<argc;i++){
		if(strncmp(string1, argv[i], 4)==0){
			fprintf(stdout, argv[i++]);
			FILE *file1 = fopen(argv[i++], "w");
			fclose(file1);	
		}		
	}
	
	return 0;
}
