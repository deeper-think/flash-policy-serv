/* include readline */
#include	"../include/common.h"

ssize_t
readall(int fd, void *vptr, size_t maxlen)
{
	ssize_t	n, rc;
	char	c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) {
		if ( (rc = read(fd, &c, 1)) == 1) {
			*ptr++ = c;
		} else if (rc == 0) {
			if (n == 1)
				return(0);	/* EOF, no data read */
			else
				break;		/* EOF, some data was read */
		} else
			return(-1);	/* error */
	}

	*ptr = 0;
	return(n);
}
/* end readline */

ssize_t
Readall(int fd, void *ptr, size_t maxlen)
{
	ssize_t		n;

	if ( (n = readall(fd, ptr, maxlen)) == -1) {
		printf("readall error\n");
		exit(-1);
	}
	return(n);
}
