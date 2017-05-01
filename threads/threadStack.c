#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4
#define N 1000
#define MEMEXTRA 1000000

pthread_attr_t attr;

void *work(void* args){
	double A[N][N];
	int i,j;
	long tid;
	tid = (long)args;
	size_t mystacksize;

	pthread_attr_getstacksize(&attr, &mystacksize);//puedo acceder a attr, pues es global
	printf("Thread: %ld size: %li",tid,mystacksize);
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			A[i][j] = (i*j)/3.452;
		}
	}
	pthread_exit(NULL);
}



int main(int argc, char const *argv[]){
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	size_t stacksize;
	
	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &stacksize);
	printf("Default stack size: %li \n", stacksize);

	stacksize = sizeof(double)*N*N+MEMEXTRA;
	printf("Stack size I'll need: %li \n", stacksize);

	pthread_attr_setstacksize(&attr, stacksize);

	for(t = 0; t < NUM_THREADS; t++){
		rc = pthread_create(&(threads[t]), &attr, work, (void*)t);
	}

	return 0;
}