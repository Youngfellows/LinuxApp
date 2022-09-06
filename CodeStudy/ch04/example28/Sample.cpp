#include "./include/Sample.h"

//全局变量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;     //静态初始化互斥锁
pthread_cond_t condProduce = PTHREAD_COND_INITIALIZER; //静态初始化条件变量
pthread_cond_t condConsume = PTHREAD_COND_INITIALIZER; //静态初始化条件变量
std::shared_ptr<list<Audio>> cacheAudio;               //缓冲区列表
int serialNum = 0;                                     //索引

/**
 * @brief 生产者,消费者模式
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    srand(time(nullptr)); //获取随机数的时间种子
    cacheAudio = std::make_shared<list<Audio>>();
    cout << "cacheAudio size " << cacheAudio->size() << endl;
    startProducer();
    startConsumer();
    pthread_exit(nullptr); //主线程退出,进程不结束
    cout << "主线程退出了,这句将不会执行 ..." << endl;
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

/**
 * @brief 启动生产者线程
 *
 */
void startProducer()
{
    cout << __FUNCTION__ << " ,启动生产者线程 ..." << endl;
    pthread_attr_t attr;                 //线程属性结构体
    pthread_t pThreads[THREAD_PRODUCER]; //生产者线程列表
    int ret;
    ret = pthread_attr_init(&attr); //初始化线程属性结构体
    if (ret)
    {
        handle_error_en(ret, "pthread_attr_init error");
    }
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //设置分离状态
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_attr_setdetachstate error");
    }

    for (int i = 0; i < THREAD_PRODUCER; i++)
    {
        ret = pthread_create(&pThreads[i], &attr, threadProducer, (void *)&i); //创建线程
        if (ret != 0)
        {
            handle_error_en(ret, "create producer thread failed");
        }
    }
}

/**
 * @brief 启动消费者线程
 *
 */
void startConsumer()
{
    cout << __FUNCTION__ << " ,启动消费者线程 ..." << endl;
    pthread_attr_t attr;                 //线程属性结构体
    pthread_t cThreads[THREAD_CONSUMER]; //生产者线程列表
    int ret;
    ret = pthread_attr_init(&attr); //初始化线程属性结构体
    if (ret)
    {
        handle_error_en(ret, "pthread_attr_init error");
    }
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //设置分离状态
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_attr_setdetachstate error");
    }

    for (int i = 0; i < THREAD_CONSUMER; i++)
    {
        ret = pthread_create(&cThreads[i], &attr, threadConsumer, (void *)&i); //创建线程
        if (ret != 0)
        {
            handle_error_en(ret, "create producer thread failed");
        }
    }
}

/**
 * @brief 生产者线程
 *
 * @param para 向线程传递的参数
 * @return void*
 */
void *threadProducer(void *para)
{
    int id = *((int *)para);        //获取主线程传递过来的参数
    pthread_t tid = pthread_self(); //获取子线程ID
    // cout << __FUNCTION__ << " ,采集音频,线程ID:" << id << ",索引:" << serialNum << endl;
    while (true)
    {
        pthread_mutex_lock(&mutex);           //互斥锁加锁
        if (cacheAudio->size() >= CACHE_SIZE) //如果缓冲区是满的,则等待消费者线程消费
        {
            cout << "容器已经满了,生产者线程等待消费者线程消费 ..." << endl;
            pthread_cond_wait(&condConsume, &mutex); //生产者线程释放锁,生产者线程阻塞,等待条件变量(消费者线程发送唤醒生产者线程的condConsume信号)
        }
        if (serialNum >= INT_MAX)
        {
            serialNum = 0;
        }
        serialNum++;
        Audio audio;
        audio.id = serialNum;
        audio.pcm = "音频数据" + to_string(serialNum);
        cacheAudio->push_back(audio);
        pthread_cond_signal(&condProduce); //生产者线程发送信号,消费者线程可以消费了
        pthread_mutex_unlock(&mutex);      //互斥锁释放锁

        int wait = rand() % 1000; //获取0 ~ 100的随机数
        // cout << "采集音频,线程ID:" << id << ",音频索引:" << audio.id << ",等待时间:" << wait << endl;
        usleep(wait);
    }

    pthread_exit((void *)0);
}

/**
 * @brief 消费者线程
 *
 * @param para 向线程传递的参数
 * @return void*
 */
void *threadConsumer(void *para)
{
    int id = *((int *)para);        //获取主线程传递过来的参数
    pthread_t tid = pthread_self(); //获取子线程ID
    // cout << __FUNCTION__ << " ,采集音频,线程ID:" << id << ",索引:" << serialNum << endl;
    while (true)
    {
        pthread_mutex_lock(&mutex);  //互斥锁加锁
        if (cacheAudio->size() == 0) //如果缓冲区是空的,则等待生产者线程产生数据
        {
            cout << "容器是空的,消费者线程等待生产者线程产生数据 ..." << endl;
            pthread_cond_wait(&condProduce, &mutex); //消费者线程释放锁,消费者线程阻塞,等待条件变量(生产者线程发送唤醒消费者线程的condProduce信号)
        }
        if (cacheAudio->size() > 0)
        {
            Audio audio = cacheAudio->front(); //获取第一个元素
            cacheAudio->pop_front();           //删除第一个元素
            cout << "获取到音频,线程ID:" << id << ",音频索引:" << audio.id << "," << audio.pcm << endl;
        }
        pthread_cond_signal(&condConsume); //消费者线程发送信号,生产者线程可以继续生产数据
        pthread_mutex_unlock(&mutex);      //互斥锁释放锁
        int wait = rand() % 1000;          //获取0 ~ 100的随机数
        usleep(wait);
    }
    return nullptr;
}