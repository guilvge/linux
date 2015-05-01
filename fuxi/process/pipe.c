#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <lkj.h>
int flag = 0;
int main(int argc, const char *argv[])
{
	pid_t pid;
	int fd[2];
	pipe(fd);
	char bufw[50];
//	memset(bufw,'\0',50);
	char bufr[50];
	pid = fork();
	if (pid == -1)
	{}
	else if (pid ==0 )
	{
#if 1
		close(fd[0]);
	
		
		
			
			fgets(bufw,20,stdin);
			if (strcmp(bufw,"quit\n") == 0)
				exit(0);
			write(fd[1],bufw,20);
			flag = 1;
		
#endif
	}
	else 
	{
		close(fd[1]);
		
		
			wait(NULL);	
			read(fd[0],bufr,20);
			printf("%s",bufr);
			flag = 0;
		
	}
	return 0;
}
