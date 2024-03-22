#include "tcpclient.h"
#include <QApplication>
#include <sharefile.h>
//#include "book.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    ShareFile w;
//    w.test();
//    w.show();
//    TcpClient w;
//    w.show();
//    Book w;
//    w.show();
    TcpClient::getInstance().show();

    return a.exec();
}
