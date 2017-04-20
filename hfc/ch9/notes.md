
### chapter 9: processes and system calls
### use ps -ef in terminal to see processes (programs running in memory)

* c programs make system calls if they want to talk to the hardware
* system calls: functions that live inside OS's kernel. Application causes an exception (by executing a protected instruction) in order to jump into kernel code. The interrupt handler executes code (in kernel mode) on behalf of process, then jumps back into application code. They are functions that your program uses to talk to the kernel
* printf(), is a system call made to OS to send string of text to screen.

## System()
* C library function system() spawns a child process and uses it to execute a shell command, which spawns a child process to execute the command
* system() is a system call that takes a string parameter and executes as if you had typed it on command line... system("gedit");
* system calls lives in the main OS
* on some OS, code for system call lives inside kernel of OS. On other OS, maybe stored in a dynamic library
* making system call generally does not create a new process. It runs some kernel code on your behalf. Exception to this rule is fork, which does create a process.

## system calls have problems
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


| List functions  | How to Use |
| ------------- | ------------- |
| execl(): a list of arguments  | execl ("/home/flynn/clu", "/home/flynn/clu", "paranoids", "contract", NULL)  |
| execlp(): a list of arguments and search on the path  | execlp ("clu", "clu", "paranoids", "contract", NULL)  |
| execle(): a list of arguments and environment variables  | execle ("/home/flynn/clu", "/home/flynn/clu", "paranoids", "contract", NULL, env_vars)  |

2) array functions
