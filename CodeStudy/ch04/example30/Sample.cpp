#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t id1;
    pthread_t id2;

    pid_t pid = getpid();
    pid_t tid = syscall(SYS_gettid);

    printf("main thread : pid = %d , tid = %d \n", pid, tid);
    pthread_create(&id1, NULL, thread_function1, NULL);
    pthread_create(&id2, NULL, thread_function, NULL);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    cout << endl;
}

void *thread_function1(void *arg)
{
    const pid_t tid = syscall(SYS_gettid);

    int ret = setpriority(PRIO_PROCESS, tid, -10);
    printf("tid of high priority thread %d , %d\n", tid, getpriority(PRIO_PROCESS, tid));
    while (1)
    {
        printf("high priority ................\n");
    }
}

void *thread_function(void *arg)
{
    const pid_t tid = syscall(SYS_gettid);
    int ret = setpriority(PRIO_PROCESS, tid, 10);
    printf("tid of low priority thread %d , %d \n", tid, getpriority(PRIO_PROCESS, tid));
    while (1)
    {
        printf("lower priority\n");
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