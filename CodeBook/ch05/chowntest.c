#include <sys/stat.h>
main()
{
	struct stat buf;
	
	unlink("f1");
	system("touch f1");

	stat("f1",&buf);
	printf("old userid:%d  grpid:%d\n",buf.st_uid,buf.st_gid);

	chown("f1",-1,502);
	stat("f1",&buf);

	printf("new userid:%d  grpid:%d\n",buf.st_uid,buf.st_gid);
}
