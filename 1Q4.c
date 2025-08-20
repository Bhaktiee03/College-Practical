#include<stdio.h>
#include<sys/stat.h>

int main(int argc,char*argv[]){
if (argc<2){
printf("Usage:%s<file1><file2>...\n",argv[0]);
return 1;
}
struct stat file_stat;

for(int i=1;i<argc;i++){
if(stat(argv[i],&file_stat)==0){
printf("file:%sInode:%lu\n",argv[i],file_stat.st_ino);
}else{
perror(argv[i]);
}
}
return 0;
}
