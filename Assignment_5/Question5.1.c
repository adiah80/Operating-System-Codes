// Assignment 5.1
// gcc -lpthread -lrt -pthread Question5.1.c -w && ./a.out
// Sample input 5 3

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
 
sem_t customers;
sem_t barber; 
sem_t cutting;
sem_t mutex;

int customer1 = 0;
int allDone = 0;
int n;

void critical_section(int num){
	printf("Customer %d cutting hair.\n", num);
	sleep(3);
}

void *barbers(void *arg){
	while(!allDone){

		sem_wait(&customers); 		// Sleeps when no one is waiting.

		if(!allDone){
			sem_wait(&mutex); 		// Barber begins cutting hair.
			customer1--;
			sem_post(&barber); 	
			sem_post(&mutex);

			printf("The barber is cutting hair\n");
			sem_wait(&cutting);
		}
	}

	printf("The barber is going home for the day.\n");
}

void *customer(void *args){
	int num = (int)args;

	sem_wait(&mutex);

	if(customer1 < n){
		customer1++;				// Customer enters.
		sem_post(&customers);		// Customer must wake him.
		sem_post(&mutex);		
		sem_wait(&barber);			// Barber set to busy. Customers must wait.

		// Critical Section
		critical_section(num);
		
		sem_post(&cutting);
	}

	else{
		printf("Customer %d leaving barber shop.\n", num);
		sem_post(&mutex);
	}
}

int main(){
	printf("Enter Number of chairs : ");
	scanf("%d",&n); 			// number of chairs

	int numcust;
	printf("Enter Number of customers : ");
	scanf("%d",&numcust); 		// number of customers
 
	pthread_t btid;				// barber_thread
	pthread_t tid[numcust];		// thread for each customer

	sem_init(&customers,0,0);	// Is there any customer?
	sem_init(&barber,0,0);		 
	sem_init(&cutting,0,0);
	sem_init(&mutex,0,1);

	pthread_create(&btid,NULL,barbers,NULL);
	
	for(int i=0; i<numcust; i++) {
		pthread_create(&tid[i],NULL,customer,i);
		sleep(1);
	}

	for(int i=0; i<numcust; i++){
		pthread_join(tid[i],NULL);
	}
	
	allDone = 1;
	sem_post(&customers);
	pthread_join(btid,NULL);
	return 0;
}


