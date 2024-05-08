#ifndef _REQUEST_H_
#define _REQUEST_H_
#include "csapp.h"





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
    int headerLen;
}request;

typedef struct {
    char host[MAXLINE];
    char path[MAXLINE];
    int port;
}proxy_request;

int paresLine(request *myrequest, int fd,rio_t *rio);

int paresHeader(request *myrequest, int fd,rio_t *rio);

int requestForwarding(request *myrequest,int fd);

int starts_with_http_or_https(const char* str);

proxy_request parseProxyUrl(char uri[MAXLINE]);

char* deep_copy_string(char* source);
#endif