#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_
#include "csapp.h"
#include "arrayBlockQueue.h"


#define INIT_THREAD_N 5
 

extern blockQueue myqueue;

typedef struct {
    pthread_t tid;
} ithread;

void init();
void *run(void);

void create_threads(int end);

#endif