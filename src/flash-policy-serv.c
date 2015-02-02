#include "../include/common.h"

#define CROSSDOMFILELEN 20480

char crossdomfile [CROSSDOMFILELEN];
unsigned int crossdomfilelen;

unsigned int load_file(const char fp [], char tostr [], unsigned int len);
void req_proc(int sockfd, int crossdomfd);

int
main(int argc, char **argv)
{
    int listenfd, connfd, crossdomfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in    cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr)); 

    Listen(listenfd, LISTENQ); 

	crossdomfilelen = load_file(CROSSDOMAINFILE , crossdomfile, CROSSDOMFILELEN);

    for ( ; ; ) {
        clilen = sizeof(cliaddr);
        if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
            if (errno == EINTR)  
                continue;        /* back to for() */
            else
                printf("accept error\n");
        }
        /* 创建子进程，处理客户连接 */
        if ( (childpid = Fork()) == 0) {
            Close(listenfd);    
            req_proc(connfd, crossdomfd);  
            exit(0);
        }

        Close(connfd); 
		printf("parent close connfd\n"); 
    }
}


unsigned int load_file(const char filepath[] , char tostr[], unsigned int len) {
	
	int n, cur = 0;
    int crossdomfd;	
	if((crossdomfd = open(filepath, O_RDONLY)) == -1) {
        printf("open file: %s failed!!\n", filepath);
        exit(-1);
    }
	
	for ( ; ; ) {
        if ( (n = Readline(crossdomfd, tostr + cur, len - cur)) == 0)
            break;
		cur = cur + n;
	}
	Close(crossdomfd);
	return cur;
}

void
req_proc(int sockfd, int crossdomfd)
{
    ssize_t        n;
    char        line[MAXLINE];
	char c;
     
    /* 发送响应  */
    Writen(sockfd, crossdomfile, crossdomfilelen);
	//shutdown(sockfd, SHUT_RDWR);
	printf("will colse connfd\n");
	sleep(10);
	close(sockfd);
	printf("children shutdown connfd\n");
}
