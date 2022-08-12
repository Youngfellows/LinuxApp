#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    //获取系统文件属性
    const char *fileName = "/etc/passwd"; //文件名称
    struct stat buf;                      //属性信息结构体
    int rt;                               //获取文件属性结果

    rt = lstat(fileName, &buf); //获取文件属性
    if (rt == -1)
    {
        perror("lstat");
        cout << "获取" << fileName << ",文件属性失败 ..." << endl;
    }
    else
    {
        cout << "获取" << fileName << ",文件属性成功 ..." << endl;
        dev_t stDev = buf.st_dev;             //文件所在设备的设备ID
        ino_t stIno = buf.st_ino;             //索引节点编号
        nlink_t stNlink = buf.st_nlink;       //硬连接数
        uid_t stUid = buf.st_uid;             //文件所属用户的ID
        gid_t stGid = buf.st_gid;             //文件所属组的ID
        dev_t stRdev = buf.st_rdev;           //设备ID号
        off_t stSize = buf.st_size;           //文件总长度字节数
        blksize_t stBlksize = buf.st_blksize; //文件系统I/O块大小
        blkcnt_t stBlocks = buf.st_blocks;    //分配给文件的块数
        char *stAtime = ctime(&buf.st_atime); //文件的最后访问时间
        char *stMtime = ctime(&buf.st_mtime); //文件最后修改时间
        char *stCtime = ctime(&buf.st_ctime); //索引节点的最后修改时间
        cout << "stDev:" << stDev << endl;
        cout << "stIno:" << stIno << endl;
        cout << "stNlink:" << stNlink << endl;
        cout << "stUid:" << stUid << endl;
        cout << "stGid:" << stGid << endl;
        cout << "stRdev:" << stRdev << endl;
        cout << "stSize:" << stSize << endl;
        cout << "stBlksize:" << stBlksize << endl;
        cout << "stBlocks:" << stBlocks << endl;
        cout << "stAtime:" << stAtime << endl;
        cout << "stMtime:" << stMtime << endl;
        cout << "stCtime:" << stCtime << endl;

        // 1.判断文件类型
        if (S_ISREG(buf.st_mode))
        {
            cout << "常规文件" << endl;
        }
        else if (S_ISDIR(buf.st_mode))
        {
            cout << "目录文件" << endl;
        }
        else if (S_ISCHR(buf.st_mode))
        {
            cout << "字符设备文件" << endl;
        }
        else if (S_ISBLK(buf.st_mode))
        {
            cout << "块设备文件" << endl;
        }
        else if (S_ISFIFO(buf.st_mode))
        {
            cout << "FIFO文件" << endl;
        }
        else if (S_ISLNK(buf.st_mode))
        {
            cout << "符号链接文件" << endl;
        }
        // else if (S_ISSOCK(buf.st_mode))
        // {
        //     cout << "Socket文件" << endl;
        // }e
        else
        {
            cout << "未知类型文件" << endl;
        }

        // 2.判断文件类型
        switch (buf.st_mode & S_IFMT)
        {
        case S_IFDIR:
            cout << "目录文件" << endl;
            break;
        case S_IFLNK:
            cout << "符号链接文件" << endl;
            break;
        case S_IFREG:
            cout << "常规文件" << endl;
            break;
        case S_IFBLK:
            cout << "块设备文件" << endl;
            break;
        case S_IFCHR:
            cout << "字符设备文件" << endl;
            break;
        case S_IFSOCK:
            cout << "Socket文件" << endl;
            break;
        case S_IFIFO:
            cout << "FIFO文件" << endl;
            break;
        default:
            cout << "未知类型文件" << endl;
        }

        //判断文件权限
        //用户权限
        if (buf.st_mode & S_IRUSR)
        {
            cout << "用户可读" << endl;
        }
        else
        {
            cout << "用户不可读" << endl;
        }

        if (buf.st_mode & S_IWUSR)
        {
            cout << "用户可写" << endl;
        }
        else
        {
            cout << "用户不可写" << endl;
        }

        if (buf.st_mode & S_IXUSR)
        {
            cout << "用户可执行" << endl;
        }
        else
        {
            cout << "用户不可执行" << endl;
        }

        //所属组权限
        if (buf.st_mode & S_IRGRP)
        {
            cout << "所属组可读" << endl;
        }
        else
        {
            cout << "所属组不可读" << endl;
        }

        if (buf.st_mode & S_IWGRP)
        {
            cout << "所属组可写" << endl;
        }
        else
        {
            cout << "所属组不可写" << endl;
        }

        if (buf.st_mode & S_IXGRP)
        {
            cout << "所属组可执行" << endl;
        }
        else
        {
            cout << "所属组不可执行" << endl;
        }

        //其他成员权限
        if (buf.st_mode & S_IROTH)
        {
            cout << "其他成员可读" << endl;
        }
        else
        {
            cout << "其他成员不可读" << endl;
        }

        if (buf.st_mode & S_IWOTH)
        {
            cout << "其他成员可写" << endl;
        }
        else
        {
            cout << "其他成员不可写" << endl;
        }

        if (buf.st_mode & S_IXOTH)
        {
            cout << "其他成员可执行" << endl;
        }
        else
        {
            cout << "其他成员不可执行" << endl;
        }
    }

    cout << endl;
}

