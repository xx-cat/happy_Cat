#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
#include<protocol.h>
#include<opedb.h>
#include<QDir>
#include<QFile>
#include<QTimer>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    QString getName();
    void copyDir(QString strSrcDir, QString strDestDir);

signals:
    //用地址操作
    void offline(MyTcpSocket *mysocket);

public slots:
    void recvmsg();
    //用来处理槽函数下线的信号
    void clientOffline();
    void sendFileToClient();
private:
    QString m_strName;

    QFile m_file;
    qint64 m_iTotal;
    qint64 m_iRecved;
    bool m_bUpload;

    QTimer *m_pTimer;
};

#endif // MYTCPSOCKET_H
