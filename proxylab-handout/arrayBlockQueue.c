#include "arrayBlockQueue.h"



void initConnFdArray(blockQueue* queue,int n){
    sem_unlink("empty");
    sem_unlink("full");
    sem_unlink("mutexLock");

    // 初始化sem_t指针
    //queue->slots = *(sem_t *)malloc(sizeof(sem_t));
  // queue->items = *(sem_t *)malloc(sizeof(sem_t));
   // queue->mutex = *(sem_t *)malloc(sizeof(sem_t));
    queue->size=0;
    queue->n=n;
    queue->front=0;
    queue->rear=0;

    Sem_init(&queue->mutex, 0, 1); /* Binary semaphore for locking */
    Sem_init(&queue->empty, 0, n); /* Initially, buf has n empty slots */
    Sem_init(&queue->full, 0, 0); /* Initially, buf has zero data items */


    for (int i = 0; i < n; ++i) {
         queue->connFdArray[i] = -1;
    }
}


void offer(blockQueue* queue,int connFd){
    P(&queue->empty);                          /* Wait for available slot */
    P(&queue->mutex);   
    int tailIndex= queue->rear;                /* Lock the buffer */
    queue->connFdArray[tailIndex] = connFd;    
    queue->rear= (tailIndex+1) % (queue->n);   /* Insert the item */
    ++queue->size;
    V(&queue->mutex); /* Unlock the buffer */
    V(&queue->full); /* Announce available item */
}
int poll(blockQueue* queue){
    int item;
    P(&queue->full);                           /* Wait for available item */
    //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);  // 不可取消
    P(&queue->mutex);                           /* Lock the buffer */
    int headIndex =(queue->front);
    item = queue->connFdArray[headIndex]; /* Remove the item */
    headIndex++;
    if (headIndex==queue->n)
    {
        headIndex=0;
    }
    queue->front=headIndex;
    --queue->size;
    V(&queue->mutex); /* Unlock the buffer */
    V(&queue->empty); /* Announce available slot */
    return item;
}

int mygetV(sem_t *empty){
    int value = 0;
    sem_getvalue(empty, &value);
    return value;
}




