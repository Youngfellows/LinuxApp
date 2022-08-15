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
    DIR *fromDir;                //指向源目录的指针变量
    DIR *toDir;                  //指向目标目录的指针变量
    // struct dirent *fromDent;        //指向目录项的指针变量
    fromDir = opendir(fromDirName); //打开目录
    if (fromDir == nullptr)
    {
        perror("opendir from dir error");
        cout << "打开源目录失败:" << fromDirName << endl;
        return;
    }
    toDir = opendir(toDirName); //打开目录
    if (toDir == nullptr)
    {
        perror("opendir to dir error");
        cout << "打开目录文件失败,errno:" << errno << "," << toDirName << endl;
        int rt = mkdir(toDirName, 0644); //创建一个目录
        if (rt == -1)
        {
            perror("mkdir error");
            cout << "创建目录失败:" << toDirName << endl;
        }
        else
        {
            //目录创建成功,开始拷贝目录
            cout << "目录创建成功,开始拷贝目录" << endl;
            copyDir(fromDirName, toDirName, true);
        }
    }
    else
    {
        //目录存在,开始拷贝目录
        cout << "目录存在,开始拷贝目录" << endl;
        copyDir(fromDirName, toDirName, true);
    }

    cout << endl;
}

/**
 * @brief 拷贝目录到指定目录
 *
 * @param fromDirName 源目录
 * @param toDirName 目标目录
 * @param isCreateRoot 是否创建根目录
 */
void copyDir(char *fromDirPathName, char *toDirPathName, bool isCreateRoot)
{
    cout << endl;
    cout << "copyDir:: isCreateRoot:" << isCreateRoot << ",fromDirPathName:" << fromDirPathName << ",toDirPathName:" << toDirPathName << endl;
    cout << "0,toDirPathName:" << toDirPathName << endl;
    DIR *fromDir;            //指向源目录的指针变量
    DIR *toDir;              //指向目标目录的指针变量
    struct dirent *fromDent; //指向目录项的指针变量
    cout << "01,toDirPathName:" << toDirPathName << endl;
    fromDir = opendir(fromDirPathName); //打开目录
    cout << "02,toDirPathName:" << toDirPathName << endl;
    if (fromDir == nullptr)
    {
        perror("opendir from dir error");
        cout << "打开源目录失败:" << fromDirPathName << endl;
        return;
    }
    cout << "1,toDirPathName:" << toDirPathName << endl;

    //提取文件名,提取路径
    char *fromDirName = basename(fromDirPathName); //提取目录名称
    char *fromDirPath = strdup(fromDirPathName);   //提取目录路径
    cout << "fromDirName:" << fromDirName << endl;
    cout << "1,fromDirPath:" << fromDirPath << endl;

    char *fromParentDirPath = dirname(fromDirPath); //获取父目录名称,fromDirPath的值会被改变
    cout << "2,fromDirPath:" << fromDirPath << endl;
    cout << "fromParentDirPath:" << fromParentDirPath << endl;
    cout << "2,toDirPathName:" << toDirPathName << endl;

    //在新目录中创建一个源目录
    char *newPathName = nullptr;
    // char *newPathName = new char[strlen(toDirPathName) + strlen(fromDirName) + 1]; //新目录名
    // sprintf(newPathName, "%s/%s", toDirPathName, fromDirName);                     //字符串拼接,新文件名
    // printf("newPathName:%s\n", newPathName);
    cout << "3,toDirPathName:" << toDirPathName << endl;

    if (isCreateRoot)
    {
        newPathName = new char[strlen(toDirPathName) + strlen(fromDirName) + 1]; //新目录名
        sprintf(newPathName, "%s/%s", toDirPathName, fromDirName);               //字符串拼接,新文件名
        printf("newPathName:%s\n", newPathName);
    }
    else
    {
        cout << "toDirPathName:" << toDirPathName << endl;
        newPathName = new char[strlen(toDirPathName) + 1];
        strcpy(newPathName, toDirPathName);
        newPathName[strlen(toDirPathName)] = '\0';
    }
    printf("newPathName:%s\n", newPathName);

    //创建一个新目录
    int rt = mkdir(newPathName, 0644);
    if (rt == -1)
    {
        perror("mkdir new dir error");
        cout << "创建新目录失败:" << newPathName << endl;
        return;
    }

    errno = 0;
    //循环读取源目录文件项内容,并且拷贝到新目录中
    while ((fromDent = readdir(fromDir)) != nullptr)
    {
        long nodeNumber = fromDent->d_ino; //索引节点编号
        char *nodeName = fromDent->d_name; //索引节点名称
        printf("索引节点编号:%ld,索引节点名称:%s\n", nodeNumber, nodeName);
        // cout << "is . dir " << (strcmp(nodeName, ".") == 0) << endl;
        // cout << "is .. dir " << (strcmp(nodeName, "..") == 0) << endl;

        //获取源目录路径或者文件路径
        char *fromName = new char[strlen(fromDirPathName) + strlen(nodeName) + 1]; //文件路径(文件名)
        sprintf(fromName, "%s/%s", fromDirPathName, nodeName);                     //字符串拼接,文件名
        printf("fromName:%s\n", fromName);
        int fileType = checkFileType(fromName);
        printf("fileType:%d\n", fileType);
        //递归拷贝目录
        if ((fileType == 2))
        {
            if (((strcmp(nodeName, ".") == 0) || (strcmp(nodeName, "..") == 0)))
            {
                cout << "is . or .." << endl;
            }
            else
            {
                char *toDirName = new char[strlen(newPathName) + strlen(nodeName) + 1]; //文件路径(文件名)
                sprintf(toDirName, "%s/%s", newPathName, nodeName);                     //字符串拼接,文件名
                printf("toDirName:%s\n", toDirName);
                delete[] newPathName;
                copyDir(fromName, toDirName, false); //递归拷贝目录
            }
        }
        else if (fileType == 1)
        {
            //拷贝单个源文件到指定路径
            char *toName = new char[strlen(newPathName) + strlen(nodeName) + 1]; //文件路径(文件名)
            sprintf(toName, "%s/%s", newPathName, nodeName);                     //字符串拼接,文件名
            printf("toName:%s\n", toName);
        }
    }

    if (errno != 0)
    {
        perror("readdir error");
    }

    closedir(fromDir); //关闭目录
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