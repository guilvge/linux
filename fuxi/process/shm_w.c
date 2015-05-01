#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <signal.h>
#if 0
typedef struct shm_data
{
	pid_t pid;
	char buf[100];
}shm_t;
#endif
void fun(int signo)
{
	
}
int main(int argc, const char *argv[])
{
	int key = ftok(".",'a');
	int shmid;
	 char   *p;
	pid_t pid;
	signal(SIGUSR1,fun);
	signal(SIGUSR2,fun);
	if((shmid = shmget(key,100,IPC_CREAT | IPC_EXCL | 0664)) == -1)
	{
		if(errno == EEXIST)
		{
			shmid = shmget(key,100,0664);
			p = shmat(shmid,NULL,0);

			pid = *(pid_t *)p;
			*(pid_t *)p = getpid();
			kill(pid,SIGUSR1);


		}
		else
		{
			perror("shmget");
		}
	}
	else{
	p = shmat(shmid,NULL,0);


	*(pid_t *)p=getpid();
	
	pause();
	pid =*(pid_t*)p;
	}


	while(1)
	{
		fgets(p,100,stdin);
		kill(pid,SIGUSR1);
		pause();
	}
	return 0;
}
