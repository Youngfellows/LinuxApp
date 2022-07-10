#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
main()
{
    	pid_t id;

    	id=fork();
	if(id<0)
        {
        	perror("fork");
        	exit(1);
        }
       else if(id==0)
       {  printf("I am child, my pid=  %d\n",getpid());  }
       else
       {  printf("I am parent, my pid=  %d\n",getpid());  }
       printf("%d print this sentence\n",getpid());
}

/*
[root@bogon 7]# gcc fork1.c -o fork1
[root@bogon 7]# ./fork1 

[root@bogon 7]# ./fork1 
I am child, my pid=  8704
8704 print this sentence
I am parent, my pid=  8703
8703 print this sentence

*/
