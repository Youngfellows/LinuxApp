#include "./include/Sample.h"

void test1(int argc, char *argv[])
{
    cout << "test1():: ..." << endl;
    if (argc != 3)
    {
        printf("使用:%s 目录 目录\n", argv[0]);
        return;
    }
    char *fromDirName = argv[1]; //源目录
    char *toDirName = argv[2];   //目标目录
    mycpdir(fromDirName, toDirName);
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
 * @brief 复制符号链接
 *
 * @param name1 源文件名
 * @param name2 目标文件名
 * @return int 成功返回0
 */
int mycplink(char *name1, char *name2)
{
    char buf[1024] = ""; //缓冲区
    int ret;
    ret = readlink(name1, buf, sizeof(buf)); //读取符号连接所指的原文件名
    if (ret != 0)
    {
        symlink(buf, name2); //创建一个符号连接文件
    }
    return 0;
}

/**
 * @brief 复制普通文件
 *
 * @param dir1 源文件名
 * @param dir2 目标文件名
 * @return int 成功返回0
 */
int mycp(char *dir1, char *dir2)
{
    int fd1;        //源文件文件描述符
    int fd2;        //目标件文件描述符
    int ret;        //读取的字节数
    int sts;        //成功写入的字节数
    char buf[1024]; //缓冲区

    fd1 = open(dir1, O_RDONLY); //打开文件
    if (fd1 == -1)
    {
        perror("open dir1 error");
        cout << "打开文件失败:" << dir1 << endl;
        return 1;
    }
    fd2 = open(dir2, O_WRONLY | O_CREAT | O_TRUNC, 0666); //创建并打开文件,如果文件存在则置空
    if (fd2 == -1)
    {
        perror("open dir2 error");
        cout << "打开文件失败:" << dir2 << endl;
        return 1;
    }

    bzero(buf, sizeof(buf));                            //清空缓冲区
    while ((ret = read(fd1, buf, sizeof(buf) - 1)) > 0) //循环读出文件内容
    {
        sts = write(fd2, buf, ret); //向文件fd2中写入读取的数据
        while (sts < ret)
        {
            sts += write(fd2, buf + sts, ret - sts); //循环写入未写入的数据
        }
        bzero(buf, sizeof(buf)); //清空缓冲区
    }

    close(fd1); //关闭fd1文件
    close(fd2); //关闭fd2文件

    struct stat info;        //源文件系统文件属性
    ret = stat(dir1, &info); //获取源文件系统文件属性
    if (ret != 0)
    {
        perror("stat");
        return 1;
    }
    chmod(dir2, info.st_mode); //改变文件访问权限
    return 0;
}

/**
 * @brief 复制目录
 *
 * @param name1 源目录
 * @param name2 目标目录
 * @return int 成功返回0
 */
int mycpdir(char *name1, char *name2)
{
    int ret;
    DIR *dir1;           //指向源目录文件的指针
    DIR *dir2;           //指向目标目录文件的指针
    struct dirent *drr;  //指向目录项的指针变量
    struct stat info;    //系统文件属性
    struct stat dirinfo; //目录文件系统属性
    char buf1[1024];     //源目录或者源文件路径
    char buf2[1024];     //目标目录或者目标文件路径

    lstat(name1, &info);   //获取name1的信息
    dir1 = opendir(name1); //打开源目录
    if (dir1 == NULL)
    {
        perror("open dir1");
        cout << "打开源目录失败:" << name1 << endl;
        return 1;
    }

    dir2 = opendir(name2); //打开name2目录, 打开失败则创建
    if (dir2 == NULL)
    {
        int rt = mkdir(name2, info.st_mode); //创建目标目录
        if (rt == -1)
        {
            perror("mkdir error");
            return 1;
        }
        dir2 = opendir(name2); //再次打开name2目录
        if (dir2 == nullptr)
        {
            perror("opendir error");
            return 1;
        }
    }

    //循环读取目录文件,获取每一个目录项
    while ((drr = readdir(dir1)) != nullptr)
    {
        bzero(buf2, sizeof(buf2));
        bzero(buf2, sizeof(buf2));
        if (*drr->d_name == '.') //过滤掉 "." ".."
            continue;
        sprintf(buf1, "%s/%s", name1, drr->d_name); //构造完整的源文件(源目录)相对路径
        sprintf(buf2, "%s/%s", name2, drr->d_name); //构造完整的目标文件(目标目录)相对路径
        printf("from:%s\n", buf1);
        printf("to:%s\n", buf2);

        ret = lstat(buf1, &dirinfo); //获取源文件系统属性
        if (ret == -1)
        {
            perror("lstat error");
            break;
        }
        if (S_ISDIR(dirinfo.st_mode)) //如果是目录
        {
            mycpdir(buf1, buf2); //递归拷贝目录
        }
        else if (S_ISREG(dirinfo.st_mode)) //如果是普通文件
        {
            mycp(buf1, buf2); //拷贝文件
        }
        else if (S_ISLNK(dirinfo.st_mode)) //如果是符号链接
        {
            mycplink(buf1, buf2); //拷贝符号连接
        }
    }

    closedir(dir1); //关闭源目录文件
    closedir(dir2); //关闭目标目录文件
    return 0;
}