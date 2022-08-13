#include "./include/Sample.h"

/**
 * @brief 实现ls功能
 * @brief 测试: ./obj/test_sample.out -l /etc/passwd
 */
void test1(int argc, char *argv[])
{
    cout << "test1():: ..." << endl;
    //判断命令行参数
    if (argc != 3)
    {
        printf("用法:$s -l 文件名\n", argv[0]);
        return;
    }
    if (strcmp(argv[1], "-l") != 0)
    {
        printf("用法:$s -l 文件名\n", argv[0]);
        return;
    }

    //检查文件类型
    int rt = checkFileType(argv[2]);
    switch (rt)
    {
    case 0:
        printf("未知类型文件\n");
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        displayProperties(argv[2]);
        break;
    default:
        break;
    }

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

/**
 * @brief 打印文件属性
 *
 * @param pathname 文件名
 */
void displayProperties(char *pathname)
{
    struct stat statbuf;                //系统文件属性
    struct passwd *user;                //用户信息
    struct group *grp;                  //所属组信息
    char linkName[64];                  //链接的文件名
    char dirFileName[64];               //目录文件名称
    int rt = lstat(pathname, &statbuf); //获取系统文件属性
    if (rt == -1)
    {
        perror("displayProperties:lstat");
        cout << "获取系统文件属性失败:" << pathname << endl;
        return;
    }
    //获取文件类型
    switch (statbuf.st_mode & S_IFMT)
    {
    case S_IFREG: //普通文件
        printf("-");
        break;
    case S_IFDIR: //目录文件
        printf("d");
        break;
    case S_IFLNK: //链接文件
        printf("l");
        break;
    case S_IFCHR: //字符设备文件
        printf("c");
        break;
    case S_IFBLK: //块设备文件
        printf("b");
        break;
    case S_IFSOCK: // Sock文件
        printf("s");
        break;
    case S_IFIFO: //管道文件
        printf("p");
        break;
    default: //未知类型文件
        printf("?");
        break;
    }

    //获取文件权限 - 用户权限
    putchar(((statbuf.st_mode & S_IRUSR) ? 'r' : '-'));
    putchar(((statbuf.st_mode & S_IWUSR) ? 'w' : '-'));
    if (statbuf.st_mode & S_ISUID) //用户有修饰权限
    {
        putchar(((statbuf.st_mode & S_IXUSR) ? 's' : 'S')); //是否具有执行权限
    }
    else
    {
        //用户没有修饰权限
        putchar(((statbuf.st_mode & S_IXUSR) ? 'x' : '-')); //是否具有执行权限
    }

    //获取文件权限 - 所属组权限
    putchar(((statbuf.st_mode & S_IRGRP) ? 'r' : '-'));
    putchar(((statbuf.st_mode & S_IWGRP) ? 'w' : '-'));
    if (statbuf.st_mode & S_ISGID) //用户有修饰权限
    {
        putchar(((statbuf.st_mode & S_IXGRP) ? 's' : 'S')); //是否具有执行权限
    }
    else
    {
        //用户没有修饰权限
        putchar(((statbuf.st_mode & S_IXGRP) ? 'x' : '-')); //是否具有执行权限
    }

    //获取文件权限 - 其他成员权限
    putchar(((statbuf.st_mode & S_IROTH) ? 'r' : '-'));
    putchar(((statbuf.st_mode & S_IWOTH) ? 'w' : '-'));
    if (statbuf.st_mode & S_ISVTX) //用户有修饰权限
    {
        putchar(((statbuf.st_mode & S_IXOTH) ? 't' : 'T')); //是否具有执行权限
    }
    else
    {
        //用户没有修饰权限
        putchar(((statbuf.st_mode & S_IXOTH) ? 'x' : '-')); //是否具有执行权限
    }

    nlink_t stNlink = statbuf.st_nlink; //硬连接数
    printf(" %lu", stNlink);
    user = getpwuid(statbuf.st_uid); //获取用户信息
    char *uName = user->pw_name;     //用户名
    printf(" %s", uName);
    grp = getgrgid(statbuf.st_gid); //获取所属组信息
    char *grpName = grp->gr_name;   //组名称
    printf(" %s", grpName);
    displaySize(&statbuf); //显示文件大小
    displayDate(&statbuf); //显示文件更新时间
    //如果是符号链接文件,打印原文件名
    if ((statbuf.st_mode & S_IFMT) == S_IFLNK)
    {
        rt = readlink(pathname, linkName, sizeof(linkName)); //读取符号链接文件的原文件名
        linkName[rt] = 0;
        printf(" %s->%s", pathname, linkName);
    }
    else
    {
        printf(" %s", pathname);
    }
    printf("\n");
}

/**
 * @brief 打印文件大小
 *
 * @param statbuf 系统文件属性
 */
void displaySize(struct stat *statbuf)
{
    switch (statbuf->st_mode & S_IFMT)
    {
    case S_IFCHR: //字符设备文件
    case S_IFBLK: //块设备文件
        printf(" %u,%u", (unsigned)(statbuf->st_rdev >> 8), (unsigned)(statbuf->st_rdev & 0xFF));
        break;
    default:
        printf(" %lu", (unsigned long)statbuf->st_size);
        break;
    }
}

/**
 * @brief 显示时间
 *
 * @param statbuf 系统文件属性
 */
void displayDate(struct stat *statbuf)
{
    time_t now;  //当前时间
    double diff; //时间差
    char buff[100];
    char *fmt; //时间日期格式化
    if (time(&now) == -1)
    {
        perror("time error");
        printf("???????????????????");
        return;
    }
    diff = difftime(now, statbuf->st_mtime);     //获取文件更新时间差
    if (diff < 0 || diff > 60 * 60 * 24 * 182.5) // 6个月
    {
        fmt = "%b %e  %Y"; //时间日期格式化
    }
    else
    {
        fmt = "%b %e %H:%M"; //时间日期格式化
    }
    strftime(buff, sizeof(buff), fmt, localtime(&statbuf->st_mtime)); //时间格式化
    printf(" %s", buff);
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