#include "./include/Sample.h"

/**
 * @brief 拷贝文件夹到目录
 * @brief "cp 文件 目录"
 *
 * @param argc
 * @param argv
 */
void test1(int argc, char *argv[])
{
    cout << "test1():: ..." << endl;
    if (argc != 3)
    {
        printf("使用:%s 文件 目录\n", argv[0]);
        return;
    }
    char *spathname = argv[1];                //源文件
    char *dpathname = argv[2];                //目标目录
    int sFileType = checkFileType(spathname); //检测文件类型
    int dFileType = checkFileType(dpathname); //检测文件类型
    printf("sFileType:%d,dFileType:%d\n", sFileType, dFileType);
    DIR *dir = opendir(dpathname); //打开目录文件
    if (dir == nullptr)
    {
        perror("opendir error");
        cout << "打开目录失败:" << dpathname << endl;
        return;
    }
    errno = 0;
    struct dirent *dent = nullptr;           //指向目录项的指针变量
    while ((dent = readdir(dir)) != nullptr) //循环读取目录项
    {
        long nodeNum = dent->d_ino;    //索引节点
        char *nodeName = dent->d_name; //文件名称
        errno = 0;
        printf("nodeNum:%ld,nodeName:%s\n", nodeNum, nodeName);
    }
    if (errno != 0)
    {
        perror("readdir error");
    }

    //提取文件名,提取路径
    char *sFileName = basename(spathname); //提取文件名
    char *sPath = strdup(spathname);       //提取文件路径
    cout << "sFileName:" << sFileName << endl;
    cout << "1,sPath:" << sPath << endl;
    char *sDirName = dirname(sPath); //获取目录名称,sPath的值会被改变
    cout << "2,sPath:" << sPath << endl;
    cout << "sDirName:" << sDirName << endl;

    //拷贝文件到目录
    char *newPathNmae = new char[strlen(sFileName) + strlen(dpathname) + 1]; //新文件名
    sprintf(newPathNmae, "%s/%s", dpathname, sFileName);                     //字符串拼接,新文件名
    printf("newPathName:%s\n", newPathNmae);

    int fromfd;       //源文件文件描述符
    int tofd;         //目标文件文件描述符
    char buffer[100]; //内容缓冲区

    fromfd = open(spathname, O_RDONLY); //以只读方式打开要拷贝的源文件
    if (fromfd == -1)
    {
        perror("open fromfd error");
        cout << "打开源文件失败:" << spathname << endl;
    }
    else
    {
        tofd = open(newPathNmae, O_WRONLY | O_CREAT | O_TRUNC, 0644); //创建比打开文件
        if (tofd == -1)
        {
            perror("open tofd error");
            cout << "打开文件失败:" << newPathNmae << endl;
        }
        else
        {
            int number = 0;
            //读取文件并写入新文件中
            while ((number = read(fromfd, buffer, sizeof(buffer))) > 0)
            {
                write(tofd, buffer, number); //写入文件
            }
            close(tofd); //关闭文件
        }
        close(fromfd); //关闭文件
    }
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