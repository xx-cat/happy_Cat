#include "tcpclient.h"
#include "ui_tcpclient.h"
#include<QByteArray>
//协议
#include"protocol.h"

#include<QDebug>
#include<QMessageBox>
#include<QHostAddress>
#include<QTcpSocket>
#include"privatechat.h"
#include"protocol.h"

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    loadConfig();

//    connect(m_tcpSocket,&Q,this,&TcpClient::showConnect);
    connect(&m_tcpSocket,SIGNAL(connected()),this,SLOT(showConnect()));
    //服务器发送数据给客户端，客户端收到数据的话，就会发出信号去调用该函数接收
    connect(&m_tcpSocket,SIGNAL(readyRead()),this,SLOT(recvMsg()));

    //连接服务器
    m_tcpSocket.connectToHost(QHostAddress(m_strIp),(m_usPort));
}

TcpClient::~TcpClient()
{
    delete ui;
}

//读取数据
void TcpClient::loadConfig()
{
    QFile file(":/client.config");
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

TcpClient &TcpClient::getInstance()
{
    static TcpClient instance;
    return instance;
}

QTcpSocket &TcpClient::getTcpSocket()
{
    return m_tcpSocket;
}

QString TcpClient::loginName()
{
    return m_strLoginName;
}

QString TcpClient::curPath()
{
    return m_strCurPath;
}

void TcpClient::setCurPath(QString strCurPath)
{
    m_strCurPath = strCurPath;
}

void TcpClient::showConnect()
{
    QMessageBox::information(this,"连接服务器","连接服务器成功");
}

void TcpClient::recvMsg()
{
    if(!OpeWidget::getInstance().getBook()->getDownloadStatus()){
    //当前可读到的数据有多少
    qDebug()<<m_tcpSocket.bytesAvailable();
    uint uiPDULen = 0;
    //存放数据的位置，大小
    //获取该四个字节，包含了我们发送的数据的总值的大小
    m_tcpSocket.read((char*)&uiPDULen, sizeof(uint));
    //实际消息长度
    uint uiMsgLen = uiPDULen - sizeof(PDU);
    //通过一个实际的消息长度产生一个PDU来接收剩余数据
    PDU *pdu = mkPDU(uiMsgLen);
    //获取除了前四个字节（总大小数值），剩下的内容
    m_tcpSocket.read((char*)pdu + sizeof(uint),uiPDULen - sizeof(uint));
    switch (pdu->uiMsgType) {
    case ENUM_MSG_TYPE_REGIST_RESPOND:
    {
       //判断回复的信息是成功还是失败
       if(0 == strcmp(pdu->caData, REGIST_OK)){
           QMessageBox::information(this,"注册",REGIST_OK);
       }
       else if(0 == strcmp(pdu->caData, REGIST_FAILED)){
           QMessageBox::warning(this,"注册",REGIST_FAILED);
    }
       break;
    }
    case ENUM_MSG_TYPE_LOGIN_RESPOND:
    {
       //判断回复的信息是成功还是失败
       if(0 == strcmp(pdu->caData, LOGIN_OK)){
           m_strCurPath = QString("./%1").arg(m_strLoginName);

           QMessageBox::information(this,"登录",LOGIN_OK);
           OpeWidget::getInstance().show();
           hide();
       }
       else if(0 == strcmp(pdu->caData, LOGIN_FAILED)){
           QMessageBox::warning(this,"登录",LOGIN_FAILED);
    }
       break;
    }
    case ENUM_MSG_TYPE_ALL_ONLINE_RESPOND:
    {
       OpeWidget::getInstance().getFriend()->showAllOnlineUsr(pdu);
       break;
    }
    case ENUM_MSG_TYPE_SEARCH_USR_RESPOND:
    {
       if(0 == strcmp(SEARCH_USR_NO,pdu->caData)){
           QMessageBox::information(this,"搜索",QString("%1: not exist").arg(OpeWidget::getInstance().getFriend()->m_strSearchName));
       }else if(0 == strcmp(SEARCH_USR_ONLINE,pdu->caData)){
           QMessageBox::information(this,"搜索",QString("%1: online").arg(OpeWidget::getInstance().getFriend()->m_strSearchName));
       }else if(0 == strcmp(SEARCH_USR_OFFLINE,pdu->caData)){
           QMessageBox::information(this,"搜索",QString("%1: offline").arg(OpeWidget::getInstance().getFriend()->m_strSearchName));
       }
        break;
    }
    case ENUM_MSG_TYPE_ADD_FRIEND_REQUEST:{
        char caName [32] = {'\0'};
        strncpy(caName,pdu->caData+32,32);
        int ret = QMessageBox::information(this,"添加好友",QString("%1 want to add you as friend ?").arg(caName),QMessageBox::Yes,QMessageBox::No);
        PDU *respdu = mkPDU(0);
        memcpy(respdu->caData,pdu->caData,64);
        if(QMessageBox::Yes==ret){
           respdu->uiMsgType=ENUM_MSG_TYPE_ADD_FRIEND_AGGREE;
        }else{
           respdu->uiMsgType=ENUM_MSG_TYPE_ADD_FRIEND_REFUSE;
        }
        m_tcpSocket.write((char*)respdu,respdu->uiPDULen);
        free(respdu);
        respdu = NULL;
        break;
    }
    case ENUM_MSG_TYPE_ADD_FRIEND_RESPOND:{
        QMessageBox::information(this,"添加好友",pdu->caData);
    }
    case ENUM_MSG_TYPE_ADD_FRIEND_AGGREE:{
        char caParName[32]={'\0'};
        memcpy(caParName,pdu->caData,32);
        QMessageBox::information(this,"添加好友",QString("添加%1好友成功").arg(caParName));
        break;
    }
    case ENUM_MSG_TYPE_FLUSH_FRIEND_RESPOND:{
        OpeWidget::getInstance().getFriend()->updateFriendList(pdu);
        break;
    }
    case ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST:{
        char caName[32] = {'\0'};
        memcpy(caName,pdu->caData,32);
        QMessageBox::information(this,"删除好友",QString("%1 删除你作为他的好友").arg(caName));
        break;
    }
    case ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND:{
        QMessageBox::information(this,"删除好友","删除好友成功");
        break;
    }
    case ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST:{
        if(PrivateChat::getInstance().isHidden()){
           PrivateChat::getInstance().show();
        }
        char caSendName[]={'\0'};
        memcpy(caSendName,pdu->caData,32);
        QString strSendName = caSendName;
        PrivateChat::getInstance().setChatName(strSendName);
        PrivateChat::getInstance().updataMsg(pdu);
        break;
    }
    case ENUM_MSG_TYPE_GROUP_CHAT_REQUEST:{
        OpeWidget::getInstance().getFriend()->updateGroupMsg(pdu);
        break;
    }
    case ENUM_MSG_TYPE_CREATE_DIR_RESPOND:{
        QMessageBox::information(this,"创建文件",pdu->caData);
        break;
    }
    case ENUM_MSG_TYPE_FLUSH_FILE_RESPOND:{
        OpeWidget::getInstance().getBook()->updateFileList(pdu);
        QString strEnterDir = OpeWidget::getInstance().getBook()->enterDir();
        if(!strEnterDir.isEmpty()){
           m_strCurPath = m_strCurPath + "/" +strEnterDir;
           qDebug() << "enter dir:"<<m_strCurPath;
        }
        break;
    }
    case ENUM_MSG_TYPE_DEL_DIR_RESPOND:{
        QMessageBox::information(this,"删除文件夹",pdu->caData);
        break;
    }
    case ENUM_MSG_TYPE_RENAME_FILE_RESPOND:{
        QMessageBox::information(this,"重命名文件",pdu->caData);

        break;
    }
    case ENUM_MSG_TYPE_ENTER_DIR_RESPOND:{
        OpeWidget::getInstance().getBook()->cleanEnterDir();
        QMessageBox::information(this,"进入文件夹",pdu->caData);
        break;
    }
    case ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND:{
        QMessageBox::information(this,"文件上传",pdu->caData);
        break;
    }
    case ENUM_MSG_TYPE_DEL_FILE_RESPOND:{
        QMessageBox::information(this,"删除文件",pdu->caData);
        break;
    }
    case ENUM_MSG_TYPE_DOWNLOAD_FILE_RESPOND:{
        qDebug()<<pdu->caData;
        char caFileName[32] = {'\0'};
        sscanf(pdu->caData,"%s%lld",caFileName,&(OpeWidget::getInstance().getBook()->m_iTotal));
        if(strlen(caFileName)>0 && OpeWidget::getInstance().getBook()->m_iTotal>0){
           OpeWidget::getInstance().getBook()->setDownloadStatus(true);
           m_file.setFileName(OpeWidget::getInstance().getBook()->getSaveFilePath());
           if(!m_file.open(QIODevice::WriteOnly)){
               QMessageBox::warning(this,"下载文件","获取保存的文件路径失败");
           }
        }
        break;
    }
    case ENUM_MSG_TYPE_SHARE_FILE_RESPOND:{
        QMessageBox::information(this,"共享文件",pdu->caData);
        break;
    }
    case ENUM_MSG_TYPE_SHARE_FILE_NOTE:{
        qDebug()<<"NOTE---->"<<pdu->caData<<(char*)(pdu->caMsg);
        char *pPath = new char[pdu->uiMsgLen];
        memcpy(pPath,pdu->caMsg,pdu->uiMsgLen);
        char *pos = strrchr(pPath, '/');
        qDebug()<<"pos = "<<pos;
        if(NULL != pos){
           pos++;
           QString strNote = QString("%1 share file->%2 \n Do you accept?").arg(pdu->caData).arg(pos);
           int ret = QMessageBox::question(this,"共享文件",strNote);
           if(QMessageBox::Yes == ret){
               PDU *respdu = mkPDU(pdu->uiMsgLen);
               respdu->uiMsgType = ENUM_MSG_TYPE_SHARE_FILE_NOTE_RESPOND;
               memcpy(respdu->caMsg,pdu->caMsg,pdu->uiMsgLen);
               QString strName = TcpClient::getInstance().loginName();
               strcpy(respdu->caData,strName.toStdString().c_str());
               m_tcpSocket.write((char*)respdu,respdu->uiPDULen);
           }
        }
        break;
    }
    case ENUM_MSG_TYPE_MOVE_FILE_RESPOND:{
        QMessageBox::information(this,"移动文件",pdu->caData);
        break;
    }
    default:
       break;
    }
    free(pdu);
    pdu = NULL;
    }
    else
    {
    QByteArray buffer = m_tcpSocket.readAll();
    m_file.write(buffer);
    Book *pBook = OpeWidget::getInstance().getBook();
    pBook->m_iRecved += buffer.size();
    if(pBook->m_iRecved == pBook->m_iTotal){
       m_file.close();
       pBook->m_iRecved = 0;
       pBook->m_iTotal = 0;
       pBook->setDownloadStatus(false);
       QMessageBox::information(this,"下载文件","下载文件完成");
    }else if(pBook->m_iRecved > pBook->m_iTotal){
       m_file.close();
       pBook->m_iRecved = 0;
       pBook->m_iTotal = 0;
       pBook->setDownloadStatus(false);

       QMessageBox::critical(this,"下载文件","下载文件失败");
    }
    }
}

#if 0
//点击发送
void TcpClient::on_send_pb_clicked()
{
    //获得一个输入框的信息
    QString strMsg = ui->lineEdit->text();
    if(!strMsg.isEmpty()){
       //弹性结构体
       PDU *pdu = mkPDU(strMsg.toUtf8().size()+1);
       pdu->uiMsgType = 8888;
       //数据拷贝
       memcpy(pdu->caMsg,strMsg.toStdString().c_str(),strMsg.toUtf8().size()+1);
       //用tcp发送数据 ，数据封装到协议单元里，再发送
       m_tcpSocket.write((char*)pdu,pdu->uiPDULen);
       free(pdu);
       pdu=NULL;
    }else{
       QMessageBox::warning(this,"消息发送","发送的消息不能为空");
    }

}
#endif

void TcpClient::on_login_pb_clicked(){
    QString strName = ui->name_le->text();//获取用户名
    QString strPwd = ui->pwd_le->text();//获取密码
    if(!strName.isEmpty() && !strPwd.isEmpty()){
       m_strLoginName = strName;
       PDU *pdu = mkPDU(0);
       pdu->uiMsgType = ENUM_MSG_TYPE_LOGIN_REQUEST;
       strncpy(pdu->caData,strName.toStdString().c_str(),32);
       strncpy(pdu->caData+32,strPwd.toStdString().c_str(),32);
       m_tcpSocket.write((char*)pdu,pdu->uiPDULen);
       free(pdu);
       pdu = NULL;
    }else{
       QMessageBox::critical(this,"登录","登录失败：用户名或密码不能为空");
    }
}

//注册请求
//获得数据，如果不为空，产生一个pdu设置它的消息类型，把用户名和密码放到cData,通过tcpSocket发送出去，发送完后，pdu被释放掉
void TcpClient::on_regist_pb_clicked()
{
    QString strName = ui->name_le->text();//获取用户名
    QString strPwd = ui->pwd_le->text();//获取密码
    if(!strName.isEmpty() && !strPwd.isEmpty()){
       PDU *pdu = mkPDU(0);
       pdu->uiMsgType = ENUM_MSG_TYPE_REGIST_REQUEST;
       strncpy(pdu->caData,strName.toStdString().c_str(),32);
       strncpy(pdu->caData+32,strPwd.toStdString().c_str(),32);
       m_tcpSocket.write((char*)pdu,pdu->uiPDULen);
       free(pdu);
       pdu = NULL;
    }else{
       QMessageBox::critical(this,"注册","注册失败：用户名或密码不能为空");
    }

}

void TcpClient::on_cancel_pb_clicked(){

}
