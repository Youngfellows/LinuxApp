#include "./include/Sample.h"

/**
 * @brief 打印命令行参数
 *
 * @param argc 参数个数
 * @param argv 参数列表
 */
void printArgv(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s\t", argv[i]);
    }
    printf("\n");
}

/**
 * @brief 获取命令行参数
 * @brief 使用: ./obj/test_sample.out [-l] [目录名/文件名]
 * @brief 使用: ./obj/test_sample.out
 * @brief 使用: ./obj/test_sample.out -h
 * @brief 使用: ./obj/test_sample.out -l
 * @brief 使用: ./obj/test_sample.out -l /etc/passwd
 * @brief 使用: ./obj/test_sample.out -l ./file
 *
 * @param argc 参数个数
 * @param argv 参数列表
 *
 *
 */
void test0(int argc, char *argv[])
{
    cout << "test1():: ..." << endl;
    printArgv(argc, argv);
    printf("====================\n");
    if (argc == 1)
    {
        // cout << "使用: " << argv[0] << " [-l] [目录名/文件名]" << endl;
        lsdir(".", FLAG_DIR); //目录类型
        return;
    }

    const char *optstring = "hl:";
    int optchar;              //返回选项参数中的选项字符
    opterr = 0;               //遇到未知的选项参数,或选项参数缺失时,返回？代表出错
    char *pathname = nullptr; //目录或者文件名称
    while ((optchar = getopt(argc, argv, optstring)) != -1)
    {
        printf("optchar=%c\n", optchar);
        switch (optchar)
        {
        case 'l':
        {
            pathname = optarg;
            // cout << pathname << endl;
            printf("%s\n", optarg);
            int fileType = checkFileType(optarg);
            printf("fileType:%d\n", fileType);
            if (fileType == 2) //目录类型
            {
                lsdir(pathname, FLAG_DIR);
            }
            else
            {
                lsdir(pathname, FLAG_FILE); //文件类型
            }
            break;
        }
        case 'h': //使用帮助
            cout << "使用: " << argv[0] << " [-l] [目录名/文件名]" << endl;
            return;
        case '?':
        {
            // optop存储的是未知的参数或缺失参数的选项字符
            if (optopt == 'l')
            {
                // fprintf(stderr, "选项字符 \'-%c\' 需要一个参数\n", optopt);
                lsdir(".", FLAG_DIR); //目录类型
            }
            else if (isprint(optopt))
            {
                fprintf(stderr, "未知的选项字符 \'-%c\'\n", optopt);
            }
            else
            {
                fprintf(stderr, "未知的选项字符 \'%x\'\n", optopt);
            }
            break;
        }
        default:
            break;
        }
    }

    printf("====================\n");
    printArgv(argc, argv);

    //遍历未知的选项参数
    for (int i = optind; i < argc; i++)
    {
        printf("未知的选项参数:%s\n", argv[i]);
    }
    cout << endl;
}

/**
 * @brief 实现"ls 目录"功能
 * @brief 实现"ls 文件"功能
 * @brief 测试: ./obj/test_sample.out
 * @brief 测试: ./obj/test_sample.out -l
 * @brief 测试: ./obj/test_sample.out ./include/
 * @brief 测试: ./obj/test_sample.out /home
 * @brief 测试: ./obj/test_sample.out  -l ./includ
 * @brief 测试: ./obj/test_sample.out -l /home/
 * @brief 测试:
 */
void test1(int argc, char *argv[])
{
    cout << "test1():: ..." << endl;
    //判断命令行参数
    if (argc > 3)
    {
        printf("用法:%s \n", argv[0]);
        printf("用法:%s 文件名\n", argv[0]);
        printf("用法:%s 目录名\n", argv[0]);
        printf("用法:%s -l 文件名\n", argv[0]);
        printf("用法:%s -l 目录名\n", argv[0]);
        return;
    }

    printf("argc:%d\n", argc);

    //显示当前目录信息
    if (argc == 1)
    {
        lsdir(".", FLAG_DIR); //目录类型
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-l") == 0)
        {
            cout << "xxxxxxxxxx" << endl;
            lsdir(".", FLAG_DIR); //文件类型
        }
        else
        {
            int fileType = checkFileType(argv[1]);
            printf("fileType:%d\n", fileType);
            if (fileType == 2) //目录类型
            {
                cout << "yyyyyyyy" << endl;
                lsdir(argv[1], FLAG_DIR);
            }
            else
            {
                cout << "ssssssssssssssss" << endl;
                lsdir(argv[1], FLAG_FILE); //文件类型
            }
        }
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-l") == 0)
        {
            int fileType = checkFileType(argv[2]);
            cout << "fileType:" << fileType << endl;
            if (fileType == 2) //目录类型
            {
                lsdir(argv[2], FLAG_DIR);
            }
            else
            {
                lsdir(argv[2], FLAG_FILE); //文件类型
            }
        }
    }
    cout << endl;
}

/**
 * @brief 实现"ls 目录"功能
 * @brief 实现"ls 文件"功能
 *
 * @param pathname 目录名或者文件名
 * @param flag 是否目录的标志
 */
void lsdir(char *pathname, int flag)
{
    cout << "lsdir:: pathName:" << pathname << endl;
    DIR *dir;                //指向目录文件的指针变量
    struct dirent *dent;     //指向目录项的指针变量
    char workdir[100];       //当前工作目录
    dir = opendir(pathname); //打开目录
    if (dir == nullptr)
    {
        perror("opendir");
        cout << "打开目录文件失败:" << pathname << endl;
        return;
    }
    getcwd(workdir, 100); //获取当前目录
    printf("当前目录:%s\n", workdir);
    //切换到指定目录
    if (chdir(pathname) == -1)
    {
        perror("chdir error");
        cout << "切换到指定目录失败:" << pathname << endl;
    }

    //反复读取目录
    errno = 0;
    while ((dent = readdir(dir)) != nullptr)
    {
        char *nodeName = dent->d_name; //目录项文件名
        if (nodeName[0] != '.')
        {
            if (flag == FLAG_DIR) //是目录
            {
                printf("%s\t", nodeName); //打印文件名
            }
            else
            {
                displayProperties(nodeName); //显示文件属性信息
            }
        }
    }
    if (errno != 0)
    {
        perror("readdir");
    }
    if (flag == FLAG_DIR)
    {
        printf("\n");
    }

    closedir(dir);  //关闭目录
    chdir(workdir); //切换回工作目录
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