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
int buckets;


double Get_time(){
  struct timeval t;
  int rc = gettimeofday(&t, NULL);
  return (double) ((double)t.tv_sec + (double)t.tv_usec / 1e6);
}

void *mythread(void *arg){
	hash_t *jb = (hash_t *) arg;
	int i;
	int *element = NULL;
	for(i = 0; i < max; i++){
    element = (int*)malloc(sizeof(int));
		Hash_Insert(jb, element, i);
	}
}


int main(int argc, char const *argv[])
{
	pthread_t *p = NULL;
	hash_t *h = NULL;
	int i,j,k;
	double t_start, t_end;
	if(argc != 4){
		perror("Error! Need four arguments!");
		return -1;
	}

	t_num = atoi(argv[1]);
	max = atoi(argv[2]);
	times = atoi(argv[3]);
	buckets = 30;
	i = 1;
	while(i <= buckets){
		printf("With %d\n", i);

		for(j = 0; j < times; j++){
			p = (pthread_t*)malloc(sizeof(pthread_t)*(max + 1));
			h = (hash_t*)malloc(sizeof(hash_t));

			Hash_Init(h, i);
			t_start = Get_time();
			for(k = 0; k <=t_num; k++){
				pthread_create(&(p[k]), NULL, mythread, h);
			}

			for (k = 0; k <= t_num; k++){
				pthread_join(p[k], NULL);
			}
			t_end = Get_time();
      delete_hash(h);
			printf("%f ", t_end - t_start);
		}
		i += 2;
		printf("\n");
	}
	return 0;

}
