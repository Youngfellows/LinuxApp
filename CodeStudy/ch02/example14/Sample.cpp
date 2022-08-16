#include "./include/Sample.h"

/**
 * @brief 创建符号连接文件
 * @brief
 *
 * @param argc
 * @param argv
 */
void test1()
{
    cout << "test1():: ..." << endl;
    const char *actualpath = "./file1/f1.txt"; //真实的文件夹
    const char *sympath1 = "./file1/f1_link1"; //符号连接文件1
    const char *sympath2 = "./file1/f1_link2"; //符号连接文件1
    int rt = symlink(actualpath, sympath1);    //创建符号连接文件1
    if (rt == -1)
    {
        perror("symlink sympath1 error");
    }
    rt = symlink(actualpath, sympath2); //创建符号连接文件1
    if (rt == -1)
    {
        perror("symlink sympath2 error");
    }
    cout << endl;
}

/**
 * @brief 拷贝目录到目录
 * @brief cp 目录 目录
 * @brief 使用: ./obj/test_sample.out ./file1 ./file2
 *
 * @param argc
 * @param argv
 */
void test2(int argc, char *argv[])
{
    cout << "test2():: ..." << endl;
    if (argc != 3)
    {
        printf("使用:%s 目录 目录\n", argv[0]);
        return;
    }
    char *fromDirName = argv[1]; //源目录
    char *toDirName = argv[2];   //目标目录
    copyDir(fromDirName, toDirName);
    cout << endl;
}

/**
 * @brief 拷贝符号连接文件
 *
 * @param fromPathName 源文件文件名称
 * @param toPathName 目标文件文件名称
 * @return int 成功返回0,失败返回1
 */
int copyLinkFile(char *fromPathName, char *toPathName)
{
    char buffer[1024];                                           //缓冲区
    bzero(buffer, sizeof(buffer));                               //清空缓冲区
    int number = readlink(fromPathName, buffer, sizeof(buffer)); //读取符号连接所指的原文件名,真实的文件
    if (number != 0)
    {
        symlink(buffer, toPathName); //创建一个符号连接文件
    }
    return 0;
}

/**
 * @brief 拷贝常规文件
 *
 * @param fromPathName 源文件文件名称
 * @param toPathName 目标文件文件名称
 * @return int 成功返回0,失败返回1
 */
int copyRegularFile(char *fromPathName, char *toPathName)
{
    int fromfd;                            //源文件文件描述符
    int tofd;                              //目标文件文件描述符
    fromfd = open(fromPathName, O_RDONLY); //打开源文件
    if (fromfd == -1)
    {
        perror("open fromfd error");
        return 1;
    }
    tofd = open(toPathName, O_RDWR | O_CREAT | O_TRUNC, 0666); //创建并打开文件,如果存在则置空
    if (tofd == -1)
    {
        perror("open tofd error");
        return 1;
    }
    char buffer[100];                                           //缓冲区
    int number;                                                 //读取到字节数
    bzero(buffer, sizeof(buffer));                              //清空缓冲区
    while ((number = read(fromfd, buffer, sizeof(buffer) - 1))) //循环读取文件内容
    {
        int wNum = write(tofd, buffer, number); //拷贝到文件中
        if (wNum < number)
        {
            wNum += write(tofd, buffer + wNum, number - wNum); //循环写入剩下的
        }
        bzero(buffer, sizeof(buffer)); //清空缓冲区
    }
    close(fromfd); //关闭文件
    close(tofd);   //关闭文件

    struct stat info; //系统文件属性
    int rt = lstat(fromPathName, &info);
    if (rt == -1)
    {
        perror("lstat error");
        return 1;
    }
    rt = chmod(toPathName, info.st_mode); //改变文件访问权限
    if (rt == -1)
    {
        perror("chmod error");
        return 1;
    }
    return 0;
}

/**
 * @brief 拷贝目录到指定目录
 *
 * @param fromDirName 源目录
 * @param toDirName 目标目录
 * @param isCreateRoot 是否创建根目录
 */
