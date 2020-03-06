/*
	ADITYA AHUJA
	2017A7PS0080G
	Definition of custom system call (no. 434): 'floatAdd'
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/syscalls.h>
#include "floatAdd.h"

#define EXP_MASK 2139095040		// ~ 0 11111111 00000000000000000000000 binary
#define MNT_MASK 8388607        // ~ 0 00000000 11111111111111111111111 binary 
#define ERROR_ST 2147483648     // ~ 1 00000000 00000000000000000000000 binary

/* 
	Pre-Condition : 1. num1 > 0 and num2 > 0
					2. num1 and num2 are valid floating point numbers

	Post-Condition: 
                    1. num1 + num2 is a valid positive floating point number
                    2. num1 + num2 is returned
*/

SYSCALL_DEFINE2(floatAdd, int, num1, int, num2 ){
	int exp1,exp2;
	int mnt1,mnt2;
	int exp,mnt;
	int ans;

	// GETTING EXPONENT AND MANTISSA FOR EACH NUM
	// NUM1
	exp1 = num1 & EXP_MASK;
	exp1 = exp1>>23;
	mnt1 = num1 & MNT_MASK;
	if(exp1 > 0)							// 1.fraction form
		mnt1 += (1<<23);

	// NUM2
	exp2 = num2 & EXP_MASK;
	exp2 = exp2>>23;
	mnt2 = num2 & MNT_MASK;
	if(exp2 > 0)							// 1.fraction form
		mnt2 += (1<<23);
	
	// ADDING THE FLOATING POINT NUMBERS
	while(exp1<exp2){
		exp1 = exp1+1;
		mnt1 = mnt1>>1;
	}
	while(exp2<exp1){
		exp2 = exp2+1;
		mnt2 = mnt2>>1;
	}
	exp = exp1;
	mnt = mnt1+mnt2;
	if(mnt> ((MNT_MASK<<1)+1) ){
		mnt = mnt>>1;
		exp+=1;
	}

	// OVERFLOW
	if(exp>=255)
		return ERROR_ST+1;

	//exp = exp & 255;
	mnt = mnt & MNT_MASK;	
	ans = 0;
	ans = ans + (exp<<23) + mnt;
	return ans;
}
