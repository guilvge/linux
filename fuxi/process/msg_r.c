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
	mybuf.types = 100;
	key = ftok(".",'a');
	int len = sizeof(mybuf)-sizeof(long);
	if((msgid = msgget(key,IPC_CREAT | IPC_EXCL | 0664))==-1)
	{
		if(errno ==EEXIST)
		{
			msgid = msgget(key,0664);	
		}
	}
	while(1)
	{
		msgrcv(msgid,&mybuf,len,0,0);	
		printf("%s",mybuf.buf);
	}
	return 0;
}
