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
            cout << "*grMem:" << *grMem << endl;
        }
        else
        {
            cout << "组成员为空 ..." << endl;
        }
        while (*grMem != nullptr)
        {
            cout << "组成员:" << *grMem << endl;
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
    cout << endl;
}

void test8()
{
    cout << "test8():: ..." << endl;
    cout << endl;
}

void test9()
{
    cout << "test9():: ..." << endl;
    cout << endl;
}
void test10()
{
    cout << "test10():: ..." << endl;
    cout << endl;
}

void test11()
{
    cout << "test11():: ..." << endl;
    cout << endl;
}

void test12()
{
    cout << "test12():: ..." << endl;
    cout << endl;
}