int copyDir(char *fromDirPathName, char *toDirPathName)
{
    cout << "copyDir:: fromDirPathName:" << fromDirPathName << ",toDirPathName:" << toDirPathName << endl;
    DIR *fromDir;            //指向源目录的指针变量
    DIR *toDir;              //指向目标目录的指针变量
    struct stat info;        //目录或者文件系统文件属性
    struct dirent *fromDent; //指向目录项的指针变量
    char fromPathName[1024]; //源目录或者源文件路径
    char toPathName[1024];   //目标目录或者目标文件路径

    int rt = lstat(fromDirPathName, &info); //获取系统文件属性
    if (rt == -1)
    {
        perror("lstat error");
        return 1;
    }
    fromDir = opendir(fromDirPathName); //打开源目录
    if (fromDir == nullptr)
    {
        perror("opendir from dir error");
        cout << "打开源目录失败:" << fromDirPathName << endl;
        return 1;
    }

    //打开要拷贝的目录,如果不存在则创建该目录
    toDir = opendir(toDirPathName); //打开目标目录
    if (toDir == nullptr)
    {
        rt = mkdir(toDirPathName, info.st_mode); //创建一个新目录
        if (rt == -1)
        {
            perror("mkdir new dir error");
            cout << "创建新目录失败:" << toDirPathName << endl;
            return 1;
        }
        toDir = opendir(toDirPathName);
        if (toDir == nullptr)
        {
            perror("opendir error");
            return 1;
        }
    }

    errno = 0;
    //循环读取源目录文件项内容,并且拷贝到新目录中
    while ((fromDent = readdir(fromDir)) != nullptr)
    {
        bzero(fromPathName, sizeof(fromPathName)); //清空缓冲区
        bzero(toPathName, sizeof(toPathName));     //清空缓冲区

        // long nodeNumber = fromDent->d_ino; //索引节点编号
        // char *nodeName = fromDent->d_name; //索引节点名称
        // printf("索引节点编号:%ld,索引节点名称:%s\n", nodeNumber, nodeName);

        if (*fromDent->d_name == '.') //过滤掉 "." ".."
            continue;

        sprintf(fromPathName, "%s/%s", fromDirPathName, fromDent->d_name); //构造完整的源文件(源目录)相对路径
        sprintf(toPathName, "%s/%s", toDirPathName, fromDent->d_name);     //构造完整的目标文件(目标目录)相对路径
        printf("fromPathName:%s\n", fromPathName);
        printf("toPathName:%s\n", toPathName);

        switch (checkFileType(fromPathName))
        {
        case 1: //普通文件
            copyRegularFile(fromPathName, toPathName);
            break;
        case 2: //目录文件,递归拷贝目录
            copyDir(fromPathName, toPathName);
            break;
        case 3: //符号连接文件
            copyLinkFile(fromPathName, toPathName);
            break;
        default:
            break;
        }
    }

    if (errno != 0)
    {
        perror("readdir error");
    }

    closedir(fromDir); //关闭目录
    closedir(toDir);   //关闭目录
    cout << endl;
    return 0;
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
 * @brief 检查文件类型
 *
 * @param pathname 文件名
 * @return int 返回文件类型
 */
int checkFileType(char *pathname)
{
    struct stat statbuf;       //系统文件属性
    lstat(pathname, &statbuf); //获取系统文件属性
    int typeflag;
    switch (statbuf.st_mode & S_IFMT)
    {
    case S_IFREG: //普通文件
        typeflag = 1;
        break;
    case S_IFDIR: //目录文件
        typeflag = 2;
        break;
    case S_IFLNK: //链接文件
        typeflag = 3;
        break;
    case S_IFCHR: //字符设备文件
        typeflag = 4;
        break;
    case S_IFBLK: //块设备文件
        typeflag = 5;
        break;
    case S_IFSOCK: // Sock文件
        typeflag = 6;
        break;
    case S_IFIFO: //管道文件
        typeflag = 7;
        break;
    default:
        typeflag = 0; //未知类型文件
        break;
    }
    return typeflag;
}