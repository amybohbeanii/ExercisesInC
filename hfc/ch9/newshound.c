/*gcc newshound.c -o newshound
* ./newshound 'Snooki'
*/
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>


int main (int argc, char *argv[]){
	char *feeds[] = {"http://www.cnn.com/rss/celebs.xml", "http://www.rollingstone.com/rock.xml","http://eonline.com/gossip.xml"};
	int times = 3;
	char *phrase = argv[1];
	int i;
	/*the loop only runs once. Once execle() is called, the whole program quits*/
	/*if you want to start another process and keep origin process running, use fork()*/
	for(i=0;i<times;i++){
		char var[255];
		sprintf(var,"RSS_FEED=%s", feeds[i]);
		char *vars[] = {var, NULL};
		if(execle("/usr/bin/python","/usr/bin/python","./rssgossip.py", phrase, NULL, vars) == -1){
			fprintf(stderr, "Can't run script: %s\n", strerror(errno));
			return 1;
		}
	}	
	return 0;
}
