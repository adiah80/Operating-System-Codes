# Topics

 Questions are taken from assignments of CS F372 [Operating Systems] course offered at BITS-Pilani, Goa.

Topics covered in the exercises include :

- Assignment 1 : Kernel Recompilation
- Assignment 2/3 : Processes
- Assignment 4 : Threads
- Assignment 5 : Synchronization

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


# Assignment 2

## Question 2.1

Execute : `gcc -lpthread -lrt -pthread Question2.1.c -w && ./a.out 1 2`

Output : 
```
Num Children : 1
Depth : 2
Nodes per level : 1 1 
===================================
K.I.N.G. : 19020
##### 19020 -> 19021 #####
[19020] Stopped process 19021
19021 
===================================
[19020] Over.
[19020] Started process 19021
-----------------------------------------------------------------------------
[19021] Here 1
-Examine : 19021 19021
--> Inside : 19021
##### 19021 -> 19022 #####
[19021] 1
[19021] Stopped process 19022
Num_parents : 1
Parent : 0
[19021] Started process 19022
-----------------------------------------------------------------------------
[19022] Here 2
[19021] Over.
[19022] Over.
[19021] Started process 19022
--------------------------------------------------------------------------------
19021 
19022 
```

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Assignment 3

## Question 3.1

Exeute : `gcc -lpthread -lrt -pthread Question3.1.c -w && ./a.out`

Input : 
```
Enter Grid Dimension : 4
Enter 4 by 4 Grid: 
0 0 1 0
1 0 0 1
1 0 1 0
1 0 0 0 
```

Output : 
```
My PID=19222 My PPID = 19218 Right
My PID=19226 My PPID = 19223 Right
Path Failed.
My PID=19231 My PPID = 19229 Right
My PID=19232 My PPID = 19231 Right
19232 3 2
19231 3 1
19229 2 1
19225 1 1
19223 0 1
19222 0 0
Path Found, Exiting.
```

## Question 3.2

Execute : `gcc -lpthread -lrt -pthread Question3.2.c -w && ./a.out`

Input : 
```
dummy_command
entry
ls
ls -l
exit
```

Output : 
```
dummy_command
Command line interpreter not started, enter `entry` command.
entry

Welcome to Aditya's Shell 
************************ 

>> ls
Got ls
a.out  Assignment_3_Process.pdf  Question3.1.c	Question3.2.c

>> ls -l
Got ls -l
total 356
-rwxrwxrwx 1 root root  18000 Mar  7 00:45 a.out
-rwxrwxrwx 1 root root 330121 Oct 14 02:58 Assignment_3_Process.pdf
-rwxrwxrwx 1 root root   1969 Mar  7 00:43 Question3.1.c
-rwxrwxrwx 1 root root   4458 Mar  7 00:20 Question3.2.c

>> exit
Exiting.

```

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Assignment 4

## Question 4.1

Execute : `gcc -lpthread -lrt -pthread Question4.1.c -w && ./a.out`

Input : 
```
Enter the values m,k,n for m*k and k*n matrix
2 3 2
enter 6 values for matrix 1
1 2 3 4 5 6
enter 6 values for matrix 2
1 2 3 4 5 6
```

Output : 
```
Output Matrix: 
22 28 
40 52 
```


## Question 4.2

Execute : `gcc -lpthread -lrt -pthread Question4.2.c -w && ./a.out`

Input : 
```
Enter 2 numbers
81 983
```

Output : 
```
Product of 81 and 983 is : 79623
```


## Question 4.3

Execute : `gcc -lpthread -lrt -pthread Question4.3.c -w && ./a.out`

Input : 
```
Enter size of array1 and array2
2 4
Enter array 1
1 10
Enter array 2
2 4 6 7
```

Output : 
```
Output array : 1 2 4 6 7 10 

```

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Assignment 5

## Question 5.1

Execute : `gcc -lpthread -lrt -pthread Question5.1.c -w && ./a.out`

Input : 
```
Enter Number of chairs : 5
Enter Number of customers : 3
```

Output : 
```
The barber is cutting hair
Customer 0 cutting hair.
Customer 1 cutting hair.
The barber is cutting hair
The barber is cutting hair
Customer 2 cutting hair.
The barber is going home for the day.
```


## Question 5.2

Execute : `gcc -lpthread -lrt -pthread Question5.2.c -w && ./a.out`
Output : 
```
SMOKER1 has tobacco
SMOKER2 has paper
SMOKER3 has matches
SMOKER3 goes to smoke.
SMOKER2 goes to smoke.
SMOKER3 goes to smoke.
SMOKER3 goes to smoke.
SMOKER1 goes to smoke.
SMOKER3 goes to smoke.
SMOKER3 goes to smoke.
SMOKER2 goes to smoke.
SMOKER2 goes to smoke.
SMOKER1 goes to smoke.
SMOKER3 goes to smoke.
SMOKER3 goes to smoke.
SMOKER1 goes to smoke.
SMOKER3 goes to smoke.
SMOKER1 goes to smoke.
SMOKER3 goes to smoke.
SMOKER2 goes to smoke.
SMOKER2 goes to smoke.
SMOKER3 goes to smoke.
SMOKER3 goes to smoke.
SMOKER1 goes to smoke.
SMOKER1 goes to smoke.
SMOKER2 goes to smoke.
SMOKER2 goes to smoke.
SMOKER1 goes to smoke.
SMOKER1 goes to smoke.
^C
```
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
