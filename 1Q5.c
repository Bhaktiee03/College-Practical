#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(){
int pipe1[2],pipe2[2];
char parent_msg[]="hellow from parent";
char child_msg[]="hellow from child";
char buffer[100];

pipe(pipe1);
pipe(pipe2);

if(fork()==0){
close(pipe1[1]);
close(pipe2[0]);

read(pipe1[0],buffer,sizeof(buffer));
printf("child received:%s\n",buffer);

write(pipe2[1],child_msg,strlen(child_msg)+1);

close(pipe1[0]);
close(pipe2[1]);
}else{

close(pipe1[0]);
close(pipe2[1]);

write(pipe1[1],child_msg,strlen(child_msg)+1);
read(pipe2[0],buffer,sizeof(buffer));
printf("parent received:%s\n",buffer);

close(pipe1[1]);
close(pipe2[0]);
wait(NULL);
}
return 0;
}
