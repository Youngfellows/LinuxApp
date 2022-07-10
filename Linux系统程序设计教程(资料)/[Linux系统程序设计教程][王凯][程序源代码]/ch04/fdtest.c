#include <fcntl.h>
main()
{
	int fd1,fd2,fd3;
 	fd1 = open("f1",O_RDWR);
	fd2 = open("f2",O_RDWR);
 	fd3 = open("f3",O_RDWR);
 	printf("fd1=%d\nfd2=%d\nfd3=%d\n",fd1,fd2,fd3);
 	close(fd1);
 	close(fd2);
 	close(fd3);
}
