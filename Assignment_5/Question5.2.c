// gcc -lpthread -lrt -pthread 5_2_smoker.c -w && ./a.out

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>

sem_t match,paper,tobacco,agent,lock;

void *agentJ(void *arg){
	while(1){
		sem_wait(&lock);
		int randNum = rand()%3+1;
		if(randNum == 1){
			sem_post(&match); 		// wake up smoker with match; 
		}
		else if(randNum == 2){
			sem_post(&paper); 		// wake up with paper;
		}
		else{
			sem_post(&tobacco);		// wake up with tobacco;
		}
		sem_post(&lock);
		sem_wait(&agent); 			// agent sleeps
	}
}

void *smoker1(void *arg){
	while(1){
		sem_wait(&tobacco);
		sem_wait(&lock);
		sem_post(&agent);
		sem_post(&lock);
		sleep(1);
		printf("SMOKER1 goes to smoke.\n");
	}
 
}

void *smoker2(void *arg){
	while(1){
		sem_wait(&match);
		sem_wait(&lock);
		sem_post(&agent);
		sem_post(&lock);
		sleep(1);
		printf("SMOKER2 goes to smoke.\n" );
	}
 
}

void *smoker3(void *arg){
	while(1){
		sem_wait(&paper);
		sem_wait(&lock);
		sem_post(&agent);
		sem_post(&lock);
		sleep(1);
		printf("SMOKER3 goes to smoke.\n");
	}
 
}

int main(){

	pthread_t moker1,moker2,moker0,agnt;
	sem_init(&match,0,0);
	sem_init(&tobacco,0,0);
	sem_init(&paper,0,0);
	sem_init(&agent,0,0);
	sem_init(&lock,0,1);

	printf("SMOKER1 has tobacco\n");
	printf("SMOKER2 has paper\n");
	printf("SMOKER3 has matches\n");
	pthread_create(&agnt,0,agentJ,0);
	pthread_create(&moker0,0,smoker1,(void*)0);
	pthread_create(&moker1,0,smoker2,(void*)1);
	pthread_create(&moker2,0,smoker3,(void*)2);

	while(1);	
	return 0;
}