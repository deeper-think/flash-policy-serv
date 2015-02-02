#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>


#define SERV_PORT 843
#define LISTENQ 1024
#define	MAXLINE	4096

#define CROSSDOMAINFILE "/usr/local/flash-policy-serv/etc/crossdomain.xml"

#define	SA	struct sockaddr


int Accept(int, SA *, socklen_t *);
void Bind(int, const SA *, socklen_t);
void Listen(int fd, int backlog);
int Socket(int family, int type, int protocol);
ssize_t Readline(int fd, void *ptr, size_t maxlen);
void Writen(int fd, void *ptr, size_t nbytes);
ssize_t Readall(int fd, void *ptr, size_t maxlen);

void Lseek(int fd, off_t offset, int fromwhere);

void Connect(int fd, const struct sockaddr *sa, socklen_t salen);

void Inet_pton(int family, const char *strptr, void *addrptr);

const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
