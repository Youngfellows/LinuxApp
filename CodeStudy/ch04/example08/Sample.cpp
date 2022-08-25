#include "./include/Sample.h"

//定义一个全局变量key
pthread_key_t key;

/**
 * @brief 线程私有数据
 *
 */
void test1()
{
    cout << "test1():: Start ..." << endl;
    pthread_t tid;                                                 //线程ID
    int ret;                                                       //线程创建结果
    pthread_key_create(&key, nullptr);                             //创建键值
    ret = pthread_create(&tid, nullptr, threadFunction1, nullptr); //创建线程
    if (ret != 0)
    {
        perror("pthread_create error");
        exit(0);
    }
    pthread_join(tid, nullptr); //等待线程1结束
    pthread_key_delete(key);    //删除键值
    cout << "test1():: End ..." << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数1
 *
 * @param para
 * @return void*
 */
void *threadFunction1(void *para)
{
    int number = 5;                 //线程私有数据
    pthread_t tid = pthread_self(); //获取线程ID
    printf("线程1运行了,线程ID:%ld\n", tid);
    pthread_setspecific(key, (void *)&number);                          //设置线程私有数据
    pthread_t tid2;                                                     //线程ID
    int ret = pthread_create(&tid2, nullptr, threadFunction2, nullptr); //创建线程2
    if (ret != 0)
    {
        perror("pthread_create error");
        exit(0);
    }
    // sleep(3);
    pthread_join(tid2, nullptr); //等待线程2执行结束
    printf("获取线程1的私有数据,number:%d\n", *((int *)pthread_getspecific(key)));
    pthread_exit(0); //结束线程
}

/**
 * @brief 线程回调函数2
 *
 * @param para
 * @return void*
 */
void *threadFunction2(void *para)
{
    int number = 10;                //线程私有数据
    pthread_t tid = pthread_self(); //获取线程ID
    printf("线程2运行了,线程ID:%ld\n", tid);
    pthread_setspecific(key, (void *)&number); //设置线程私有数据
    sleep(1);                                  //阻塞1秒
    printf("获取线程2的私有数据,number:%d\n", *((int *)pthread_getspecific(key)));
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