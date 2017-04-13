/*
Purpose: To use variable number of arguments to make functions like printf stretchier. To also understand variadic function (a function that takes a variable number of parameters)

To Run: gcc price_drinks.c -o price_drinks && ./price_drinks
*/
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <stdarg.h> /*you need for variadic functions*/

enum drink {  MUDSLIDE, FUZZY_NAVEL, MONKEY_GLAND, ZOMBIE };

double price(enum drink d) {  
	switch(d) {  
	case MUDSLIDE:    
		return 6.79;  
	case FUZZY_NAVEL:    
		return 5.31;  
	case MONKEY_GLAND:    
		return 4.82;  
	case ZOMBIE:    
		return 5.89;  
	}  
	return 0; 
}
/*variadic function and macros*/
/*
variable arguments follows args
var_start says where variable arguments start
args contains count of how many variables there are
va_end is a macro
*/
double total(int args, ...) {  
	double total = 0;
  	va_list ap;  /*stores extra arguments*/
	va_start(ap, args);  /*needs to know last fixed argument*/
	int i;  
	for(i = 0; i < args; i++) {    
		/*va arg takes va list and type of next argument*/
		enum drink d = va_arg(ap, enum drink);    
		total = total + price(d);  
	}  
	va_end(ap);
	return total;
}



int main(){  
	printf("Price is %.2f\n", total(2, MONKEY_GLAND, MUDSLIDE));  
	printf("Price is %.2f\n", total(3, MONKEY_GLAND, MUDSLIDE, FUZZY_NAVEL));  
	printf("Price is %.2f\n", total(1, ZOMBIE));  
	return 0; 
}
