#include "./include/Sample.h"

//全局变量
sem_t mMutex;            //互斥信号量
sem_t mEmpty;            //容器是空的信号量
sem_t mFull;             //容器是满的信号量
int mBuffer[BUFFERSIZE]; //容器
int mIn;                 //生产数据
int mOut;                //消费数据
int mProduction = 0;     //生产的数据
int mConsume = 0;        //消费的数据

/**
 * @brief 利用信号量实现生产者,消费者模型
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    initSems();
    pthread_t producerThread[5]; //生产者线程
    pthread_t consumerThread[3]; //消费者线程

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&producerThread[i], nullptr, producerFunction, (void *)&i);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&consumerThread[i], nullptr, consumerFunction, (void *)&i);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(producerThread[i], nullptr);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(consumerThread[i], nullptr);
    }

    destroySems();
    cout << endl;
}

/**
 * @brief 初始化信号量
 *
 */
void initSems()
{
    sem_init(&mMutex, 0, 1);  //初始化互斥信号量初始值为1
    sem_init(&mEmpty, 0, 50); //容器是空的信号量,初始值为50
    sem_init(&mFull, 0, 0);   //容器是满的信号量,初始值为0
}

/**
 * @brief 销毁信号量
 *
 */
void destroySems()
{
    sem_destroy(&mMutex);
    sem_destroy(&mEmpty);
    sem_destroy(&mFull);
}

/**
 * @brief 线程回调函数
 * @brief 生产者线程
 * @param arg
 * @return void*
 */
void *producerFunction(void *arg)
{
    printf("生产者线程ID:%ld,Thread ID:%d\n", pthread_self(), *((int *)arg));
    while (true)
    {
        sem_wait(&mEmpty); //获取到锁,并且mEmpty的值减1,如果mEmpty为0,则阻塞
        sem_wait(&mMutex); //获取到锁,并且mMutex的值减1,如果mEmpty为0,则阻塞
        printf("生产者线程ID:%ld,Thread ID:%d,mProduction:%d\n", pthread_self(), *((int *)arg), mProduction);
        mBuffer[mIn % BUFFERSIZE] = mProduction;
        mProduction++;
        mIn++;
        sem_post(&mMutex); // mMutex值增加1
        sem_post(&mFull);  // mFull值增加1
        sleep(1);          //休眠1秒
    }
}

/**
 * @brief 线程回调函数
 * @brief 消费者线程
 * @param arg
 * @return void*
 */
void *consumerFunction(void *arg)
{
    printf("消费者线程ID:%ld,Thread ID:%d\n", pthread_self(), *((int *)arg));
    while (true)
    {
        sem_wait(&mFull);  //获取到锁,并且mFull的值减1,如果mFull为0,则阻塞
        sem_wait(&mMutex); //获取到锁,并且mMutex的值减1,如果mEmpty为0,则阻塞
        mConsume = mBuffer[mOut % BUFFERSIZE];
        printf("消费者线程ID:%ld,Thread ID:%d,mConsume:%d\n", pthread_self(), *((int *)arg), mConsume);
        mOut++;
        sem_post(&mMutex); // mMutex值增加1
        sem_post(&mEmpty); // mEmpty值增加1
    }
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