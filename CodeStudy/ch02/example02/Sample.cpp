#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    //父子进程访问同一个文件
    std::string context = "welcome to shen zhen !!!"; //要写入的内容
    const char *pathName = "./file/f1.txt";
    int fd;         //文件描述符
    int number;     //读取的字节数
    pid_t pid;      //进程号
    char cache[30]; //缓冲区

    const char *buffer = context.c_str(); //缓冲区,字符串转换为字符数组
    int size = context.length();          //字符串的大小
    cout << "size:" << size << ",buffer:" << buffer << endl;

    fd = open(pathName, O_RDWR | O_TRUNC | O_CREAT, 644); //打开文件,不存在则创建,存在则覆盖
    if (fd == -1)
    {
        perror("open");
        cout << "打开文件" << pathName << ",失败 ..." << endl;
    }
    else
    {
        write(fd, buffer, size); //父进程写入文件
        lseek(fd, 0, SEEK_SET);  //从开始位置开始移动0个字节

        //创建子进程
        if ((pid = fork()) < 0)
        {
            perror("fork");
            cout << "创建子进程失败" << endl;
        }
        else if (pid == 0)
        {
            //先读10个字节
            number = read(fd, cache, 10);
            cache[number] = 0; //字符串结束标准
            cout << "子进程:" << getpid() << ",fd:" << fd << "," << cache << endl;
        }
        else
        {
            // wait();
            //再读剩下的10个字节
            number = read(fd, cache, 10);
            cache[number] = 0; //字符串结束标准
            cout << "父进程:" << getpid() << ",fd:" << fd << "," << cache << endl;
        }
    }
    close(fd); //关闭文件
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