#include "tcpserver.h"
#include "ui_tcpserver.h"
#include<QDebug>
#include<QMessageBox>
#include<QHostAddress>
#include<QTcpSocket>
#include<QFile>

TcpServer::TcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpServer)

{
    ui->setupUi(this);

    loadConfig();

    //监听
    MyTcpserver::getInstance().listen(QHostAddress(m_strIp),m_usPort);
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::loadConfig()
{

    QFile file(":/tcpserver.config");
    if(file.open(QIODevice::ReadOnly)){
        QByteArray baData = file.readAll();
        //转换成字符串 获取其首地址转化为char*
        QString strData = baData.toStdString().c_str();
        //       qDebug()<<strData;
        file.close();

        strData.replace("\r\n"," ");
        qDebug()<<strData;

        //空格切分
        QStringList strList = strData.split(" ");
        //        for(int i=0;i<strList.size();i++){
        //           qDebug()<<"--->"<<strList[i];
        //       }
        m_strIp = strList[0];
        //端口是一个字符串 需转换为整型
        m_usPort = strList[1].toShort();
        qDebug()<<"IP："<<m_strIp<<" 端口："<<m_usPort;
    }else{
        QMessageBox::critical(this,"open config","open config failed");
    }

}

