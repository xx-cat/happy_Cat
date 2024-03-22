#ifndef TCPSERVER_H
#define TCPSERVER_H
#include<mytcpserver.h>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpServer; }
QT_END_NAMESPACE

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = nullptr);
    ~TcpServer();
    void loadConfig();


private:
    Ui::TcpServer *ui;
    //IP
    QString m_strIp;
    //端口、无符号短整型
    quint16 m_usPort;
};
#endif // TCPSERVER_H
