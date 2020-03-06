// Assignment 3.2
// gcc -lpthread -lrt -pthread Question3.2.c -w && ./a.out
// Sample Input:
// wrong_command
// entry
// ls
// ls -l
// exit

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define MAX_LENGTH 1024

char command[MAX_LENGTH];
int len,fd,logSwitch;
time_t t;
char lt[26];

void write_log(char res[7]){
    time(&t);
    strcpy(lt,ctime(&t));
    
    char date[7];
    strncpy(date,lt+4,6);
    date[7] = '\0';

    char time[9];
    strncpy(time,lt+11,8);
    time[9] = '\0';

    write(fd,command,strlen(command));
    write(fd," ",1);
    write(fd,date,strlen(date));
    write(fd," ",1);
    write(fd,time,strlen(time));
    write(fd," ",1);
    write(fd,res,strlen(res));
    write(fd,"\n",1);
}

int runExtCommand(){
    int i,j,k,pos;
    int p[2];
    char **args;
    int cargs,temp,cnt,argNum;
    pipe(p);

    i=0;
    while(1){
        if(command[i] == '\0')
            break;

        k=i;
        cargs=0; temp=0; 
        while(command[i] != '|' && command[i] != '\0'){
            if(command[i] == ' ' && temp){
                cargs++; temp=0;
            }
            else if(command[i] != ' ')
                temp=1;
            i++;
        }
        if(temp)
            cargs++;

        temp = i;

        if(!cargs)
            return 0;
        
        args = (char**)malloc(cargs*sizeof(char*)+1);
        args[cargs] = NULL;
        i=k; argNum=0;
        while(i<temp){
            cnt=0;
            for(i=k;command[i]!=' ' && i<temp;i++) cnt++;
            args[argNum] = (char*)malloc(cnt*sizeof(char)+1);
            for(i=k,j=0;j<cnt;i++)
                if(command[i] != ' '){
                    args[argNum][j] = command[i];
                    j++;
                }
            args[argNum][j] = '\0';
            // printf("Part : %s\n",args[argNum]);
            argNum++;
            k=i+1;
        }

        if(k==0)
            pos = 1;
        else if(command[k-1] == '\0')
            pos = -1;
        else
            pos = 0;

        if(!fork()){
            if(pos==1){
                close(p[0]);
                dup2(p[1],1);    
            }
            else if(!pos){
                dup2(p[0],0);
                dup2(p[1],1);
            }
            else{
                dup2(p[0],0);
                close(p[1]);   
            }

            execvp(args[0],args);
            perror("Error ");
            exit(0);    //incase exec fails
        }

        for(j=0;j<argNum;j++)
            free(args[j]);
        free(args);

        wait(NULL);
        i=k;
        if(command[k-1] == '\0')
            break;
    }

    while(wait(NULL)!=-1);
    return 1;
}

void pro(){
    printf("Got %s\n",command);
    int child=0;
    int i,ret;

    if(!strcmp(command,"log")){
        logSwitch=1;
        fd = open("command.log",O_CREAT|O_RDWR, 0666);
    }
    else if(!strcmp(command,"unlog")){
        logSwitch=0;
        close(fd);
    }
    else if(!strcmp(command,"viewcmdlog"))
        printf("viewcmdlog not implemented \n");
    else if(!strcmp(command,"viewoutlog"))
        printf("viewoutlog not implemented \n");
    else if(!strncmp(command,"changedir",9))
        printf("changedir not implemented \n");
    else
        ret = runExtCommand();

    if(logSwitch){
        if(ret) write_log("failure");
        else write_log("success");
    }
    
}

int main(){
    struct tm* local;
    time_t tsec;
    char buf;    
    int ret;

    command[0] = '\0';
    len=0;

    while(read(0,&buf,1)>0){
        if(buf=='\n'){
            command[len] = '\0';
            len=0;
            if(!strcmp(command,"entry")) break;
            else printf("Command line interpreter not started, enter `entry` command.\n");
        }
        else{
            command[len] = buf;
            len++;
        }
    }

    printf("\nWelcome to Aditya's Shell \n");
    printf("************************ \n");

    logSwitch = 0;
    printf("\n>> ");
    fflush(stdout);

    while(read(0,&buf,1)>0){
        if(buf=='\n'){
            command[len] = '\0';
            if(!strcmp(command,"exit")) break;
            else pro();
            len=0; 
            printf("\n>> ");
            fflush(stdout);            
        }
        else{
            command[len] = buf;
            len++;
        }
    }

    if(logSwitch)
        close(fd);
    printf("Exiting.\n");
    return 0;
}