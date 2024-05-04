/*
 * echo - read and echo text lines until client closes connection
 */
/* $begin echo */
#include "csapp.h"

void echo(int connfd) 
{
    size_t n; 
    char buf[MAXLINE]; 
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    Rio_writen(connfd, "你是不是乖娃儿\n", 22);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { //line:netp:echo:eof
        char ans[MAXLINE]="hellowrold\n";
        printf("server received %d bytes: %s\n", (int)n,buf);
        Rio_writen(connfd, ans, 11);  
    }
}
/* $end echo */

