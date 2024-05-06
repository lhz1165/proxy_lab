// #include <stdio.h>
// #include "arrayBlockQueue.h"

// int main(int argc, char const *argv[])
// {
//     blockQueue  *myqueue = ( blockQueue *)malloc(sizeof(blockQueue));
//     initConnFdArray(myqueue);
//     printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     offer(1,myqueue);
//     printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     offer(2,myqueue);
//      printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     offer(3,myqueue);
//      printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     offer(4,myqueue);
//      printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     offer(5,myqueue);
//     printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     int fd = poll(myqueue);
//     printf("poll fd = %d\n",fd);
//     printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     offer(6,myqueue);
//     printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     int fd2 = poll(myqueue);
//     printf("poll fd = %d\n",fd2);
//      printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     int fd3 = poll(myqueue);
//     printf("poll fd = %d\n",fd3);
//      printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     int fd4 = poll(myqueue);
//     printf("poll fd = %d\n",fd4);
//      printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     int fd5 = poll(myqueue);
//     printf("poll fd = %d\n",fd5);
//      printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);
//     int fd6 = poll(myqueue);
//     printf("poll fd = %d\n",fd6);
//     printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);

//     int fd7 = poll(myqueue);
//     printf("poll fd = %d\n",fd7);
//     printf("queue head = %d,tail = %d\n",myqueue->headIndex,myqueue->tailIndex);

//     return 0;
// }