void test2()
{
    cout << "test2():: ..." << endl;
    //获取用户信息
    const char *fileName = "/etc/passwd"; //文件名
    struct stat buf;                      //系统文件属性
    int rt = lstat(fileName, &buf);       //获取系统文件属性
    struct passwd *user = nullptr;        //文件用户信息
    if (rt == -1)
    {
        perror("lstat error");
        cout << "获取文件:" << fileName << ",系统文件属性错误 ..." << endl;
    }
    else
    {
        cout << "获取文件:" << fileName << ",系统文件属性成功 ..." << endl;
        user = getpwuid(buf.st_uid);     //获取文件用户信息
        char *uName = user->pw_name;     //用户名
        char *uPasswd = user->pw_passwd; //用户密码
        uid_t uUid = user->pw_uid;       //用户ID
        gid_t gid = user->pw_gid;        //组ID
        char *uGecos = user->pw_gecos;   //备注信息
        char *mainDir = user->pw_dir;    //主目录
        char *shell = user->pw_shell;    // Shell
        cout << "uName:" << uName << endl;
        cout << "uPasswd:" << uPasswd << endl;
        cout << "uUid:" << uUid << endl;
        cout << "gid:" << gid << endl;
        cout << "uGecos:" << uGecos << endl;
        cout << "mainDir:" << mainDir << endl;
        cout << "shell:" << shell << endl;
    }
    cout << endl;
}

void test3()
{
    cout << "test3():: ..." << endl;
    //获取所属组信息
    const char *fileName = "/etc/passwd"; //文件名
    struct stat buf;                      //系统文件属性
    struct group *grp;                    //所属组信息
    int rt = lstat(fileName, &buf);       //获取系统文件属性
    if (rt == -1)
    {
        perror("lstat error");
        cout << "获取" << fileName << ",文件系统属性失败 ..." << endl;
    }
    else
    {
        grp = getgrgid(buf.st_gid);      //获取所属组信息
        char *grName = grp->gr_name;     //组名
        char *grPasswd = grp->gr_passwd; //组密码
        gid_t gid = grp->gr_gid;         //组ID
        char **grMem = grp->gr_mem;      //组成员
        cout << "grName:" << grName << endl;
        cout << "grPasswd:" << grPasswd << endl;
        cout << "gid:" << gid << endl;
        cout << "grMem:" << grMem << endl;
        if (*grMem)
        {
            cout << "*grMem:" << **grMem << endl;
        }
        else
        {
            cout << "组成员为空 ..." << endl;
        }
        while (*grMem != nullptr)
        {
            cout << "组成员:" << **grMem << endl;
            grMem++;
        }
    }
    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    //创建一个硬连接文件
    const char *from = "./file/f1.txt"; //已经存在的文件
    const char *to = "./file/f2.txt";   //硬链接文件
    int rt = link(from, to);            //创建一个硬连接文件
    if (rt == -1)
    {
        perror("link error");
        cout << "创建硬连接文件失败 ..." << endl;
    }
    else
    {
        cout << "创建硬连接文件成功:" << to << endl;
    }

    cout << endl;
}

