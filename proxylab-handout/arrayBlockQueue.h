/* 信号量实现阻塞队列 */
#ifndef _ARRAYBLOCKQUEUE_H_
#define _ARRAYBLOCKQUEUE_H_

#include "csapp.h"
#define SBUFSIZE 4
//阻塞的循环队列
typedef struct {
    
    int connFdArray[SBUFSIZE];
    int n; 
    //头
    int front;
    //尾
    int rear;
    //当前容量    
    sem_t mutex;
    sem_t full;
    sem_t empty;
    int size;


} blockQueue;
//typedef struct arrayBlockQueue blockQueue;
void initConnFdArray(blockQueue* queue,int n);
void offer(blockQueue* queue,int connFd);
int poll(blockQueue* queue);
#endif