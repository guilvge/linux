#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
pthread_mutex_t mutex;
sem_t sem_r,sem_w;
void * fun1 (void * buf)
{
	while(1)
	{
		sem_wait(&sem_w);
		pthread_mutex_lock(&mutex);
		fgets(buf,40,stdin);
		pthread_mutex_unlock(&mutex);
		sem_post(&sem_r);
	}

}
void * fun2(void * buf)
{
	static int i = 100;
	while(1)
	{
		sem_wait(&sem_r);
		pthread_mutex_lock(&mutex);
		printf("%s",(char *)buf);
	//	pthread_exit((void * )& i);
		pthread_mutex_unlock(&mutex);
		sem_post(&sem_w);
	}
}
int main(int argc, const char *argv[])
{
	pthread_t tid[2];
	pthread_mutex_init(&mutex,NULL);
	sem_init(&sem_r,0,0);
	sem_init(&sem_w,0,1);
	char buf[100]="hello to the world\n";
	int * val;
	pthread_create(&tid[0],NULL,fun1,buf);
	pthread_create(&tid[1],NULL,fun2,buf);
//	pthread_join(tid[1],(void * )&val);
	pthread_join(tid[1],NULL);
//	printf("%d\n",*val);
//	while(1);
	return 0;
}
