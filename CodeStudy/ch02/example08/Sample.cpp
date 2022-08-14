#include "./include/Sample.h"

/**
 * @brief 读取目录中的目录项
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    DIR *dir;                   //指向目录文件的指针变量
    struct dirent *dent;        //存放目录项的结构体变量
    const char *pathname = "."; //当前目录
    dir = opendir(pathname);    //打开目录
    if (dir == nullptr)
    {
        //打开目录失败,显示相应的错误信息
        perror("open .");
        cout << "打开目录:" << pathname << ",失败 ..." << endl;
        return;
    }

    //循环读取目录项,置错误码为0来检测错误
    errno = 0;
    while ((dent = readdir(dir)) != nullptr)
    {
        long nodeNumber = dent->d_ino; //索引节点编号
        char *nodeName = dent->d_name; //目录项
        errno = 0;
        printf("索引节点编号:%ld,目录项:%s\n", nodeNumber, nodeName);
    }

    //如果报错
    if (errno != 0)
    {
        perror("read dir error");
    }

    //关闭目录
    closedir(dir);

    cout << endl;
}

/**
 * @brief 创建目录
 *
 */
void test2()
{
    cout << "test2():: ..." << endl;
    const char *pathname = "./file"; //目录名称
    const char *filename = "./file/f1.txt";
    int rt = mkdir(pathname, 0644); //创建目录
    int fd1;                        //文件描述符
    int fd2;                        //文件描述符
    std::string content = "今天周末,心情很好呀...";
    int count = content.size(); //字符长度
    if (rt == -1)
    {
        perror("mkdir error");
        cout << "创建目录失败:" << pathname << endl;
    }
    else
    {
        cout << "创建目录成功:" << pathname << endl;
        //在目录中创建文件,并写入数据            //文件名
        fd1 = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644); //文件不存在则创建,存在则置空
        if (fd1 == -1)
        {
            perror("open error");
            cout << "创建文件失败:" << filename << endl;
            return;
        }
        else
        {
            //向文件中写入数据
            const char *buffer = content.c_str();   //字符串转换为字符数组
            int number = write(fd1, buffer, count); //向文件中写入数据
            if (number < count)
            {
                printf("写入的字符%d少于%d\n", number, count);
            }
        }

        //读出文件中的内容
        fd2 = open(filename, O_RDONLY); //可读方式打开文件
        if (fd2 == -1)
        {
            perror("open error");
            cout << "打开文件失败:" << filename << endl;
            return;
        }

        char buff[count]; //缓冲区
        int number = 0;
        //循环读取文件数据
        while ((number = read(fd2, buff, count)) > 0)
        {
            //向屏幕文件写入读取的数据
            write(1, buff, number);
        }

        //关闭文件
        close(fd1);
        close(fd2);
    }

    cout << endl;
}

/**
 * @brief 删除目录
 *
 */
void test3()
{
    cout << "test3():: ..." << endl;
    const char *pathname = "./file"; //目录名称
    //删除一个不为空的目录
    int rt = rmdir(pathname);
    if (rt == -1)
    {
        perror("rmdir error");
        cout << "删除目录失败:" << pathname << endl;
    }
    else
    {
        cout << "删除目录成功:" << pathname << endl;
    }

    cout << endl;
}

/**
 * @brief 删除文件
 *
 */
void test4()
{
    cout << "test4():: ..." << endl;
    const char *pathname = "./file/f1.txt"; //目录名称
    //删除一个不为空的目录
    // int rt = rmdir(pathname);
    int rt = remove(pathname);
    if (rt == -1)
    {
        perror("rmdir error");
        cout << "删除目录失败:" << pathname << endl;
    }
    else
    {
        cout << "删除目录成功:" << pathname << endl;
    }
    cout << endl;
}

/**
 * @brief 删除目录
 *
 */
void test5()
{
    cout << "test5():: ..." << endl;
    const char *pathname = "./file"; //目录名称
    //删除一个不为空的目录
    int rt = rmdir(pathname);
    if (rt == -1)
    {
        perror("rmdir error");
        cout << "删除目录失败:" << pathname << endl;
    }
    else
    {
        cout << "删除目录成功:" << pathname << endl;
    }

    cout << endl;
}