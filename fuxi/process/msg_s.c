#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <fcntl.h>
struct msgbuf{
	long types;
	char buf[100];
};
int main(int argc, const char *argv[])
{
	key_t key;
	int msgid;
	struct msgbuf mybuf;
	int len = sizeof(mybuf) - sizeof (long);
	key = ftok(".",'a');
	if((msgid = msgget(key,IPC_CREAT | IPC_EXCL | 0664))==-1)
	{
		if(errno ==EEXIST)
		{
			msgid = msgget(key,0664);	
		}
	}
	while(1)
	{
		fgets(mybuf.buf,sizeof(mybuf.buf),stdin);
		mybuf.types = 100;

		msgsnd(msgid,&mybuf,len,0);	
	}
	return 0;
}
