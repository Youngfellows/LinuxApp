#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
main()
{
	int fd1,fd2,fd3;
	int num;
	char buf[20];
	fd1 = open("f1",O_RDWR|O_TRUNC);
	if(fd1==-1)
	{
		perror("open");
		exit(1);
	}
	printf("fd1 is %d \n",fd1);
	fd2 = open("f1",O_RDWR);
	if(fd2==-1)
	{
		perror("open");
		exit(1);
	}
	printf("fd2 is %d \n",fd2);
	fd3=dup(fd1);
	printf("fd3 is %d \n",fd3);
	num=write(fd1,"hello world!",12);
	printf("fd1:write num=%d bytes into f1\n",num);
	num=read(fd2, buf,20);
	buf[num]=0;
	printf("fd2:read  %d bytes from f1: %s\n",num, buf);
	num=read(fd3, buf,20);
	buf[num]=0;
	printf("fd3:read  %d bytes from f1: %s\n",num, buf);
	close(fd1);
	close(fd2);
	close(fd3);
}
/*
[root@bogon 5]# ./fileopenone2 
fd1 is 3 
fd2 is 4 
write num=12 bytes into f1 through fd1
read  12 bytes from f1: hello world! through fd2

*/

/*

 [root@bogon 5]# gcc fileopenone2.c -o fileopenone2
[root@bogon 5]# ./fileopenone2 
fd1 is 3 
fd2 is 4 
fd3 is 5 
fd1:write num=12 bytes into f1
fd2:read  12 bytes from f1: hello world!
fd3:read  0 bytes from f1: 
[root@bogon 5]# 

*/

