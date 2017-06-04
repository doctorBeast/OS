#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
//#include<time.h>
#include<unistd.h>
#define num 5

int glob = 0;
int counter = 0;
pthread_cond_t read_phase = PTHREAD_COND_INITIALIZER;
pthread_cond_t write_phase = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *reader(void *param);
void *writer(void *param);

void main(){
	int i,temp[num];
	pthread_t read[num];
	pthread_t write[num];
	for(i=0;i<5;i++){
		if(pthread_create(&read[i],NULL,reader,NULL)!=0){
			fprintf(stderr,"Unable to create read thread\n");
			exit(1);
		}
		temp[i] = i;
		if(pthread_create(&write[i],NULL,writer,&temp[i])!=0){
			fprintf(stderr,"Unable to create write thread\n");
			exit(1);
		}
		sleep(0.9);
	}
	for(i = 0;i<5;i++){
		pthread_join(read[i],NULL);
		pthread_join(write[i],NULL);
	}
}

void *reader(void *param){
	pthread_mutex_lock(&m);
		while(counter == -1){
			pthread_cond_wait(&read_phase,&m);
		}
		counter++;
	pthread_mutex_unlock(&m);
	printf("The data read is : %d\n",glob);
	pthread_mutex_lock(&m);
		counter--;
		if(counter == 0){
			pthread_cond_signal(&write_phase);
		}
	pthread_mutex_unlock(&m);
}

void *writer(void *param){
int a;
int *p = (int *)param;
a = *p;

	pthread_mutex_lock(&m);
		while(counter != 0){
			pthread_cond_wait(&write_phase,&m);
		}
		counter = -1;
	pthread_mutex_unlock(&m);
	//Here I will write the data to be made changed to
	glob = a;
	printf("The written data is :%d\n",glob)
;	pthread_mutex_lock(&m);
		counter = 0;
		pthread_cond_signal(&write_phase);
		pthread_cond_broadcast(&read_phase);
	pthread_mutex_unlock(&m);

}
