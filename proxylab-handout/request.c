#include "request.h"




int paresLine(request *myrequest, int fd,rio_t *rio){
    requestLine requestline;

    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    //先读一行 
    //GET /index.html  HTTP/1.1
    if (!Rio_readlineb(rio, buf, MAXLINE)){
        return -1;
    }

    //获取 METHOD URI VERSION
    sscanf(buf, "%s %s %s", method, uri, version);
    
    memcpy(requestline.method, method, strlen(method) + 1);
    memcpy(requestline.uri, uri, strlen(uri) + 1);
    memcpy(requestline.version, version, strlen(version) + 1);
    myrequest->line = &requestline;
    printf("parse request line and header\n%s \n----- \n", buf);

    if (strcasecmp(method, "GET")) {                // line:netp:doit:beginrequesterr
        clienterror(fd, method, "501", "Not Implemented", "proxy does not implement this method");
        return 1;
    }
    return 0;

}


int paresHeader(request *myrequest,int fd,rio_t *rp){

    char buf[MAXLINE];
    //Rio_readlineb(rp, buf, MAXLINE);
    //printf("%s", buf);
    int index = 0;
    char *name;
    char *value;
    requestHeader *curRequestHeader;
    while(strcmp(buf, "\r\n")) {    
        curRequestHeader =(requestHeader *) Malloc(sizeof(requestHeader));   
        Rio_readlineb(rp, buf, MAXLINE);


        char *colon = strchr(buf, ':');
        if (colon == NULL) {
            return 1;
        }
       *colon = '\0';
        name = buf;
        value = colon + 1;
        printf("name: %s, value: %s\n",name,value);
        curRequestHeader->name=name;
        curRequestHeader->value=value;
        myrequest->header[index]= curRequestHeader;
        index++;
    }
    
    
    return 0;

}