void test5()
{
    cout << "test5():: ..." << endl;
    //创建一个硬连接文件,删除改文件
    const char *from = "./file/f1.txt"; //已经存在的文件
    const char *to = "./file/f3.txt";   //硬链接文件
    int rt = link(from, to);            //创建一个硬连接文件
    if (rt == -1)
    {
        perror("link error");
        cout << "创建硬连接文件失败 ..." << endl;
    }
    else
    {
        cout << "创建硬连接文件成功:" << to << endl;
        //读取硬链接文件
        int fd = open(to, O_RDONLY); //打开文件
        if (fd == -1)
        {
            perror("open error");
            cout << "打开文件失败:" << to << endl;
        }
        else
        {
            char buffer[100]; //缓冲区
            int number;       //读取到的字节数
            while ((number = read(fd, buffer, sizeof(buffer))))
            {
                write(1, buffer, number); //向屏幕输入读取到的内容
            }
            close(fd); //关闭文件
        }
    }
    cout << endl;
}

void test6()
{
    cout << "test6():: ..." << endl;
    //创建一个硬连接文件,删除改文件
    const char *pathName = "./file/f3.txt"; //硬链接文件
    int rt = unlink(pathName);              //删除硬连接文件
    if (rt == -1)
    {
        perror("unlink error");
        cout << "删除硬连接文件错误:" << pathName << endl;
    }
    else
    {
        cout << "删除硬连接文件成功:" << pathName << endl;
    }
    cout << endl;
}

void test7()
{
    cout << "test7():: ..." << endl;
    //指针与二维数组
    char *elements[] = {"C++", "Java", "Kotlin", "C", "Python"}; //二维数组
    char **programs = elements;                                  //指针指向二维数组元素

    // 1.打印二维数组元素
    for (int i = 0; i < 5; i++)
    {
        char *program = elements[i];
        cout << program << endl;
    }

    cout << "=======================" << endl;

    // 2.打印二维数组元素
    for (int i = 0; i < 5; i++)
    {
        char *program = *(programs + i); //获取二维数组元素
        cout << program << endl;
    }
    cout << endl;
}

void test8()
{
    cout << "test8():: ..." << endl;
    //创建符号链接文件
    const char *actualpath = "./file/f2.txt"; //真实存在的文件
    const char *sympath = "./file/f3";        //符号链接文件
    int rt = symlink(actualpath, sympath);    //创建符号链接文件
    if (rt == -1)
    {
        perror("symlink error");
        cout << "创建符号链接文件失败:" << sympath << endl;
    }
    else
    {
        //读取符号链接所指原文件名
        char buffer[100]; //保存文件名缓冲区
        rt = readlink(sympath, buffer, sizeof(buffer));
        if (rt == -1)
        {
            perror("readlink error");
            cout << "读取符号链接所指原文件名错误 ..." << endl;
        }
        else
        {
            buffer[rt] = 0;
            cout << "读取原文件名成功:" << buffer << endl;
            char cache[1024];                //文件内容缓冲区
            int fd = open(buffer, O_RDONLY); //打开文件
            if (fd == -1)
            {
                perror("open error");
                cout << "打开文件失败:" << buffer << endl;
            }
            else
            {
                //读取原文件内容
                int number = 0;
                while ((number = read(fd, cache, sizeof(cache))) > 0)
                {
                    write(1, cache, number); //向屏幕输出读取的内容
                }
                close(fd); //关闭文件
            }
        }
    }

    cout << endl;
}

/**
 * @brief 对指定的文件描述符进行复制
 * @brief 共享文件指针
 */
