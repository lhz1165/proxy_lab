#include "request.h"

/* You won't lose style points for including this long line in your code */

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
    if (starts_with_http_or_https(uri)){
        return 0;
    }else{
        return 1;
    }
}

int paresHeader(request *myrequest,int fd,rio_t *rp){
        char buf[MAXLINE];
        //Rio_readlineb(rp, buf, MAXLINE);
        //printf("%s", buf);
        int index = 0;

        char * userAgent="User-Agent";
        int userAgenti=0;

        char * connection="Connection";
        char * connectionV="Close\n";
        int connectioni=0;

        char * proxyConnection=" Proxy-Connection";
        char * proxyConnectionV="Close\n";
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
            curRequestHeader->value="User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
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
        index++;
    }
        if (userAgenti==0)
        {
             requestHeader *curRequestHeader =(requestHeader *) Malloc(sizeof(requestHeader));   
           curRequestHeader->name="User-Agent";
            curRequestHeader->value="User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
            myrequest->header[index]= curRequestHeader;
            index++;
        }
        if (connectioni==0)
        {
             requestHeader *curRequestHeader =(requestHeader *) Malloc(sizeof(requestHeader));   
            curRequestHeader->name=connection;
            curRequestHeader->value=connectionV;
            myrequest->header[index]= curRequestHeader;
             index++;
        }

        if (proxyConnectioni==0)
        {   
             requestHeader *curRequestHeader =(requestHeader *) Malloc(sizeof(requestHeader));   
            curRequestHeader->name=proxyConnection;
            curRequestHeader->value=proxyConnectionV;
            myrequest->header[index]= curRequestHeader;
            index++;
        }
        myrequest->headerLen=index;
    return 0;
}


int requestForwarding(request *myrequest,int fd){
    //printf("uri=%s\n",uri);
    char * oldMethod = deep_copy_string(myrequest->line->method);
    char * oldVersion =deep_copy_string(myrequest->line->version);

    char* newUri = (char*)Malloc(strlen(myrequest->line->uri) + 1);
    strcpy(newUri, myrequest->line->uri);
    proxy_request nerequest= parseProxyUrl(newUri);
    Free(newUri);
    char *proxyHost = nerequest.host;
    char *proxyPath = nerequest.path;
    int proxyPort = nerequest.port;

    char proxyPortStr[20]; 
    sprintf(proxyPortStr, "%d", proxyPort);

    printf("proxyHost=%s,proxyPortSt = %s\n",proxyHost,proxyPortStr);
    int clientfd = Open_clientfd(proxyHost, proxyPortStr);
    if (clientfd == -1) return -1;
    printf("proxy open_clientfd  %d\n",clientfd);

    //请求buffer
    char buf[MAXLINE];


    rio_t rio;
    Rio_readinitb(&rio, clientfd);
    //发送请求
    //请求头


    //1.请求行 buffer
    //GET / HTTP/1.1\r\n 
    sprintf(buf, "%s %s %s\r\n", oldMethod, proxyPath, oldVersion);
    //2.请求头 buffer
    
    //strcat()
    for (int i = 0; i < myrequest->headerLen; ++i) {
        char *newHead=(char *)Malloc(sizeof(char));
        sprintf(newHead, "%s: %s\r\n", myrequest->header[i]->name, myrequest->header[i]->value);
        strcat(buf,newHead);
        Free(newHead);
        //Rio_writen(fd, buf, strlen(buf));
    }
    strcat(buf,"\r\n");
    printf("request=>\n %s",buf);
    //发送请求
    Rio_writen(clientfd,buf,strlen(buf));

    Free(oldMethod);
    Free(oldVersion);
    //读响应
    Rio_readlineb(&rio, buf, MAXLINE);

    printf("response=>\n %s",buf);

}

proxy_request parseProxyUrl(char uri[MAXLINE]){
    proxy_request info;
    memset(&info, 0, sizeof(info)); // 初始化结构体

    // 判断 URI 是否以 "https://" 或 "http://" 开头，并计算偏移量
    int offset = strncmp(uri, "https://", strlen("https://")) == 0 ? strlen("https://") : strncmp(uri, "http://", strlen("http://")) == 0 ? strlen("http://") : 0;

    // 解析域名
    const char *host_start = uri + offset;
    const char *path_start = strchr(host_start, '/');
    if (path_start == NULL) {
        // 如果没有路径，则整个剩余部分为域名
        strncpy(info.host, host_start, MAXLINE - 1);
        info.host[MAXLINE - 1] = '\0';
    } else {
        // 如果有路径，则从 URI 中提取出域名和路径
        int host_len = path_start - host_start;
        strncpy(info.host, host_start, host_len);
        info.host[host_len] = '\0';

        // 解析端口
        const char *port_start = strchr(info.host, ':');
        if (port_start != NULL) {
            sscanf(port_start + 1, "%d", &info.port);
            port_start = '\0'; // 将端口号之前的字符截断，得到纯净的域名
        } else {
            info.port = 80; // 默认端口
        }

        // 解析资源路径
        strncpy(info.path, path_start, MAXLINE - 1);
        info.path[MAXLINE - 1] = '\0';
    }
    return info;
}

//以http 和http开头返回1 否则0
int starts_with_http_or_https(const char* str) {
    return strncmp(str, "http://", strlen("http://")) == 0 || strncmp(str, "https://", strlen("https://")) == 0;
}


char* deep_copy_string(char* source) {
    // 获取源字符串的长度
    size_t length = strlen(source);

    // 分配足够的内存来存储新字符串，包括结尾的 NULL 字符
    char* new_string = (char*)malloc(length + 1);
    if (new_string == NULL) {
        // 内存分配失败
        return NULL;
    }

    // 复制源字符串到新分配的内存空间
    strcpy(new_string, source);

    return new_string;
}
