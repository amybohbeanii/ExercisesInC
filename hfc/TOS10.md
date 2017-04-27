## Quiz 6 notes
1) readings 22-24
2) HFC 11 + 12
3) TOS 10 
4) Rec reading with TOS 10 is LBOS Ch3 and 4

* lecture 24 talks about producer-consumer
* LBOS 4.1 solves problem using semphares
* TOS solves problem POSIX way. Mutex protects access to queue. condition variable singals when queue is non-empty and non-full. real world implementation of synchronization. OO pattern in C

## TOS 10: POSIX condition variables. Producer/Consumer problem

 * Use a condition variable to solve producer-consumer problem
 * in multi-threaded rograms, threads perform diff tasks. Threads communicate with each other using a queue. 
 * Some threads, "producers" put data into queue, other "consumers" take data out. 
 * example is a GUI. one thread might put requests into queue. Bad end thread might take requests out to process them
 * queue implementation is needed for both or more than two threads to access queue at the same time. "thread safe"
 * special case is when queue is empty AND (if size of queue is bounded) when queue is full
 
 * base example
 
 ```
 typedef struct {
  int *array; //contains elements of queue
  int length; 
  int next_in; //index for where next element should be added
  int next_out; //index of next element that should be removed
 } Queue; 
 
 Queue *make_queue(int length){
  Queue *queue = (Queue *) malloc(sizeof(Queue));
  queue->length = length;
  queue->array = (int *) malloc(length * sizeof(int));
  queue->next_in = 0;
  queue->next_out = 0;
  return queue;
}

/*special case if queue is initially empty. No next element to remove, so next_out is invalid
int queue_empty(Queue *queue){
  return(queue->next_in == queue->next_out);
}  

/*increments next_in if queue isnt full*/
int queue_incr(Queue *queue, int i){
  return (i+1)%queue->length;
}

/*special case if queue is full. In queue_incr, at end of array it wraps around to 0 and if we keep adding next_in==next_out 
which means queue is empty. To avoid, this func is necessary*/
int queue_full(Queue *queue){
  return (queue_incr(queue,queue->next_in)==queue->next_out);
}

/*add elements to queue*/
void queue_push(Queue *queue, int item){
  if(queue_full(queue)){
    perror_exit("queue is full");
  }
  queue->array[queue->next_in] = item;
  queue->next_in = queue_incr(queue, queue->next_in); //increases next_in using func
}  

/*removes and returns next element from queue*/
int queue_pop(Queue *queue){
  if(queue_empty(queue)){
    perror_exit("queue is empty");
  }
  int item = queue->array[queue->next_out];
  queue->next_out = queue_incr(queue,queue->next_out);
  return item;
}  
```
 ## producers and consumers / making threads to access the queue
```
void *producer_entry(void *arg){
 int i;
 Shared *shared = (Shared *)arg;
 
 for(i=0;i<QUEUE_LENGTH-1;i++){
  printf("adding item %d\n",i);
  queue_push(shared->queue,i);
 }
 pthread_exit(NULL);
} 

void *consumer_entry(void *arg){
 int i;
 int item;
 Shared *shared = (Shared *)arg;
 
 for(i=0;i<QUEUE_LENGTH-1;i++){
  item = queue_pop(shared->queue);
  printf("consuming item %d\n", item);
 }
 pthread_exit(NULL);
}
```
 ## parent code that starts threads and waits for them
 
```
 int i;
 pthread_t child[NUM_CHILDREN];

 Shared *shared = make_shared();
 
 child[0] = make_thread(producer_entry, shared);
 child[1] = make_thread(consumer_entry, shared);

 for(i=0;i<NUM_CHILDREN;i++){
  join_thread(child[i]);
 }

/*shared structure containing the queue*/
typedef struct{
 Queue *queue;
} Shared; 
 
Shared *make_shared(){
 Shared *shared = check_malloc(sizeof(Shared));
 shared->queue = make_queue(QUEUE_LENGTH);
 return shared;
}
```

## problem is currently access to queue is not thread safe. array, next_in, next_out can have different threads access at the same time, which leaves queue to be in a broken state. For example, if consumer is scheduled first, it finds the queue empty, prints error, exits. Rather we need to have consumer blocked until queue is not empty and producer blocked if queue is full. Two ways to solve 1) mutex 2) condition variables
## queue_mutex.c makes queue thread safe with mutex

