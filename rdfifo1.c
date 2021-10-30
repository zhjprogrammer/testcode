/*
 * rdfifo.c - Create a FIFO and read from it
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include<pthread.h>
#include<sys/wait.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
typedef struct Refrence
{
		int x;
		int y;
}Codinate;
int main(void)
{
    int fd;	/* Descriptor for FIFO */
    int len; /* Bytes read from FIFO */
    char buf[PIPE_BUF];
    pid_t pid = fork();
    mode_t mode = 0666;//mode bit
    if ((mkfifo("fifo1", mode)) < 0) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
     }

        /* Open the FIFO read-only */
     if ((fd = open("fifo1", O_RDONLY)) < 0) {//O_RDONLYÖ»¶Á
            perror("open");
            exit(EXIT_FAILURE);
     }
        /* Read and display the FIFO's output until EOF */
	if (pid > 0)
      {
        while ((len = read(fd, buf, PIPE_BUF - 1)) > 0)
            printf("rdfifo read: %s", buf);
         }
    else if(pid == 0)
    {
        execlp("qvfb","qvfb","-width","800","-height","600","-depth","16",NULL);
    }

    close(fd);

    exit(EXIT_SUCCESS);
}

