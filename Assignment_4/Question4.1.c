// Assignment4.1
// gcc -lpthread -lrt -pthread Question4.1.c -w && ./a.out


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int* mat1;
int* mat2;
int* mat3;
int r1,c1,r2,c2;
int m,k,n;

typedef struct{
	int r;
	int c;
}coordinates;

void* semi(void* arg){
	coordinates* temp = (coordinates*) arg;
	int r = temp->r;
	int c = temp->c;
	int sum = 0;

	for(int i=0; i<k; i++)
		sum += mat1[r*n+i] * mat2[i*n+c];

	// printf("%d\n", sum);

	int* p = (int*)malloc(sizeof(int)); 
    *p = sum; 
	pthread_exit(p);
}


void* runner(void* arg) {
	//sub-thread to create m*n threads
	pthread_t* tids = (pthread_t*) malloc(sizeof(pthread_t)* m*n);

	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){

			coordinates* temp_co = (coordinates*) malloc(sizeof(coordinates));
			temp_co->r = i;
			temp_co->c = j;
			pthread_create(&tids[i*n + j],NULL,semi,temp_co);
		}
	}

	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			void* return_val;
			pthread_join(tids[i*n + j],&return_val);
			
			int* val = (int*) return_val;
			// printf("val : %d\n", *val);
			mat3[i*n + j] = *val;
		}
	}

	pthread_exit(NULL);
}

int main(void){
	printf("Enter the values m,k,n for m*k and k*n matrix\n");
	scanf("%d %d %d",&m,&k,&n);
	r1 = m; 
	c1 = k; 
	r2 = k; 
	c2 = n;

	if(r1==0 || c1 == 0 || r2 == 0 || c2 == 0){
		printf("enter non zero values only\n");
		return 0;
	}

	mat1 = (int*) malloc(sizeof(int)*r1*c1); // a
	mat2 = (int*) malloc(sizeof(int)*r2*c2); // b
	mat3 = (int*) malloc(sizeof(int)*r1*c2); // c

	printf("enter %d values for matrix 1\n",r1*c1);
	for(int i=0; i<r1*c1; i++) scanf("%d",&mat1[i]);

	printf("enter %d values for matrix 2\n",r2*c2);
	for(int i=0; i<r2*c2; i++) scanf("%d",&mat2[i]);

	pthread_t temp;
	pthread_create(&temp,NULL,runner,NULL);
	pthread_join(temp,NULL);

	printf("---------------------\n");
	printf("Output Matrix: \n");
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++) printf("%d ", mat3[i*n + j]);
		printf("\n");
	}
}