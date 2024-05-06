#include "threadpool.h"
void doit(int connFd);


static int nthreads;

static pthread_t  threadIds[THREAD_LIMIT];
blockQueue myqueue;

//初始化线程，并运行
void initThreadPool(){
    nthreads = THREAD_LIMIT;
    initConnFdArray(&myqueue); 
    for (int i = 0; i < nthreads; i++) {
        // create thread
        Pthread_create(&(threadIds[i]), NULL, run, NULL);
    }

}

//线程的run方法
void *run(void)
{
    Pthread_detach(pthread_self());
    //不断从阻塞队列中获取任务
    while (1) {
        //取出一个fd
        usleep(1000*330);
        int connfd = poll(&myqueue);

        //执行操作
        doit(connfd);

        //关闭
        Close(connfd);
    }
}
/**
 lab的核心方法
*/
