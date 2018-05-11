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
  return (double) ((double)t.tv_sec + (double)t.tv_usec / 1e6);
}

void *mythread(void *arg){
	list_t *jb = (list_t *) arg;
  int *element = NULL;
	int i;
	for(i = 0; i < max; i++){
    element = (int *)malloc(sizeof(int));
		List_Insert(jb, element, i);
	}
}

int main(int argc, char const *argv[])
{
	pthread_t *p = NULL;
	list_t *l = NULL;
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
			l = (list_t*)malloc(sizeof(list_t));

			List_Init(l);
			t_start = Get_time();
			for(k = 0; k <=i; k++){
				pthread_create(&(p[k]), NULL, mythread, l);
			}

			for (k = 0; k <= i; k++){
				pthread_join(p[k], NULL);
			}
			t_end = Get_time();
      delete_list(l);
			//printf("threads: %d time: %f\n", num, t_end - t_start);
			printf("%f ", t_end- t_start);
		}
		printf("\n");
	}
	return 0;

}
