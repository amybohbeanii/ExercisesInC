/*******************************************************/
/* Counts cards, modified into 3 methods.	           */
/* Amy Wu, 2017.                                       */
/* Compile: gcc -ansi -Wall -o cards2 cards2.c         */
/* Run: ./cards2 									   */
/* Compile and run: gcc cards2.c -o cards2 && ./cards2 */
/* Compile2: gcc -ansi -pedantic -Wall cards2.c        */
/*******************************************************/

#include <stdio.h>
#include <stdlib.h>

/* Gives the value for a card */
int givesvalue(int val, char card_name[]){
	switch(card_name[0]){
    		case 'K':
    		case 'Q':
    		case 'J':
    			val = 10;
    			break;
    		case 'A':
    			val = 11;
    			break;
    		case 'X':
    			break;
    		default:
    			val = atoi(card_name);
    			if((val<1)||(val>10)){
    				puts("I don't understand that value!");
    				break;
    			}
    }
	return val;
}	

/* Counts the number of cards */
int counter(int count, int val){
	if((val>2)&&(val<7)){
    		count++;
    	}else if(val==10){
    		count--;
    }
    return count;
}

/* Prints the number of cards */
void printstatement(count){
 	printf("Current count: %i\n", count); 
}	

/* Loops to count number of cards */
int main(){
    char card_name[3];
   	int count = 0;
   	int val = 0;
    while(card_name[0]!='x'){
    	puts("Enter the card_name: ");
    	scanf("%2s", card_name);
    	val = givesvalue(val, card_name);
    	count = counter(count, val);
    	printstatement(count);
    }					 
    return 0;
}
