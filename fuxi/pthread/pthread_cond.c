#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
void * fun1 (void * buf)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		fgets(buf,40,stdin);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		usleep(1000);
	}

}
void * fun2(void * buf)
{
	//static int i = 100;
	printf("fun2\n");
	while(1)
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		printf("%s",(char *)buf);
		pthread_mutex_unlock(&mutex);
	}
}
int main(int argc, const char *argv[])
{
	pthread_t tid[2];
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	char buf[100]="hello to the world\n";
	int * val;
	pthread_create(&tid[0],NULL,fun1,buf);
	pthread_create(&tid[1],NULL,fun2,buf);
	pthread_join(tid[1],NULL);
	printf("%d\n",*val);
	while(1);
	return 0;
}
