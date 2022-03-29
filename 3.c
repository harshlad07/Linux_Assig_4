#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void *myinit()
{
	printf("\n I am in inti fun\n");          // will run only once initialization code
}

void *mythread(void *i)
{
	printf("\n I am in my thread\n");
	pthread_once(&once, (void *)myinit);
	printf("\n exit from mythread : %d\n", (int *)i);
}


int main(){
	
	pthread_t thread, thread1, thread2;
	
	pthread_create(&thread,NULL, mythread, (void *)1);
	
	pthread_create(&thread,NULL, mythread, (void *)2);
	
	pthread_create(&thread,NULL, mythread, (void *)3);
		
	printf("\nexit from main thread\n");
	pthread_exit(NULL);
	
return 0;
}
