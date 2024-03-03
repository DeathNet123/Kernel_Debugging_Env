#define _GNU_SOURCE 

#include <dirent.h>
#include <endian.h>
#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/prctl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/timerfd.h>
#include <x86intrin.h>

#include <linux/capability.h>
#include <linux/futex.h>
#include <linux/io_uring.h>

#define PAGE_SIZE 4096

int main(int argc, char **argv)
{
	int pipe_fd[2];
	char pipe_buffer[PAGE_SIZE] = {0};
	memset(pipe_buffer, 'P', PAGE_SIZE);

	puts("[+] Debug the Pipe Code");
	if(pipe(pipe_fd))
	{
		perror("Pipe: ");
		exit(-1);
	}

	puts("[+] Writing to pipe in order to allocate the page for the pipe_buffer");
	write(pipe_fd[1], pipe_buffer, PAGE_SIZE);

	puts("[+] Reading from pipe in order to release page holds by pipe_buffer");
	read(pipe_fd[1], pipe_buffer, PAGE_SIZE);


	return 0;
}