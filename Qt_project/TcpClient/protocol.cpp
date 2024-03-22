#include<protocol.h>

//协议动态空间申请
PDU *mkPDU(uint uiMsgLen)
{
    //总的PDU大小
    uint uiPDULen = sizeof(PDU)+uiMsgLen;
    //转化
    PDU *pdu = (PDU*)malloc(uiPDULen);
    //如果PDU空间申请失败，则结束程序
    if(NULL == pdu){
        exit(EXIT_FAILURE);
    }
    //清空
    memset(pdu,0,uiPDULen);
    //动态PDU
    pdu->uiPDULen=uiPDULen;
    //实际消息的大小
    pdu->uiMsgLen=uiMsgLen;
    //把空间的地址返回出去
    return pdu;
}
