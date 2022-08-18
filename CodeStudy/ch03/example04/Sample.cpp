#include "./include/Sample.h"

/**
 * @brief 父子进程共享文件
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    const char *pathname = "./file/f1.txt"; //文件名
    pid_t pid;                              //进程PID
    int fd;                                 //文件描述符
    std::string content = "今天是周四,早上下雨,下午没有下哦 ...";
    int len = content.size();
    char buffer[len];                                      //缓冲区
    const char *contentBuff = content.c_str();             //缓冲区内容
    int nBytes;                                            //读文文件字节数
    fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0644); //创建并打开文件,如果存在则置空
    if (fd == -1)
    {
        perror("open error");
        // return;
        exit(1);
    }
    printf("进程创建前\n");
    pid = fork(); //创建子进程
    if (pid < 0)
    {
        perror("fork error");
        exit(1); //结束进程
    }
    else if (pid == 0)
    {
        //子进程,写文件,写完后退出子进程
        printf("子进程:%d\n", getpid());
        if ((nBytes = write(fd, contentBuff, len)) < 0)
        {
            perror("write failed");
        }
        exit(0); //结束进程
    }
    else
    {
        printf("父进程:%d\n", getpid());
        //父进程,读文件,要移动文件读写指针到开头
        sleep(1);               //休眠1秒
        lseek(fd, 0, SEEK_SET); //文件指针移动到文件开头
        if ((nBytes = read(fd, buffer, len)) < 0)
        {
            perror("read failed");
        }
        // buffer[nBytes] = '';
        //  printf("%s\n", buffer);
        write(1, buffer, nBytes); //向屏幕文件输出读取到的内容
        exit(1);                  //结束进程
    }
    printf("\n%d进程执行\n", getpid());
    cout << endl;
    exit(0); //结束进程
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