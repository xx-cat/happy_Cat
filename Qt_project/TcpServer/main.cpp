#include "tcpserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //数据库的初始化
    OpeDB::getInstance().init();

    TcpServer w;
    w.show();

    return a.exec();
}
