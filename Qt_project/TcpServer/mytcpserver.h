#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpserver>
//把所有的socket都保存在链表里
#include<QList>
#include"mytcpsocket.h"

class MyTcpserver : public QTcpServer
{
    //支持信号槽
    Q_OBJECT
public:
    MyTcpserver();
    //静态成员函数 返回值MyTcpserver  引用函数getInstance
    static MyTcpserver &getInstance();
    //virtual虚函数 重新定义
    void incomingConnection(qintptr socketDescriptor);

    void resend (const char *pername ,PDU *pdu);
public slots:
    //槽和信号参数要一样
    void deleteSocket(MyTcpSocket *mysocket);
private:
    QList<MyTcpSocket*> m_tcpSocketList;
};

#endif // MYTCPSERVER_H
