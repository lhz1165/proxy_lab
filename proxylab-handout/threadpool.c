#include "threadpool.h"


static ithread  threads[INIT_THREAD_N];
static int nthreads;


blockQueue myqueue;

//初始化线程，并运行
void init(){
    nthreads = INIT_THREAD_N;
    initConnFdArray(&myqueue, SBUFSIZE); 
    
    create_threads(nthreads);

}
void doit(int connFd);

void *run(void)
{
    //Pthread_detach(pthread_self());
    while (1) {
        usleep(1000*330);
        int connfd = poll(&myqueue);
        doit(connfd);
        Close(connfd);
        //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);  // 可以取消
    }
}

void create_threads(int end)
{
    for (int i = 0; i < end; i++) {
        // create thread
        Pthread_create(&(threads[i].tid), NULL, run, NULL);
    }
    
}



