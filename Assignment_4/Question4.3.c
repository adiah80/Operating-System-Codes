// Assignment 4.3
// gcc -lpthread -lrt -pthread Question4.3.c -w && ./a.out
// Note : Array elements must be distinct.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n1,n2,n;
int* arr1;
int* arr2;
int* result;

typedef struct {
	int value;
}number;

void* input(void* arg){
	printf("Enter size of array1 and array2\n");
	scanf("%d %d",&n1,&n2);
	n=n1+n2;
	arr1 = (int*) malloc(sizeof(int)*n1);
	arr2 = (int*) malloc(sizeof(int)*n2);
	result = (int*) malloc(sizeof(int)*n);

	printf("Enter array 1\n");
	for(int i=0; i<n1; i++)
		scanf("%d",&arr1[i]);

	printf("Enter array 2\n");
	for(int i=0; i<n2; i++)
		scanf("%d",&arr2[i]);

}


void* findposA(void* arg) {
	number* num = (number*) arg;
	int index = num->value;
	//printf("%d..\n",index);
	int value = arr1[index];
	int* p = (int*)malloc(sizeof(int)); 

	if(value > arr2[n2-1]) {
		*p = index + n2;
		pthread_exit(p);
	}

	int lo = 0;
	int hi = n2-1;


	while(lo<hi) {
		int mid = (lo+hi)/2;
		if(value > arr2[mid]) lo = mid + 1;
		else hi = mid;

		if(lo==hi-1) {
			if(value < arr2[lo]) *p = index + lo;
			else *p = index + hi;
			pthread_exit(p);
		}
	}

	*p = index + lo;
	pthread_exit(p);
}


void* findposB(void* arg){
	number* num = (number*) arg;
	int index = num->value;
	//printf("%d,,\n",index);
	int value = arr2[index];
	int* p = (int*)malloc(sizeof(int)); 


	if(value > arr1[n1-1]){
		*p = index + n1;
		pthread_exit(p);
	}

	int lo = 0;
	int hi = n1-1;

	while(lo<hi){
		int mid = (lo+hi)/2;

		if(value > arr1[mid]) lo = mid + 1;
		else hi = mid;

		if(lo==hi-1){
			if(value < arr1[lo]) *p = index + lo;
			else *p = index + hi;
			pthread_exit(p);
		}
	}

	*p = index + lo;
	pthread_exit(p);
}


int main() {
	pthread_t input_tid;
	pthread_create(&input_tid,NULL,input,NULL);
	pthread_join(input_tid,NULL);

	pthread_t procA[n1];
	pthread_t procB[n2];

	for(int i=0; i<n1; i++)	{
		number* num = (number *) malloc(sizeof(number));
		num->value = i;
		pthread_create(&procA[i],NULL,findposA,num);
	}

	for(int i=0; i<n2; i++) {
		number* num = (number *) malloc(sizeof(number));
		num->value = i;
		pthread_create(&procB[i],NULL,findposB,num);
	} 

	for(int i=0; i<n1; i++) {
		int* position;
		void* faltu;
		pthread_join(procA[i], &faltu);
		position = (int*) faltu;

		// printf("%d : %d\n", arr1[i],*position);
		result[*position] = arr1[i];
	}

	for(int i=0; i<n2; i++) {
		int* position;
		void* faltu;
		pthread_join(procB[i], &faltu);
		position = (int*) faltu;

		//printf("%d : %d\n", arr2[i],*position);
		result[*position] = arr2[i];
	}

	printf("Output array : ");
	for(int i=0; i<n; i++) printf("%d ",result[i]);
	printf("\n");
}