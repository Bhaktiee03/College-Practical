#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>


int main(){
int fd=open("file_with_hole.txt",O_CREAT|O_WRONLY,0644);

if(fd<0){
perror("open");
return 1;
}
write(fd,"Start",5);
lseek(fd,1024,SEEK_CUR);
write(fd,"End",3);
close(fd);
printf("file'file_with_hole.txt' create with hole.\n");
return 0;
}

