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
   

        char * userAgent="User-Agent";
        int userAgenti=0;

        char * connection="Connection";
        char * connectionV="Close\r\n";
        int connectioni=0;

        char * proxyConnection=" Proxy-Connection";
        char * proxyConnectionV="Close\r\n";
        int proxyConnectioni=0;
       

    while(strcmp(buf, "\r\n")) {    
        requestHeader *curRequestHeader =(requestHeader *) Malloc(sizeof(requestHeader));   
        Rio_readlineb(rp, buf, MAXLINE);


        char *colon = strchr(buf, ':');
        if (colon == NULL) {
            break;
        }
       *colon = '\0';
        char *name=(char *)malloc(strlen(buf) + 1);
        strcpy(name, buf);

        curRequestHeader->name=name;

        char *value=(char *)malloc(strlen(colon + 1) + 1);
        strcpy(value, colon + 1);
        //
        if (strcmp(userAgent,name)==0){
            curRequestHeader->value=user_agent_hdr;
            userAgenti=1;
        }else if (strcmp(connection,name)==0){
            curRequestHeader->value=connectionV;
            connectioni=1;
        }else if (strcmp(proxyConnection,name)==0){
            curRequestHeader->value=proxyConnectionV;
            proxyConnectioni=1;
        }else{
            curRequestHeader->value=value;
        }

        myrequest->header[index]= curRequestHeader;
        printf("name: %s, value: %s\n",name,curRequestHeader->value);
        index++;
    }
        if (userAgenti==0)
        {
             requestHeader *curRequestHeader =(requestHeader *) Malloc(sizeof(requestHeader));   
           curRequestHeader->name="User-Agent";
           curRequestHeader->value=user_agent_hdr;
            myrequest->header[index]= curRequestHeader;
            index++;
           printf("name: %s, value: %s\n",curRequestHeader->name,curRequestHeader->value);
        }
        if (connectioni==0)
        {
             requestHeader *curRequestHeader =(requestHeader *) Malloc(sizeof(requestHeader));   
            curRequestHeader->name=connection;
            curRequestHeader->value=connectionV;
            myrequest->header[index]= curRequestHeader;
             index++;
            printf("name: %s, value: %s\n",curRequestHeader->name,curRequestHeader->value);
        }

        if (proxyConnectioni==0)
        {   
             requestHeader *curRequestHeader =(requestHeader *) Malloc(sizeof(requestHeader));   
            curRequestHeader->name=proxyConnection;
            curRequestHeader->value=proxyConnectionV;
            myrequest->header[index]= curRequestHeader;
            index++;
            printf("name: %s, value: %s\n",curRequestHeader->name,curRequestHeader->value);
        }
    return 0;
}