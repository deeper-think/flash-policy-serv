#include "../include/common.h"

int
Socket(int family, int type, int protocol)
{
    int n;

    if ( (n = socket(family, type, protocol)) < 0) {
        printf("socket error\n");
		exit(-1);
	}
    return(n);}

void
Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0) {
		printf("bind error\n");
		exit(-1);
	}
}

void
Listen(int fd, int backlog)
{
	char	*ptr;

	if ( (ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if (listen(fd, backlog) < 0) {
		printf("listen error\n");
		exit(-1);
	}
}

void
Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0) {
		printf("connect failed!!\n");
		exit(-1);
	}
}

int
Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;
again:
    if ( (n = accept(fd, sa, salenptr)) < 0) {
#ifdef  EPROTO
        if (errno == EPROTO || errno == ECONNABORTED)
#else
        if (errno == ECONNABORTED)
#endif
            goto again;
        else {
            printf("accept error\n");
			exit(-1);
		}
    }
    return(n);
}


void
Close(int fd)
{
	if (close(fd) == -1) {
		printf("close error\n");
		exit(-1);
	}
}

pid_t
Fork(void)
{
	pid_t	pid;

	if ( (pid = fork()) == -1) {
		printf("fork error\n");
		exit(-1);
	}
	return(pid);
}

void
Inet_pton(int family, const char *strptr, void *addrptr)
{
	int		n;

	if ( (n = inet_pton(family, strptr, addrptr)) < 0) {
		printf("inet_pton error for %s\n", strptr);	/* errno set */
		exit(-1);
	}
	else if (n == 0) {
		printf("inet_pton error for %s\n", strptr);	/* errno not set */
		exit(-1);
	}

	/* nothing to return */
}

const char *
Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const char	*ptr;

	if (strptr == NULL) {		/* check for old code */
		printf("NULL 3rd argument to inet_ntop\n");
		exit(-1);
	}
	if ( (ptr = inet_ntop(family, addrptr, strptr, len)) == NULL) {
		printf("inet_ntop error\n");		/* sets errno */
		exit(-1);
	}
	return(ptr);
}
