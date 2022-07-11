#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    // 点分形式IP地址转化为整数形式
    std::shared_ptr<IPTranslation> translation = std::make_shared<IPTranslation>();
    translation->translation1();
    translation->translation2();
    translation->translation3();
    translation->translation4();
    cout << endl;
}

void test2()
{
    cout << "test2():: ..." << endl;
    // IP地址与主机名相互转化
    std::shared_ptr<HostnameTranslation> translation = std::make_shared<HostnameTranslation>();
    char *hostname = translation->getHostName();
    translation->getHostInfo();
    char *ip = translation->translateIP(hostname);
    translation->translateHostname(ip);
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