void test9()
{
    cout << "test9():: ..." << endl;
    const char *pathName = "./file/f4.txt";                 //文件名
    int fd1;                                                //文件描述符
    int fd2;                                                //文件描述符
    int fd3;                                                //复制后的文件描述符
    fd1 = open(pathName, O_RDWR | O_CREAT | O_TRUNC, 0644); //打开文件,如果存在则置空文件内容
    if (fd1 == -1)
    {
        perror("open fd1 error");
        cout << "打开文件失败:" << pathName << endl;
        return;
    }
    cout << "fd1=" << fd1 << endl;
    fd2 = open(pathName, O_RDWR); //再次打开文件,可读可写
    if (fd2 == -1)
    {
        perror("open fd2 error");
        cout << "打开文件失败:" << pathName << endl;
        return;
    }
    cout << "fd2=" << fd2 << endl;
    //复制文件描述符,通fd1共享文件指针
    fd3 = dup(fd1);
    if (fd3 == -1)
    {
        perror("dump error");
        cout << "复制文件描述符fd1:" << fd1 << ",失败 ..." << endl;
        return;
    }
    cout << "fd3=" << fd3 << endl;

    //向fd1中写入文件,写入后,文件指针在最后
    std::string content = "今天周五,好开心,马上周末啦...";
    int length = content.size();
    const char *buffer = content.c_str();    //字符串转化为字符数组
    int number = write(fd1, buffer, length); //向文件写入内容
    cout << "写入" << number << "个字节数据到文件:" << pathName << endl;

    //读出fd2的数据
    int size = length + 100;
    char *cache = new char[size];    //动态申请内存
    number = read(fd2, cache, size); //读取fd2文件描述符指向文件的数据
    cache[number] = 0;
    cout << "读取到fd2文件描述符数据," << number << "个字节数据:" << cache << endl;

    //读取fd3文件描述符指向文件的数据,什么也读不到,因为fd1写入数据后,文件指针已经到最后啦
    number = read(fd3, cache, size);
    cache[number] = 0;
    cout << "读取到fd3文件描述符数据," << number << "个字节数据:" << cache << endl;

    lseek(fd3, 10, SEEK_SET); //移动文件指针到文件开头位置10个字节处
    number = read(fd3, cache, size);
    cache[number] = 0;
    cout << "读取到fd3文件描述符数据," << number << "个字节数据:" << cache << endl;

    //释放内存
    delete[] cache;

    //关闭文件
    close(fd1);
    close(fd2);
    close(fd3);
    cout << endl;
}

/**
 * @brief 输出重定向
 *
 */
void test10()
{
    cout << "test10():: ..." << endl;
    const char *pathname = "./file/f5.txt";                      //文件名
    int fd1 = open(pathname, O_RDWR | O_CREAT | O_APPEND, 0644); //创建并打开一个文件,以追加方式写入数据
    if (fd1 == -1)
    {
        perror("open error");
        cout << "打开文件失败:" << pathname << endl;
        return;
    }
    cout << "fd1=" << fd1 << endl;
    // close(1);           //关闭标准输出文件1,会报错
    int fd2 = dup(fd1); //文件描述符1成为最小可用文件描述符,因此把标准输出都重定向到文件描述符fd1对应的文件中
    cout << "fd2=" << fd2 << endl;

    //输出重定向
    printf("哈哈,今天下雨哦,下班记得带雨伞 ...");

    //关闭文件
    close(fd1);
    close(fd2);
    cout << endl;
}

/**
 * @brief 输入重定向
 *
 */
void test11()
{
    cout << "test11():: ..." << endl;
    const char *pathname = "./file/f5.txt"; //文件名
    int fd1 = open(pathname, O_RDWR, 0644); //创建并打开一个文件,以追加方式写入数据
    if (fd1 == -1)
    {
        perror("open error");
        cout << "打开文件失败:" << pathname << endl;
        return;
    }
    cout << "fd1=" << fd1 << endl;
    close(0);           //关闭标准输出文件1,会报错
    int fd2 = dup(fd1); //文件描述符1成为最小可用文件描述符,因此把标准输出都重定向到文件描述符fd1对应的文件中
    // cout << "fd2=" << fd2 << endl;

    //输出重定向
    // printf("哈哈,今天下雨哦,下班记得带雨伞2 ...");
    char buffer[100];
    scanf("%s", buffer);
    printf("%s", buffer);

    //关闭文件
    close(fd1);
    close(fd2);
    cout << endl;
}

void test12()
{
    cout << "test12():: ..." << endl;
    cout << endl;
}

void test13()
{
    cout << "test13():: ..." << endl;
    cout << endl;
}

void test14()
{
    cout << "test14():: ..." << endl;
    cout << endl;
}

void test15()
{
    cout << "test15():: ..." << endl;
    cout << endl;
}

void test16()
{
    cout << "test16():: ..." << endl;
    cout << endl;
}
void test17()
{
    cout << "test17():: ..." << endl;
    cout << endl;
}

void test18()
{
    cout << "test18():: ..." << endl;
    cout << endl;
}

void test19()
{
    cout << "test19():: ..." << endl;
    cout << endl;
}
void test20()
{
    cout << "test20():: ..." << endl;
    cout << endl;
}

void test21()
{
    cout << "test21():: ..." << endl;
    cout << endl;
}
