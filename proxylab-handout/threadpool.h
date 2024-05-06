#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_
#include "csapp.h"
#include "arrayBlockQueue.h"

#define THREAD_LIMIT 10   

void initThreadPool(blockQueue *myqueue);
void *run(void);

#endif