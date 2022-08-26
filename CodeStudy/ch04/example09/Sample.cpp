#include "./include/Sample.h"

/**
 * @brief 1. 创建一个简单的线程,不传递参数
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid;                                                 //线程ID
    int ret;                                                       //线程创建结果
    ret = pthread_create(&tid, nullptr, threadFunction1, nullptr); //创建线程
    if (ret != 0)
    {
        perror("pthread_create error");
        exit(0); //结束进程
    }
    pthread_join(tid, nullptr); //等待线程1执行结束
    cout << endl;
}

/**
 * @brief 2. 创建一个线程,向线程传递整数
 *
 */
void test2()
{
    cout << "test2():: ..." << endl;
    pthread_t tid;     //线程ID
    int ret;           //线程创建结果
    int number = 1024; //向线程传递的参数
    ret = pthread_create(&tid, nullptr, threadFunction2, (void *)&number);
    if (ret != 0)
    {
        perror("pthread_create error");
        exit(0); //退出进程
    }
    pthread_join(tid, nullptr); //等待子线程2结束
    cout << endl;
}

/**
 * @brief 3. 创建一个线程,向线程传递一个字符串
 *
 */
void test3()
{
    cout << "test3():: ..." << endl;
    pthread_t tid; //线程ID
    int ret;       //线程创建结果
    const char *message = "昨天台风,雨后的天空真的好美哦 ...\n";
    ret = pthread_create(&tid, nullptr, threadFunction3, (void *)message); //创建子线程
    if (ret != 0)
    {
        perror("pthread_create error");
        exit(0);
    }
    pthread_join(tid, nullptr); //等待子线程结束
    cout << endl;
}

/**
 * @brief 4. 创建一个线程,向线程传递结构体
 *
 */
void test4()
{
    cout << "test4():: ..." << endl;
    pthread_t tid;   //线程ID
    int ret;         //线程创建结果
    CarInfo carInfo; //车辆属性结构体
    carInfo.brand = "Jeep";
    carInfo.serialNumber = 1234567890;
    ret = pthread_create(&tid, nullptr, threadFunction4, (void *)&carInfo); //创建线程
    if (ret != 0)
    {
        perror("pthread_create error");
        exit(0); //结束进程
    }
    pthread_join(tid, nullptr); //等待子线程执行结束
    cout << endl;
}

/**
 * @brief 线程1回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction1(void *para)
{
    pthread_t tid = pthread_self(); //获取线程ID
    printf("开始,子线程1,执行了,线程ID:%ld\n", tid);
    sleep(3); //子线程1阻塞3秒
    printf("结束,子线程1,执行了,线程ID:%ld\n", tid);
    pthread_exit(0); //结束线程1
}

/**
 * @brief 线程2回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction2(void *para)
{
    pthread_t tid = pthread_self(); //获取线程id
    printf("子线程2,开始了,线程ID:%ld\n", tid);
    int number = *((int *)para); //获取传递过来的线程参数
    printf("子线程2,获取到整数:%d\n", number);
    sleep(2); //子线程休眠2秒,阻塞
    printf("子线程2,结束了,线程ID:%ld\n", tid);
    return (void *)0;
}

/**
 * @brief 线程3回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction3(void *para)
{
    pthread_t tid = pthread_self(); //获取线程id
    printf("子线程3,开始了,线程ID:%ld\n", tid);
    char *message = (char *)para; //获取传递过来的线程参数
    printf("子线程3,获取到字符串:%s\n", message);
    sleep(2); //子线程休眠2秒,阻塞
    printf("子线程3,结束了,线程ID:%ld\n", tid);
    // return nullptr;
    pthread_exit(0); //结束子线程
}

/**
 * @brief 线程4回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction4(void *para)
{
    pthread_t tid = pthread_self(); //获取线程id
    printf("子线程4,开始了,线程ID:%ld\n", tid);
    CarInfo *carInfo = (CarInfo *)para;            //获取传递过来的线程参数
    std::string brand = carInfo->brand;            //品牌
    long int serialNumber = carInfo->serialNumber; //序列号
    printf("子线程4,车的品牌:%s,序列号:%ld\n", brand.c_str(), serialNumber);
    sleep(2); //子线程休眠2秒,阻塞
    printf("子线程4,结束了,线程ID:%ld\n", tid);
    pthread_exit(0); //结束子线程
}