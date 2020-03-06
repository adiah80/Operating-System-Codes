/*
	ADITYA AHUJA
	2017A7PS0080G	
	Program places a call to the wrapper_floatAdd function defined in wrapper.c 
	using macro defined in addWrapper.h, which checks the input and 
	inturn calls the system call floatAdd (no. 434) with the given input.

	Assumption:
	- Direct system call access is not allowed for the user.
	- User has read documentation and understands error codes of function call.
*/

#include<stdio.h>
#include"addWrapper.h"

int main(int argc, char *argv[]){
	float num1, num2;
	float ans;

    // INPUT
	printf("Enter Input: \n");
	scanf("%f %f",&num1, &num2);

    // Call to wrapper
	ans = floatAdd(num1,num2);

    // OUTPUT | ERROR HANDLING
	if(ans > 0)
		printf("Answer : %f \n",ans);
	else if(ans == -1)
		printf("ERROR: 1st Number is not Positive \n");
	else if(ans == -2)
		printf("ERROR: 1st Number is INF \n");
	else if(ans == -3)
		printf("ERROR: 2nd Number is not Positive \n");
	else if(ans == -4)
		printf("ERROR: 2nd Number is INF \n");
	else if(ans == -5)
		printf("ERROR: Sum overflow \n");
	else 
		printf("ERROR: Undefined behaviour \n");
	
	return 0;
}
