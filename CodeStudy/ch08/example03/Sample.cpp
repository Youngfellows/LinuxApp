#include "./include/Sample.h"

/**
 * @brief 信号量举例
 *
 */
int test1(int argc, char **argv)
{
    cout << "test1():: ..." << endl;
    key_t key;           //键值
    int semid;           //信号量ID
    int ret;             //结果
    int flag;            //标记
    union semun arg;     // semctl第4个参数,表示信号量
    struct sembuf semop; //信号量操作
    const char *pathname = "./tmp/sem";

    //判断参数个数
    if (argc > 2 || (argc == 2 && strcmp("del", argv[1]) != 0))
    {
        printf("使用:%s\n", argv[0]);
        printf("使用:%s del\n", argv[0]);
        return -1;
    }
    key = ftok(pathname, 0x66); //获取键值
    if (key < 0)
    {
        perror("ftok key error");
        return -1;
    }

    semid = semget(key, 3, IPC_CREAT | 0600); //创建或者打开3个信号量
    printf("semid:%d\n", semid);
    if (semid == -1)
    {
        perror("create semget error");
        return -1;
    }

    if (argc == 2) //删除信号量集
    {
        if (strcmp("del", argv[1]) == 0)
        {
            ret = semctl(semid, 0, IPC_RMID); //删除信号量集
            if (ret == -1)
            {
                perror("semctl rm error");
                return -1;
            }
            else
            {
                printf("信号量%d已经删除了\n", semid);
            }
        }
    }
    else if (argc == 1)
    {
        //对0信号量设置初始值
        arg.val = 1;
        ret = semctl(semid, 0, SETVAL, 1);
        if (ret < 0)
        {
            perror("ctl sem error");
            ret = semctl(semid, 0, IPC_RMID); //删除信号量集
            if (ret == -1)
            {
                perror("semctl delete error");
            }
            else
            {
                printf("信号量%d已经删除了\n", semid);
                return -1;
            }
        }

        //取0号信号量的值
        ret = semctl(semid, 0, GETVAL, arg);
        printf("设置之前的值: sem[0].val=[%d]\n", ret);
        system("date");

        printf("P操作开始\n");
        flag = P(semid, 0);
        if (flag)
        {
            perror("P operate error");
            return -1;
        }
        printf("P操作结束\n");
        ret = semctl(semid, 0, GETVAL, arg);
        printf("P操作结束的值: sem[0].val=[%d]\n", ret);
        system("date");

        printf("休眠10秒后\n");
        sleep(10);

        printf("V操作开始\n");
        flag = V(semid, 0);
        if (flag < 0)
        {
            perror("V operate error");
            return -1;
        }
        printf("V操作结束\n");
        ret = semctl(semid, 0, GETVAL, arg);
        printf("V操作结束的值: sem[0].val=[%d]\n", ret);
        system("date");
    }

    cout << endl;
}

int P(int semid, int semnum)
{
    struct sembuf sops = {semnum, -1, SEM_UNDO};
    return (semop(semid, &sops, 1));
}

int V(int semid, int semnum)
{
    struct sembuf sops = {semnum, 1, SEM_UNDO};
    return (semop(semid, &sops, 1));
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