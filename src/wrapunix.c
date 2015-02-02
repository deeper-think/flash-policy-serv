#include "../include/common.h"

void
Lseek(int fd, off_t offset, int fromwhere)
{

    if ( (lseek(fd, offset, fromwhere)) == -1) {	
        printf("lseek failed!!\n");
		exit -1;
	}
}

