#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <bits/types.h>
#include <sys/types.h>

static pthread_spinlock_t spinlock;
volatile int slock;

void *spinlockthread(void *i)
{
	int rc;
	int count = 0;
	printf("entered thread %d, getting spin lock\n", (int *)i);
	rc = pthread_spin_lock(&spinlock);
	
	printf("%d thread unlock the spin lock\n", (int *)i);
	rc = pthread_spin_unlock(&spinlock);
	printf("%d thread completed", (int *)i);
	return NULL;
}


int main(){
	
	int rc = 0;
	pthread_t thread, thread1;
	
	if(pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE)!=0)
	perror("init");
	printf("main, getspin lock\n");
	rc = pthread_spin_lock(&spinlock);
	
	printf("main, create the spin lock thread\n");
	rc = pthread_create(&thread, NULL, spinlockthread, (int *)1);
	
	printf("main, wait a bit holding the spin lock\n");
	sleep(10);
	
	printf("main, now unlock the spin lock\n");
	
	rc = pthread_spin_unlock(&spinlock);
	
	if(rc == 0)
	{
		printf("\n main thread successfully unlocked\n");
	}
	else{
		printf("\n mainthread unsuccessfully unlocked\n");
	}
	
	printf("main, wait for thread to end\n");
	rc = pthread_join(thread, NULL);
	
	printf("main completed\n");
	
return 0;
}
