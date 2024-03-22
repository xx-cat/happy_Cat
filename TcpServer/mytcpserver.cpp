#include "mytcpserver.h"
#include<QDebug>

MyTcpserver::MyTcpserver()
{

}

MyTcpserver &MyTcpserver::getInstance()
{
    //静态函数无论调用多少次也只有一个对象
    static MyTcpserver instance;
    return instance;
}

//监听之后只要有客户端连接进来就调用以下函数
void MyTcpserver::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"new client connected";
    //将客户端连接和该数据收发的socket进行连接
    MyTcpSocket *pTcpSocket = new MyTcpSocket;
    pTcpSocket->setSocketDescriptor(socketDescriptor);
    //把客户端的socket放入链表中
    m_tcpSocketList.append(pTcpSocket);

    connect(pTcpSocket,SIGNAL(offline(MyTcpSocket*)),this,SLOT(deleteSocket(MyTcpSocket*)));

}

void MyTcpserver::resend(const char *pername, PDU *pdu)
{
    if(NULL == pername || NULL == pdu){
        return;
    }
    QString strName = pername;
    for(int i=0;i<m_tcpSocketList.size();i++){
//        qDebug()<<"m_tcpSocketList.size():"<<m_tcpSocketList.size();
//        qDebug()<<"strName:"<<strName;
//        qDebug()<<"m_tcpSocketList.at(i)->getName():"<<m_tcpSocketList[i]->getName();
        if(strName == m_tcpSocketList[i]->getName()){
            m_tcpSocketList[i]->write((char*)pdu,pdu->uiPDULen);
            break;
        }

    }
}

void MyTcpserver::deleteSocket(MyTcpSocket *mysocket)
{
    //通过迭代器遍历整个列表 ，以获取它指向这个socket指针
    QList<MyTcpSocket*>::iterator iter = m_tcpSocketList.begin();//指向它的第一个数据
    for(;iter != m_tcpSocketList.end();iter++){
        if(mysocket == *iter){
            //删除一是指针指向的对象
            delete *iter;
            *iter = NULL;
            //二是列表里面的指针
            m_tcpSocketList.erase(iter);
            break;
        }
    }
    for(int i=0;i<m_tcpSocketList.size();i++){
        qDebug()<<m_tcpSocketList.at(i)->getName();
    }

}

//笔记
/*
客户端连接服务器的过程：
客户端：
加载配置文件，客户端产生一个socket，通过socket连接服务器，然后发送一个connected信号，关联处理信号，把"连接成功的信息"显示出来，

服务器端：
tcpserver进行监听（该tcpserver被我们继承，产生了一个我们自己写的派生类）
*/
