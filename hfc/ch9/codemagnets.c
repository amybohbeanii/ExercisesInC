/*
*program that writes timestamped text to end of a logfile
* gcc codemagnets.c -o codemagnets && ./codemagnets
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char * now(){
  time_t t;
  time (&t);
  return asctime(localtime (&t));
}

int main(){
  char comment[80];
  char cmd[120];
  fgets(comment,80,stdin); //getting unstructured text from standard input and stores in comment array
  sprintf(cmd,"echo '%s %s' >> reports.log",comment,now()); //prints characters to string. First comment, then timestamp stored in cmd array
  system(cmd); //runs contents of cmd string
  return 0;
}  
  
