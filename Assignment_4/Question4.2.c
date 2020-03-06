// Assignment4.2
// gcc -lpthread -lrt -pthread Question4.2.c -w && ./a.out

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
     
int n,m;
int* num1;
int* num2;
int* num;
int len1,len2,len;

typedef struct{
    int val;
}number; 
     
void* runner(void* arg){
    number* numptr = (number*) arg;
    int val = numptr->val;
    int sum = 0;
     
    for(int i=0; i<=val; i++)
        sum += num1[i]*num2[val-i]; 

    // printf("%d : %d\n",val,sum);
    int* p = (int*) malloc(sizeof(int));
    *p = sum;
    pthread_exit(p);
}
     
int main(){
    printf("Enter 2 numbers\n");
    scanf("%d %d",&n,&m);

    int temp = n;
    while(temp!=0){
        len1++;
        temp/=10;
    }
     
    temp = m;
    while(temp!=0){
        len2++;
        temp/=10;
    }
     
    len = len1+len2;
    num1 = (int*) malloc(sizeof(int)*len1); // Digits of num1
    num2 = (int*) malloc(sizeof(int)*len2); // Digits of num2
    num = (int*) malloc(sizeof(int)*len);

    temp = n;
    int index = 0;
    while(temp != 0){
        num1[index] = temp%10;
        index++;
        temp = temp/10;
    }

    temp = m;
    index = 0;
    while(temp != 0){
        num2[index] = temp%10;
        index++;
        temp = temp/10;
    }

    pthread_t tids[len];

    for(int i=0; i<len; i++){
        number* temp = (number*) malloc(sizeof(number));
        temp->val = i;
        pthread_create(&tids[i], NULL, runner, temp);
    }
    
    for(int i=0; i<len; i++){
        void* return_val;
        pthread_join(tids[i],&return_val);
        int* val = (int*) return_val;
        num[i] = *val;
    }

    // for(int i=0; i<len; i++) printf("%d ", num[i]);
    // printf("\n");

    int ans = 0;
    int carry = 0;
    int pow = 1;
    for(int i=0; i<len; i++){
        int value = num[i] + carry;
        ans = (value%10)*pow+ ans;
        carry = value/10;
        pow = pow*10;
    }

    printf("Product of %d and %d is : %d\n",n, m, ans);
}