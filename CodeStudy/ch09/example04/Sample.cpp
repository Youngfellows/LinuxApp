#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    NetUtil::getIP();
    cout << endl;
}

/**
 * @brief UDP服务端
 *
 */
void test2()
{
    cout << "test2():: ..." << endl;
    std::shared_ptr<UDPServer> server = std::make_shared<UDPServer>();
    bool res = server->create();
    if (res)
    {
        res = server->bindSocket();
        if (res)
        {
            server->acceptSocket();
        }
    }
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