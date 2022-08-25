#include "./include/Sample.h"

//初始化互斥锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//初始化条件变量
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//全局变量i
int i = 0;

/**
 * @brief 使用互斥锁和条件变量实现线程间通信
 * @brief 找出100内能被3整除的数,并通知另外一个线程打印该数
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid1; //线程1的线程ID
    pthread_t tid2; //线程2的线程ID
    int ret1;       //线程创建结果
    int ret2;       //线程创建结果
    //创建线程1
    ret1 = pthread_create(&tid1, nullptr, threadFunction1, (void *)&NUMBER);
    if (ret1 != 0)
    {
        perror("pthread_create error");
        exit(0);
    }
    ret2 = pthread_create(&tid2, nullptr, threadFunction2, (void *)&NUMBER);
    if (ret2 != 0)
    {
        perror("pthread_create error");
        exit(0);
    }
    pthread_join(tid2, nullptr);   //等待tid2子线程执行完成
    pthread_mutex_destroy(&mutex); //销毁互斥锁
    pthread_cond_destroy(&cond);   //销毁条件变量
    cout << endl;
}

/**
 * @brief 线程1回调函数
 *
 * @param number 向线程传递的参数
 * @return void*
 */
void *threadFunction1(void *number)
{
    int num = *((int *)number);
    pthread_t tid;        //线程id
    tid = pthread_self(); //获取线程id
    for (i = 1; i < num; i++)
    {
        pthread_mutex_lock(&mutex); //互斥锁加锁
        if (i % 3 == 0)
        {
            pthread_cond_signal(&cond); //唤醒等待条件变量cond的线程
        }
        else
        {
            printf("Thread1:%d;tid:%ld\n", i, tid);
        }
        pthread_mutex_unlock(&mutex); //互斥锁解锁
        sleep(1);                     //休眠1秒
    }

    return nullptr;
}

/**
 * @brief 线程2回调函数
 *
 * @param number 向线程传递的参数
 * @return void*
 */
void *threadFunction2(void *number)
{
    int num = *((int *)number);
    pthread_t tid;        //线程id
    tid = pthread_self(); //获取线程id
    while (i < num)
    {
        pthread_mutex_lock(&mutex); //互斥锁加锁
        if (i % 3 != 0)
        {
            //该线程阻塞,释放互斥锁,接收并等待条件变量cond信号,收到条件变量信号后继续往下执行
            pthread_cond_wait(&cond, &mutex);
        }
        //打印能被3整初的数
        printf("Thread2:%d;tid:%ld\n", i, tid);
        pthread_mutex_unlock(&mutex); //互斥锁解锁
        sleep(1);                     //休眠1秒
        i++;
    }

    return nullptr;
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