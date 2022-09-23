#include "./include/Sample.h"

/**
 * @brief 1. 创建共享内存,并将数据写入共享内存
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    const char *pathname = "./file/test.shm"; //共享内存文件
    int shmid;                                //共享内存ID
    key_t key;                                //键值
    void *shmptr;                             //共享内存地址
    const char *content = "通知,国庆放假七天,需要加班,大哭 ...";

    if (access(pathname, F_OK) == 0) //判断文件存在
    {
        printf("exists file:%s\n", pathname);
        // remove(pathname); //删除文件
        // unlink(pathname); //删除文件
        key = ftok(pathname, 1); //产生关键字
        if (key == -1)
        {
            perror("ftok failed");
            exit(1); //结束进程
        }
        shmid = shmget(key, SHMSIZE, SHM_R | SHM_W); //打开共享内存
        if (shmid == -1)
        {
            perror("shmget failed open");
            exit(1);
        }
        if (shmctl(shmid, IPC_RMID, NULL) == -1) //删除共享内存
        {
            perror("shmctl failed");
            exit(1);
        }
    }
    int fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0644); //创建并打开文件
    if (fd == -1)
    {
        perror("create file failed");
        exit(1);
    }
    key = ftok(pathname, 1); //产生关键字
    if (key == -1)
    {
        perror("ftok failed 2");
        exit(1); //结束进程
    }
    shmid = shmget(key, SHMSIZE, IPC_CREAT | IPC_EXCL | 0600); //创建或者打开共享内存
    if (shmid == -1)
    {
        perror("shamget failed");
        printf("errno:%d\n", errno);
        exit(1);
    }
    printf("shmid:%d\n", shmid);
    shmptr = shmat(shmid, NULL, 0); //共享内存映射到进程空间
    if (shmptr == (void *)-1)       //无效的地址空间
    {
        perror("shmat error");
        exit(1);
    }
    memcpy(shmptr, content, strlen(content)); //拷贝内容到内存空间,对共享内存空间操作
    if (shmdt(shmptr) == -1)                  //解除内存映射
    {
        perror("shmdt failed");
        exit(1);
    }
    cout << endl;
}

void test2()
{
    cout << "test2():: ..." << endl;
    cout << endl;
}

void test3()
{
    cout << "test3():: ..." << endl;
    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    cout << endl;
}