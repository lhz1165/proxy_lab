#ifndef _REQUEST_H_
#define _REQUEST_H_
#include "csapp.h"

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";




/**请求行*/
//GET /index.html HTTP/1.1
typedef struct 
{
    char method[MAXLINE];
    char uri[MAXLINE];
    char version[MAXLINE];  
} requestLine;

/**请求头*/
//Host: www.example.com
//User-Agent: User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n
typedef struct 
{
    char *name;
    char *value;
} requestHeader;

typedef struct 
{   
    //请求行
    requestLine* line;
    //请求头
    requestHeader *header[MAXLINE];
    //请求体
    char *requestBody;
}request;


int paresLine(request *myrequest, int fd,rio_t *rio);

int paresHeader(request *myrequest, int fd,rio_t *rio);

#endif