// Assignment 2.1
// gcc -lpthread -lrt -pthread Question2.1.c -w && ./a.out 1 2
// Sample input : 1 2

#include<stdio.h>			// For printf().
#include <stdlib.h>			// For atoi().
#include <unistd.h>			// For fork().
#include <sys/ipc.h> 
#include <sys/shm.h>
#include<sys/wait.h>  
#include <assert.h> 
// #include <sys/types.h>

#define line1		print("-----------------------------------\n")
#define line2		print("===================================\n")
#define line3		printf("-----------------------------------[%d]\n", getpid())
#define print       if(getpid() == main_pid) printf

#define ptype(x) print("%s\n",_Generic((x),                                                 \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "pointer to char",        \
       void *: "pointer to void",                int *: "pointer to int",         \
      default: "other"))


int num_children;
int max_depth;
int main_pid;

int mem_size, shm_ID;

// -------------------------------------------------------------------

int sfork(){
	int f = fork();
	if(f) printf("##### %d -> %d #####\n", getpid(), f); 
	return f;
}

void print_arr(int* arr, int arr_size){
	for(int i=0; i<arr_size; i++) {
		print("%d ",arr[i]);
	}
	print("\n");
}

void start(int pID){
	kill(pID, SIGCONT);
	printf("[%d] Started process %d\n", getpid(), pID);
	printf("---------------------------------------------\n");
}

void stop(int pID){
	kill(pID, SIGSTOP);
	printf("[%d] Stopped process %d\n", getpid(), pID);
}

int main(int argc, const char *args[]){

	main_pid = getpid();

	// Parse arguments.
	num_children = atoi(args[1]);
	max_depth = atoi(args[2]);
	printf("Num Children : %d\n", num_children);
	printf("Depth : %d\n", max_depth);

	// Allot memory for storing number_of_nodes in a level.
	int mem_size = 3;
	int shm_ID = shmget(IPC_PRIVATE, mem_size*sizeof(int), IPC_CREAT|0666);	
	int *level_node_count = (int *)shmat(shm_ID, 0, 0);	
	*level_node_count = 1;

	// Fill the level_node_count array.
	int node_count = num_children;
	for(int cur_depth=0; cur_depth<max_depth; cur_depth++){
		level_node_count[cur_depth] = node_count;
		node_count = (node_count * (node_count+1))/2;
	}

	// Allot memory for 2D array storing pID's.
	mem_size = max_depth;
	shm_ID = shmget(IPC_PRIVATE, mem_size * sizeof(int *), IPC_CREAT|0666);	
	int **starting_pos = (int **) shmat(shm_ID, NULL, 0);

	// Allot memory for all level arrays.
	for(int level=0; level<max_depth; level++){
		mem_size = level_node_count[level];
		shm_ID = shmget(IPC_PRIVATE, mem_size * sizeof(int), IPC_CREAT|0666);	
		int *index = (int *) shmat(shm_ID, NULL, 0);
		starting_pos[level] = index;
	}

	// Allot memory for temporary child count.
	mem_size = 1;
	shm_ID = shmget(IPC_PRIVATE, mem_size*sizeof(int), IPC_CREAT|0666);	
	int *child_count = (int *)shmat(shm_ID, NULL, 0);

	print("Nodes per level : ");
	print_arr(level_node_count, max_depth);

	//---------------------------------------------------------------
	line2;
	print("K.I.N.G. : %d\n", main_pid);

	// Fill the `first` array.
	int f = 1;
	for(int i=0; i<num_children; i++){
		
		if(f) {
			f = sfork();
			if(f) {
				starting_pos[0][i] = f;
				stop(f);
			}
			else {
				printf("--------------------------------[%d] Here 1\n", getpid());
				// stop(getpid());
			}
			// else pause();
		}
		else break;
	}

	print_arr(starting_pos[0], num_children);

	//---------------------------------------------------------------
	line2;

	int done = 0;
	if(getpid() == main_pid) done=1;

	// For each level :
	for(int level = 0; level < max_depth-1; level++){

		if(done) break;

		// line3;	
		// printf("%d : Level %d\n", getpid(), level);

		int num_parents = level_node_count[level];
		int num_children = level_node_count[level+1];

		// For each parent in that level :
		for(int parent = 0; parent < num_parents; parent++){
			int parent_pid = starting_pos[level][parent];			// Get parent's pID

			printf("-Examine : %d %d\n", parent_pid, getpid());

			// Make children.
			if(getpid() == parent_pid){	
				
				
				printf("--> Inside : %d\n", getpid());

				f = 1;
				for(int child = 0; child <= parent; child++){
					f = sfork();
					
					if(f){
						done = 1;
						starting_pos[level+1][*child_count] = f;
						(*child_count)++;
						printf("[%d] %d\n",getpid(), *child_count);
						stop(f);
					}

					else{
						printf("--------------------------------[%d] Here 2\n", getpid());
						// stop(getpid());
						done = 0;
						// printf("Done : %d\n", done);
						break;
					}
				}

				// printf("[%d] Here\n", getpid());
				// printf("f : %d\n", f);
				// printf("Done : %d\n", done);
				if(!f) break;

				printf("Num_parents : %d\n", num_parents);
				printf("Parent : %d\n", parent);
				if(parent < num_parents-1) start(starting_pos[level][parent+1]);
				else {
					start(starting_pos[level+1][0]);
					*child_count = 0;
				}
				break; 
			}
		}
	}

	printf("[%d] Over.\n", getpid());
	if(getpid() == main_pid) start(starting_pos[0][0]);


	if(getpid() == starting_pos[max_depth-2][level_node_count[max_depth-2]-1]){
		for(int i = 0; i < level_node_count[max_depth-1]; i++){
			start(starting_pos[max_depth-1][i]);
		}
	}

	while(wait(NULL) > 0);
	line1;
	print_arr(starting_pos[0], level_node_count[0]);
	print_arr(starting_pos[1], level_node_count[1]);
	print_arr(starting_pos[2], level_node_count[2]);
	return 0;
}



/*
##########################################################################################


REFER :  http://www.csl.mtu.edu/cs4411.ck/www/
		http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/process.html

int mem_size = 4;
int shm_ID = shmget(IPC_PRIVATE, mem_size*sizeof(int), IPC_CREAT|0666);		// create
int *mem = (int *)shmat(shm_ID, NULL, 0);									// attach
shmdt(shm_ptr);																// detach
shmctl(shm_ID, IPC_RMID, NULL);												// destroy


##########################################################################################
*/