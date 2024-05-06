/* 信号量实现阻塞队列 */
#ifndef _ARRAYBLOCKQUEUE_H_
#define _ARRAYBLOCKQUEUE_H_

#include "csapp.h"

#define CONNFDLIMIT 5

//阻塞的循环队列
struct arrayBlockQueue
{
    sem_t *empty;
    sem_t *full;
    //锁
    sem_t *mutexLock;
    int connFdArray[CONNFDLIMIT];
    //头
    int headIndex;
    //尾
    int tailIndex;
    //当前容量
    int size;

};
typedef struct arrayBlockQueue blockQueue;
void initConnFdArray(blockQueue* queue);
void offer(int connFd,blockQueue* queue);
int poll(blockQueue* queue);
#endif