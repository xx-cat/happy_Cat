#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QFile>
//通过TcpSocket来连接服务器和收发服务器数据
#include<QTcpSocket>
#include "protocol.h"
#include"opewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TcpClient; }
QT_END_NAMESPACE

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
    //加载我们的配置
    void loadConfig();

    static TcpClient &getInstance();
    QTcpSocket &getTcpSocket();
    QString loginName();
    QString curPath();
    void setCurPath(QString strCurPath);

public slots:
    void showConnect();
    void recvMsg();

private slots:
//    void on_send_pb_clicked();

    void on_login_pb_clicked();

    void on_regist_pb_clicked();

    void on_cancel_pb_clicked();


private:
    Ui::TcpClient *ui;
    //IP
    QString m_strIp;
    //端口、无符号短整型
    quint16 m_usPort;

    //连接服务器，和服务器数据交互
    QTcpSocket m_tcpSocket;

    //登录名
    QString m_strLoginName;

    QString m_strCurPath;
    QFile m_file;
};
#endif // TCPCLIENT_H
