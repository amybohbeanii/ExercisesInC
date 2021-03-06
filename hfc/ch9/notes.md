
### chapter 9: processes and system calls
### use ps -ef in terminal to see processes (programs running in memory)

* c programs make system calls if they want to talk to the hardware

## System calls
* system calls lives in the main OS
* system calls: functions that live inside OS's kernel. Application causes an exception (by executing a protected instruction) in order to jump into kernel code. The interrupt handler executes code (in kernel mode) on behalf of process, then jumps back into application code. They are functions that your program uses to talk to the kernel. When you make system call, you are calling coe outside your program
* on some OS, code for system call lives inside kernel of OS. On other OS, maybe stored in a dynamic library
* making system call generally does not create a new process. It runs some kernel code on your behalf. Exception to this rule is fork, which does create a process.
* check for errors.
## examples of system calls
* printf(), is a system call made to OS to send string of text to screen.
* system()
* exec(): replaces the current process
* fork(): duplicates the current process. new process is called child process, original process is parent process. copy will have a different PID than original.
## System()
* C library function system() spawns a child process and uses it to execute a shell command, which spawns a child process to execute the command. However, it gives less control over how program runs.
* system() is a system call that takes a string parameter and executes as if you had typed it on command line... system("gedit");

## system calls (system()) have problems
1) security problems: deletion of files or lanching of viruses. 
2) no apostrophes in codemagnets.c example
3) wrong path variable can cause system() function to call wrong program
4) maybe program we call needs specific set of environment variables set up

## kernels are in charge of three things
1) processes: kernel creates processes, makes sure they get resources needed, and watches when processes get too greedy/crash
2) memory: kernel can increase vm size by loading/unloading sections of memory to disk. kernel rations amount of memory each process can take
3) hardware: kernel uses device drivers to talk to equipment plugged into computer. 

## exec()
* in unistd.h
* replaces current process. You can give it command line arguments and environment variables. When new program starts, it has same PID (process identifier) as old one. Think of a relay race - program hands over its process to a new program.
* benefit: removes ambiguity and tells OS precisely which program to run
* two groups of exec() functions
* if exec() function is successful, it changes process so that it runs new program instead of your program. That means program containing the exec() will stop as soon as it runs exec()

| List functions  | How to Use |
| ------------- | ------------- |
| execl(): a list of arguments  | execl ("/home/flynn/clu", "/home/flynn/clu", "paranoids", "contract", NULL)  |
| execlp(): a list of arguments and search on the path  | execlp ("clu", "clu", "paranoids", "contract", NULL)  |
| execle(): a list of arguments and environment variables  | execle ("/home/flynn/clu", "/home/flynn/clu", "paranoids", "contract", NULL, env_vars)  |

| Array functions  | How to Use |
| ------------- | ------------- |
| execv(): an array or vector of arguments  | execv ("/home/flynn/clu", my_args);  |
| execvp(): array/vector of arguments and search on path | execvp ("clu", my_args);  |
| execve(): array/vector of arguments and environment variables  | execle ("/home/flynn/clu", my_args, env_vars)  |

## getenv() system call
* create a set of environment variables as an array of string pointers 
* char *my_env[] = {"JUICE=peach and apple", NULL}; //each variable in environment is name=value
* execle(diner_info", "diner_info", "4", NULL, my_env);

## fork() + exec()
* trick is to call exec() on child process. This way parent process is able to keep running.
* fork() returns 0 to child process and nonzero value to parent process.
* child process gets exec()
* pid_t pid = fork(); //type for storing process IDs

``` 
/*newshound.c revised to include fork*/
for (i=0;i<times;i++){
  char var[255];
  sprintf(var,"RSS_FEED=%s", feeds[i]);
  char *vars[] = {var, NULL};
  pid_t pid = fork(); //clones process
  if(pid==-1){
    if (pid==-1){ //problem cloning process
      fprintf(stderr, "Can't fork process: %s\n", strerror(errno));
      return 1;
  }
  if(!pid){ //same as pid==0, if fork() or code is running child process
    if(execle("/usr/bin/python","/usr/bin/python", "./rssgossip.py", phrase, NULL, vars) == -1){
      fprintf(stderr, "Can't run script: %s\n", strerror(errno));
      return 1;
     }
  }
```


