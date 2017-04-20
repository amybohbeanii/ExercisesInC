/*test code to try out exec() and error checking
* gcc testexec2.c -o testexec2 && ./testexec2
 */

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	/*insert diff candidate code*/

	/*output shouuld be:
	* Diners: 4
	* Juice: peach and apple */
	char *my_env[] = {"JUICE=peach and apple", NULL};
	if(execle("diner_info", "diner_info", "4", NULL, my_env) == -1){
		fprintf(stderr,"can't get exec to work: %s\n", strerror(errno)); /*this shouldnt execute*/
		return 1;
	}
	return 0;
}
