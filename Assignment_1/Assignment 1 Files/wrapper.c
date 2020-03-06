/*
    ADITYA AHUJA
    2017A7PS0080G   
    Wrapper that checks for valid input and places call to floatAdd system call

    Assumption:
    - Library documentation for my wrapper will mention negative values as error codes with meaning
      because printing will add unnecessary dependency to wrapper.

*/
#include<unistd.h>
#define ERROR_ST 2147483648     // ~ 1 00000000 00000000000000000000000 binary
#define EXP_MASK 2139095040     // ~ 0 11111111 00000000000000000000000 binary

/* 
    Pre-Condition : 
                    1. Any input allowed by compiler

    Post-Condition: 
                    1. Sum of NUM1 + NUM2 is returned or appropriate error value is returned
*/

union FL {
    int i; 
    float f;
};

float wrapper_floatAdd(float num1, float num2){
    union FL x1,x2,x3;
    long ans;
    x1.f = num1; 
    x2.f = num2;

    if(num1 <= 0)                   // if NUM1 is POSITIVE
        return -1;
    if((x1.i&EXP_MASK)>>23 == 255)  // if NUM1 is not INF
        return -2;
    if(num2 <= 0)                   // if NUM2 is POSITIVE
        return -3;
    if((x2.i&EXP_MASK)>>23 == 255)  // if NUM2 is not INF
        return -4;

    ans = syscall(434, x1.i, x2.i);

    if (ans < ERROR_ST){            // NORMAL CONDITION WITH SANITY CHECK [ 80% ]
        x3.i = ans;
        return x3.f;
    }
    else if(ans == ERROR_ST + 1)    // OVERFLOW CONDITION [ 20% ]
        return -5;
    else                            // FOR UNDEFINED BEHAVIOUR [ Incase of bad syscall number ]
        return -6;


}