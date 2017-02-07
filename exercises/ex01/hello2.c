/* Compile, with assembly code: gcc hello2.c -S */
/* Compile with optimization, with assembly code: gcc -O2 hello2.c -S */
/* Run: ./hello */

#include <stdio.h>

/* 1. If you turn on optimization using flag -O2 the assembly language output seems to be shorter. Without optimization there is a 4-byte Spill*/
/* 2. Answer same as question 1 */
/* 3. Answer same as question 1 */
/* Conclusion: I think optimization made a bug, a 4-byte spill, disappear. */  
int main(){
    int x = 5;
    int y = x + 1;
    printf("%d", y);
    return 0;
}