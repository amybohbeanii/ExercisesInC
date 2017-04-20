/*test code to try out exec() and error checking
* gcc testexec.c -o testexec && ./testexec
 */

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	/*insert diff candidate code*/

	/*output is: donuts with coffee*/
	char *my_env[] = {"FOOD=coffee", NULL};
	if(execle("./coffee", "./coffee", "donuts", NULL, my_env) == -1){
		fprintf(stderr,"can't create order: %s\n", strerror(errno)); /*this shouldnt execute*/
		return 1;
	}
	return 0;
}
