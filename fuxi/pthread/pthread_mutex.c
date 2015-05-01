#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex;
void * fun1 (void * buf)
{
	pthread_mutex_lock(&mutex);
	fgets(buf,40,stdin);
	pthread_mutex_unlock(&mutex);

}
void * fun2(void * buf)
{
	static int i = 100;
	pthread_mutex_lock(&mutex);
	printf("%s",(char *)buf);
	pthread_exit((void * )& i);
	pthread_mutex_unlock(&mutex);
}
int main(int argc, const char *argv[])
{
	pthread_t tid[2];
	pthread_mutex_init(&mutex,NULL);
	char buf[100]="hello to the world\n";
	int * val;
	pthread_create(&tid[0],NULL,fun1,buf);
	pthread_create(&tid[1],NULL,fun2,buf);
	pthread_join(tid[1],(void * )&val);
	pthread_mutex_destroy(&mutex);
	printf("%d\n",*val);
	while(1);
	return 0;
}
