#include "./include/Sample.h"

//全局变量,定义一个互斥锁
pthread_mutex_t mutex;

//共享属性
int cargoValue = 3000; //货物价值
int cash = 408;        //当前现金

/**
 * @brief 1. 店员卖货,老板对账
 * @brief 2. 使用互斥锁进行同步
 * @brief 3. 卖出一件货物收入50元
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t sellThreadId;   //卖货线程ID
    pthread_t verifyThreadId; //对账线程ID
    int ret;
    pthread_mutex_init(&mutex, nullptr);                                    //初始化互斥锁
    ret = pthread_create(&sellThreadId, nullptr, threadSellGoods, nullptr); //创建卖货线程
    if (ret != 0)
    {
        perror("create sell thread failed"); //打印错误日志
        exit(1);                             //结束进程
    }
    ret = pthread_create(&verifyThreadId, nullptr, threadReconciliation, nullptr); //创建对账线程
    if (ret != 0)
    {
        perror("create verify thread failed"); //打印错误日志
        exit(1);                               //结束进程
    }

    ret = pthread_join(sellThreadId, nullptr); //等待子线程执行结束
    if (ret != 0)
    {
        printf("等待卖货线程结束错误:%s\n", strerror(ret));
    }

    ret = pthread_join(verifyThreadId, nullptr); //等待子线程执行结束
    if (ret != 0)
    {
        printf("等待对账线程结束错误:%s\n", strerror(ret));
    }
    pthread_mutex_destroy(&mutex); //销毁互斥锁
    printf("主线程结束了,Thread ID:%ld\n", pthread_self());
    cout << endl;
}

/**
 * @brief 卖货线程
 *
 * @param para
 * @return void*
 */
void *threadSellGoods(void *para)
{
    pthread_t tid = pthread_self(); //获取线程ID
    printf("卖货线程开始执行了,Thread ID:%ld\n", tid);
    while (true)
    {
        pthread_mutex_lock(&mutex); //互斥锁上锁
        cargoValue -= 50;           //卖出价值50元的货物
        cash += 50;                 //现金收入50元
        printf("卖货后,现有现金:%d,货物价值:%d\n", cash, cargoValue);
        pthread_mutex_unlock(&mutex); //互斥锁解锁
        sleep(2);                     //阻塞1秒,释放CPU,以便其他线程执行
    }
}

/**
 * @brief 对账线程
 *
 * @param para
 * @return void*
 */
void *threadReconciliation(void *para)
{
    pthread_t tid = pthread_self();
    printf("对账线程开始执行了,Thread ID:%ld\n", tid);
    while (true)
    {
        pthread_mutex_lock(&mutex);            //互斥锁加锁
        int generalLedger = cash + cargoValue; //老板对一下总账,看看员工有没有私吞货款
        printf("总账为:%d\n", generalLedger);
        pthread_mutex_unlock(&mutex); //互斥锁释放锁
        sleep(3);                     //阻塞1秒,释放CPU,以便其他线程执行
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