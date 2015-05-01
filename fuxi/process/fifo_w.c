#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc, const char *argv[])
{
	int ret;
	char buf[64];
	int n,fd;
	if((ret =mkfifo("./fifo",0664 | O_CREAT | O_WRONLY | O_EXCL)) == -1)
	{
		if (errno == EEXIST)
		{
			fd= open("./fifo",O_WRONLY);
		}
		else 
		{
			perror("mkfifo");
			exit(-1);
		}
	}
#if 0
	else
	{
		fd=open("./fifo",O_WRONLY);
	}
#endif
 	write(fd,"hello",6);	
	return 0;
}
