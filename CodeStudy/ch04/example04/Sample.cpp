#include "./include/Sample.h"

pthread_rwlock_t rwlock; //定义一个读写锁
int readerNum = 0;       //读
int writerNum = 0;       //写

/**
 * @brief 读写锁
 * @brief 允许多个reader同时读一个文件
 * @brief 当有一个reader在读文件时,不允许writer写文件
 * @brief 当有一个writer在写文件时,不允许reader读文件,也不允许其他writer写文件
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t readThread[THREAD_SIZE];  //读文件线程列表
    pthread_t writeThread[THREAD_SIZE]; //写文件线程列表
    int ids[THREAD_SIZE];               //编号列表
    int rret;                           //读文件线程创建结果
    int wret;                           //写文件线程创建结果
    pthread_rwlock_init(&rwlock, NULL); //动态初始化读写锁
    srand(time(NULL));                  //获取时间戳种子数
    //创建线程
    for (int i = 0; i < THREAD_SIZE; i++)
    {
        ids[i] = i; //为编号列表赋值
        rret = pthread_create(&readThread[i], NULL, reader, (void *)&ids[i]);
        if (rret != 0)
        {
            perror("pthread_create error");
            exit(0);
        }
        wret = pthread_create(&writeThread[i], NULL, writer, (void *)&ids[i]);
        if (wret != 0)
        {
            perror("pthread_create error");
            exit(0);
        }
    }

    //等待子线程结束
    for (int i = 0; i < THREAD_SIZE; i++)
    {
        pthread_join(readThread[i], NULL);
        pthread_join(writeThread[i], NULL);
    }
    pthread_exit(0); //主线程退出,线程不结束
    cout << endl;
}

/**
 * @brief 线程回调函数,读文件
 *
 * @param tid
 * @return void*
 */
void *reader(void *tid)
{
    randomSleep();
    pthread_rwlock_rdlock(&rwlock); //对读写锁加读锁
    readerNum++;
    readFile(*((int *)tid));
    readerNum--;
    pthread_rwlock_unlock(&rwlock); //对读写锁解锁
    return nullptr;
}

/**
 * @brief 线程回调函数,写文件
 *
 * @param tid
 * @return void*
 */
void *writer(void *tid)
{
    randomSleep();
    pthread_rwlock_wrlock(&rwlock); //对读写锁加写锁
    writerNum++;
    writeFile(*((int *)tid));
    writerNum--;
    pthread_rwlock_unlock(&rwlock); //对读写锁解锁
    return nullptr;
}

/**
 * @brief 读文件
 *
 * @param tid
 */
void readFile(int tid)
{
    printf("Reader ID:%d; Reader Num:%d; Writer Num:%d; Thread ID:%ld\n", tid, readerNum, writerNum, pthread_self());
    randomSleep();
}

/**
 * @brief 写文件
 *
 * @param tid
 */
void writeFile(int tid)
{
    printf("Writer ID:%d; Reader Num:%d; Writer Num:%d; Thread ID:%ld\n", tid, readerNum, writerNum, pthread_self());
    randomSleep();
}

/**
 * @brief 随机休眠
 *
 */
void randomSleep()
{
    struct timespec tv; //时间戳
    tv.tv_sec = 0;
    tv.tv_nsec = (long)(rand() * 1.0 / RAND_MAX * 999999999); //产生0~1秒的随机数
    nanosleep(&tv, NULL);                                     //休眠
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