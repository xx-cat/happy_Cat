#ifndef OPEDB_H
#define OPEDB_H

#include <QObject>
//连接数据库
#include<QSqlDatabase>
//查询数据库
#include<QSqlQuery>
#include<QStringList>

class OpeDB : public QObject
{
    Q_OBJECT
public:
    explicit OpeDB(QObject *parent = nullptr);
    //将数据库定义为单例模式（使用时可通过单例模式快速调用）：把它定义为一个静态的成员函数，然后在静态的成员函数里定义一个静态的函数对象
    static OpeDB& getInstance();

    void init();
    ~OpeDB();

    bool handleRegist(const char *name,const char *pwd);
    bool handleLogin(const char *name,const char *pwd);
    void handleOffline(const char *name);
    QStringList handleAllOnline();
    int handleSearchUsr(const char *name);
    int handleAddFriend(const char *pername,const char *name);
    void handleArgeeAddFriend(const char *pername,const char *name);
    QStringList handleFlushFriend(const char * name);
    bool handleDelFriend(const char *name,const char *friendname);

signals:
private:
    QSqlDatabase m_db;//连接数据库


};

#endif // OPEDB_H
