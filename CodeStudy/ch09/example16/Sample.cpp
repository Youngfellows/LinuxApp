#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    const char *patnname = "./file/f1.txt";
    int fd = open(patnname, O_RDWR);
    if (fd == -1)
    {
        perror("open file error");
        return;
    }
    char cachBuff[MAXSIZE]; //缓冲区
    int number = 0;
    while ((number = read(fd, cachBuff, MAXSIZE)) > 0)
    {
        printf("%s\n", cachBuff);
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