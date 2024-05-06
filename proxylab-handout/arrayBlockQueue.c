#include "arrayBlockQueue.h"




void initConnFdArray(blockQueue* queue){
    sem_unlink("empty");
    sem_unlink("full");
    sem_unlink("mutexLock");

    // 初始化sem_t指针
    queue->empty = (sem_t *)malloc(sizeof(sem_t));
    queue->full = (sem_t *)malloc(sizeof(sem_t));
    queue->mutexLock = (sem_t *)malloc(sizeof(sem_t));



    sem_init(queue->empty, 0, CONNFDLIMIT);
    sem_init(queue->full, 0, 0);
    sem_init(queue->mutexLock, 0, 1);

    queue->headIndex=0;
    queue->tailIndex=0;
    queue->size=0;
    for (int i = 0; i < CONNFDLIMIT; ++i) {
         queue->connFdArray[i] = -1;
    }
}


void offer(int connFd,blockQueue* queue){
    sem_t *empty = queue->empty;
    sem_t *full = queue->full;
    sem_t *mutexLock = queue->mutexLock;
    int tailIndex = queue->tailIndex;

    P(empty);
    P(mutexLock);
    queue->connFdArray[tailIndex] = connFd;
    queue->tailIndex = (tailIndex+1)%CONNFDLIMIT;
    queue->size=queue->size+1;
    V(mutexLock);
    V(full);
}
int poll(blockQueue* queue){
    sem_t *empty = queue->empty;
    sem_t *full = queue->full;
    sem_t *mutexLock = queue->mutexLock;
    int headIndex = queue->headIndex;

    P(full);
    P(mutexLock);
    int connfd = queue->connFdArray[headIndex];
    headIndex++;
    if (headIndex==CONNFDLIMIT)
    {
        headIndex=0;
    }
    queue->headIndex = headIndex;
    queue->size=queue->size-1;
    V(mutexLock);
    V(empty);
    return connfd;
}

int mygetV(sem_t *empty){
    int value = 0;
    sem_getvalue(empty, &value);
    return value;
}




