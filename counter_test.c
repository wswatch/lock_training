#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include "counter.h"
#include "list.h"
#include "hash.h"

int t_num;
int max;
int times;

double Get_time(){
  struct timeval t;
  int rc = gettimeofday(&t, NULL);
 // assert(rc == 0);
  return (double) ((double)t.tv_sec + (double)t.tv_usec / 1e6);
}

void *mythread(void *arg){
	counter_t *jb = (counter_t *) arg;
	int i;
	for(i = 0; i < max; i++){
		Counter_Increment(jb);
	}
}

int main(int argc, char const *argv[])
{	
	pthread_t *p = NULL;
	counter_t *c = NULL;
	int i,j,k;
	double t_start, t_end;
	if(argc != 4){
		perror("Error! Need four arguments!");
		return -1;
	}

	t_num = atoi(argv[1]);
	max = atoi(argv[2]);
	times = atoi(argv[3]);

	for(i = 0; i < t_num; i++){
		printf("With %d\n", i+1);
		
		for(j = 0; j < times; j++){
			p = (pthread_t*)malloc(sizeof(pthread_t)*(max + 1));
			c = (counter_t*)malloc(sizeof(counter_t));

			t_start = Get_time();

			Counter_Init(c, 0);
			for(k = 0; k <=i; k++){
				pthread_create(&(p[k]), NULL, mythread, c);
			}

			for (k = 0; k <= i; k++){
				pthread_join(p[k], NULL);
			}
			delete_counter(c);
			double t_end = Get_time();
			//printf("threads: %d time: %f\n", num, t_end - t_start);
			printf("%f ", t_end- t_start);
		}
		printf("\n");
	}
	return 0;
}
