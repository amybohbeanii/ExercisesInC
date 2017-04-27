## HFC11: Sockets and Networking

* C is used to write most low level networking code
* most networked applications need a server and client
* telnet example to talk to server
* data stream socket to talk to network

```
#include <sys/socket.h>

//descriptor for the socket
int listener_d = socket(PF_INET, SOCK_STREAM, 0);
if(listener_d==-1){
  error("cant open socket");
}
```
* server can talk to client program, but it has to BLAB 
1) Bind to a port
  * Computer runs several servers. It might send out web pages, posting emails, running chat server. To prevent diff convos from getting confused, each server uses a diff port (Think of channel on a TV). 
  * To bind, you need socket descriptor and socket name. socket name is struct that means "internet port 30000"
  
```
#include <arpa/inet.h> //for creating internet addresses

/*lines to create name for port 30000*/
struct sockaddr_in name;
name.sin_family = PF_INET;
name.sin_port = (in_port_t)htons(30000);
name.sin_addr.s_addr = htonl(INADDR_ANY);
int c = bind(listener_d,(struct sockaddr *) &name,sizeof(name));
if (c==-1){
  error("cant bind to socket");
}  
```
2) Listen
* how long you want queue to be for clients to access in case server gets popular (Reddit is terrible at this)
``` 
if (listener(listener_d,10)==-1){
  error("can't listen");
}
```
3) Accept a connection
* waits for client, then returns second socket desriptor to hold convo
```
struct sockaddr_storage client_addr;
unsigned int address_size = sizeof(client_addr);
int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
if(connect_d == -1)
  error*"can't open secondary socket")
 ``` 
4) Begin talking

## whole example before pg 477
* remember to reuse socket 479
* other code examples there
## send() to output data on socket/send data to client (HFC pg 472)
## recv() to read data from client (pg 478 for code)

## fork() a process for each client
* when clients connect to server, they have convo on newly created socket. So when client connects, fork() a separate child process to deal with convos
* after forking child, parent can close secondary socket and child can close main listener socker
```
close(connect_d);
close(listener_d);
```
### knock knock joke whole code is 488 and 483


## web client / clients talk whenever
1) connect to remote port
2) begin talking

* create socket for client 493, full solution 497