```
  typedef struct {
  int *array; //contains elements of queue
  int length; 
  int next_in; //index for where next element should be added
  int next_out; //index of next element that should be removed
  Mutex *mutex; //-- this line is new
 } Queue; 
 
 Queue *make_queue(int length){
  Queue *queue = (Queue *) malloc(sizeof(Queue));
  queue->length = length;
  queue->array = (int *) malloc(length * sizeof(int));
  queue->next_in = 0;
  queue->next_out = 0;
  queue->mutex = make_mutex(); //-- new
  return queue;
}

/*special case if queue is initially empty. No next element to remove, so next_out is invalid
int queue_empty(Queue *queue){
  return(queue->next_in == queue->next_out);
}  

/*increments next_in if queue isnt full*/
int queue_incr(Queue *queue, int i){
  return (i+1)%queue->length;
}

/*special case if queue is full. In queue_incr, at end of array it wraps around to 0 and if we keep adding next_in==next_out 
which means queue is empty. To avoid, this func is necessary*/
int queue_full(Queue *queue){
  return (queue_incr(queue,queue->next_in)==queue->next_out);
}

/*synchronization*/
/*add elements to queue*/
void queue_push(Queue *queue, int item){
  mutex_lock(queue->mutex); //-- new
  if(queue_full(queue)){
    mutex_unlock(queue->mutex); //-- new
    perror_exit("queue is full");
  }
  queue->array[queue->next_in] = item;
  queue->next_in = queue_incr(queue, queue->next_in); //increases next_in using func
  mutex_unlock(queue->mutex); //-- new
}  

/*removes and returns next element from queue*/
int queue_pop(Queue *queue){
  mutex_lock(queue->mutex); //-- new
  if(queue_empty(queue)){
    mutex_unlock(queue->mutex); //-- new
    perror_exit("queue is empty");
  }
  int item = queue->array[queue->next_out];
  queue->next_out = queue_incr(queue,queue->next_out);
  mutex_unlock(queue->mutex); //-- new
  return item;
}  
```
## condition variable = data struc allows threads to block until condition becomes true.
* example is thread_push might want to check if queue is full. If full, block until is not full. "queue not full" is the condition

```
  typedef struct {
  int *array; //contains elements of queue
  int length; 
  int next_in; //index for where next element should be added
  int next_out; //index of next element that should be removed
  Mutex *mutex; 
  Cond *nonempty; //new
  Cond *nonfull; //new
 } Queue; 
 
 Queue *make_queue(int length){
  Queue *queue = (Queue *) malloc(sizeof(Queue));
  queue->length = length;
  queue->array = (int *) malloc(length * sizeof(int));
  queue->next_in = 0;
  queue->next_out = 0;
  queue->mutex = make_mutex(); 
  queue->nonempty = make_cond(); //new
  queue->nonfull = make_cond(); //new
  return queue;
}

/*special case if queue is initially empty. No next element to remove, so next_out is invalid
int queue_empty(Queue *queue){
  return(queue->next_in == queue->next_out);
}  

/*increments next_in if queue isnt full*/
int queue_incr(Queue *queue, int i){
  return (i+1)%queue->length;
}

/*special case if queue is full. In queue_incr, at end of array it wraps around to 0 and if we keep adding next_in==next_out 
which means queue is empty. To avoid, this func is necessary*/
int queue_full(Queue *queue){
  return (queue_incr(queue,queue->next_in)==queue->next_out);
}

/*synchronization*/
/*add elements to queue*/
void queue_push(Queue *queue, int item){
  mutex_lock(queue->mutex); 
  while(queue_full(queue)){
    cond_wait(queue->nonfull,queue,queue->mutex); //new
  }
  queue->array[queue->next_in] = item;
  queue->next_in = queue_incr(queue, queue->next_in); //increases next_in using func
  mutex_unlock(queue->mutex); 
  cond_signal(queue->nonempty); //new
}  

/*if queue is empty, we dont exit. Instead condition variable will block*/
/*removes and returns next element from queue*/
int queue_pop(Queue *queue){
  mutex_lock(queue->mutex); 
  while(queue_empty(queue)){ //new
   cond_wait(queue->nonempty,queue->mutex); //new
  } 
 
  int item = queue->array[queue->next_out];
  queue->next_out = queue_incr(queue,queue->next_out);
  mutex_unlock(queue->mutex); 
  cond_signal(queue->nonfull); //new
  return item;
}  
```
## 10.5 condition variable implementation
condition structure is a wrapper for type called pthread_cond_t, defined in POSIX threads API. Similar to mutex, which is a wrapper for pthread_mutex_t. Both are wrappers defiend in utils.c and utils.h

```
typedef pthread_cond_t Cond;

Cond *make_cond(){
 Cond *cond = check_malloc(sizeof(Cond));
 int n = pthread_cond_init(cond,NULL);
 if(n!=0){
  perror_exit("make_cond failed");
 }
 return cond;
} 

void cond_wait(Cond *cond, Mutex *mutex){
 int n = pthread_cond_wait(cond,mutex);
 if(n!=0){
  perror_exit("cond_wait failed");
 }
}

void cond_signal(Cond *cond){
 int n = pthread_cond_signal(cond);
 if(n!=0){
  perror_exit("cond_signal failed");
 }
}
```
