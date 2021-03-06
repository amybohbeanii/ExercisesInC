/*
Purpose: To understand array of function pointers

Run: gcc dear_john.c -o dear_john && ./dear_john
*/
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

enum response_type {DUMP, SECOND_CHANCE, MARRIAGE};
typedef struct {
	char *name;
	enum response_type type;
} response;

void dump(response r) {  
	printf("Dear %s,\n", r.name);  
	puts("Unfortunately your last date contacted us to");  		puts("say that they will not be seeing you again"); 
}

void second_chance(response r) {  
	printf("Dear %s,\n", r.name);  
	puts("Good news: your last date has asked us to");  
	puts("arrange another meeting. Please call ASAP."); 
}

void marriage(response r) {  
	printf("Dear %s,\n", r.name);  
	puts("Congratulations! Your last date has contacted");  	puts("us with a proposal of marriage."); 
}

/* Complex syntax for telling compiler exactly what functions will look like that youre storing in array
*/
void(*replies[])(response) = {dump,second_chance,marriage};

int main() {
	response r[] = {
		{"Mike", DUMP}, {"Luis", SECOND_CHANCE}, {"Matt", SECOND_CHANCE}, {"William", MARRIAGE}
	};
	int i;
	for(i=0; i<4; i++){
		//pg 340 HFC, gets ride of long switch statements
		/* 
		switch(r[i].type){
		case DUMP:
			dump(r[i]);
			break;
		case SECOND_CHANCE:
			second_chance(r[i]);
			break;
		default:
			marriage(r[i]);
		}
		*/
		/* first full parenthesis is like a function "dump" or "marriage"
			replies like array of function names
			r[i].type is a value like 0 for DUMP or 2 for MARRIAGE
			r[i] is passing the response data type
		*/
		(replies[r[i].type])(r[i]);
	}
	return 0;
}
