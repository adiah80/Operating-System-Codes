// Assignment 3.1
// gcc -lpthread -lrt -pthread Question3.1.c -w && ./a.out

// Sample input:
// 4
// 0 0 1 0
// 1 0 0 1
// 1 0 1 0
// 1 0 0 0


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
 
 
int main()
{ 
    int n;
    printf("Enter Grid Dimension : ");
    scanf("%d",&n);
    if(n==1) {printf("Path not possible n=1\n"); return 0;}

    printf("Enter %d by %d Grid: \n", n,n);
    int arr[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&arr[i][j]);
        }
    }
 	
 	printf("------------------------\n");

    int l=0;
    int r=0;
    pid_t pidleft;
    pid_t pidright;
    while(l!=(n-1) || r!=(n-1)){
       int f=0;
       
       if(l<(n-1)){
            pidleft = fork(); 
            if(pidleft==0){
                if(arr[l+1][r]==1){
                    while(wait(NULL) != -1);
                    exit(3);
                }
                f=1;
                l = l+1;
                continue;
            }
            if(f==1) l = l-1;
       }

       f=0;
       if(r<(n-1)){
           pidright = fork();
           if(pidright==0){
           if(arr[l][r+1]==1){
               while(wait(NULL) != -1);
               exit(3);
           }
           printf("My PID=%d My PPID = %d Right\n",getpid(),getppid());
           f=1;
           r = r+1;
           continue;
       }
           if(f==1) r = r-1;
       }
       if(pidright>0 || pidleft>0){
           break;
       }
    }
    if(l==(n-1) && r==(n-1)){
        exit(10);
    }

    int status;
    int f=0;
    while(1){
        pid_t pid= wait(&status);
        if(pid == -1){
            break;
        }
        if((status/256)==10){
            printf("%d %d %d\n",pid,l,r);
            if(l == 0 && r == 0) printf("Path Found, Exiting.\n");
            f = 1;
            exit(10);
        }
    }

    if(f==0) printf("Path Failed.\n");
    return 0;
}