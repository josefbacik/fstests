// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2010
 *	by D.Buczek - Max Planck Institute for Molecular Genetics Berlin
 *
 * mmap() a file and writev() back to another file
 *	- kernel bug #22452 testcase
 */

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char *file = argv[1];
	char *new_file = argv[2];
	int fd;
	int fd_new;
	void *base;

	struct iovec iovec[3]=
	{
		{ "aaaaaaaaaa" , 10 },
		{ "bbbbbbbbbb" , 10 },
	 	{ NULL , 10 }
	};

	int i;

	fd=open(file, O_RDONLY);
	if (fd==-1) {perror("open");exit(1);}

	base = mmap(NULL,16384,PROT_READ,MAP_SHARED,fd,0);
	if  (base == MAP_FAILED) { perror("mmap");exit(1); }

	unlink(new_file);

	fd_new=open(new_file,O_RDWR|O_CREAT,0666);
	if (fd_new==-1) {perror("creat");exit(1);}

	iovec[2].iov_base=(char *)base;
	i=writev(fd_new,iovec,sizeof(iovec)/sizeof(*iovec));
	if (i==-1) {perror("writev");exit(1);}

	close(fd_new);
	munmap(base,16384);
	close(fd);

	return 0;
}
