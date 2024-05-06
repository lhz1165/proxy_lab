#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_
#include "csapp.h"
#include "arrayBlockQueue.h"

#define THREAD_LIMIT 10   

void initThreadPool();
void *run(void);
extern blockQueue myqueue;
#endif