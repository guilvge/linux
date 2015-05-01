/*
 *该程序实现线程的创建，但是没有进行
 *线程的同步。
 *
 *
 *
 * */
#include <stdio.h>


#include <pthread.h>
void * fun1 (void * buf)
{

	fgets(buf,40,stdin);

}
void * fun2(void * buf)
{
	static int i = 100;
	printf("%s",(char *)buf);
	pthread_exit((void * )& i);
}
int main(int argc, const char *argv[])
{
	pthread_t tid[2];
	char buf[100]="hello to the world\n";
	int * val;
	pthread_create(&tid[0],NULL,fun1,buf);
	pthread_create(&tid[1],NULL,fun2,buf);
	pthread_join(tid[1],(void * )&val);
	printf("%d\n",*val);
	while(1);
	return 0;
}
