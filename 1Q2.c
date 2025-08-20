#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[]="hello from parent process!";
    char read_msg[100];
    
    if(pipe(fd)==-1){
    perror("pipe");
    return 1;
    }
    pid=fork();
    if(pid<0){
    perror("fork");
    return 1;
    }
    if(pid==0){
    close(fd[1]);
    
    read(fd[0],read_msg,sizeof(read_msg));
    printf("child recevied:%s\n",read_msg);
    
    close(fd[0]);
    }else{
    
    close(fd[0]);
    
    write(fd[1],write_msg,strlen(write_msg)+1);
    
    close(fd[1]);
    wait(NULL);
    }
    return 0;
    }
    
     

