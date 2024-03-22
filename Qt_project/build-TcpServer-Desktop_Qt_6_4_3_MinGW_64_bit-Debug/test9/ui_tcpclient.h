/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpClient
{
public:
    QWidget *widget_5;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *name_lan;
    QLineEdit *name_le;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *pwd_lab;
    QLineEdit *pwd_le;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QPushButton *login_pb;
    QPushButton *regist_pb;
    QPushButton *cancel_pb;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *TcpClient)
    {
        if (TcpClient->objectName().isEmpty())
            TcpClient->setObjectName("TcpClient");
        TcpClient->resize(600, 220);
        TcpClient->setMinimumSize(QSize(300, 220));
        TcpClient->setMaximumSize(QSize(600, 220));
        widget_5 = new QWidget(TcpClient);
        widget_5->setObjectName("widget_5");
        widget_5->setGeometry(QRect(10, 0, 581, 201));
        gridLayout = new QGridLayout(widget_5);
        gridLayout->setObjectName("gridLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        widget_4 = new QWidget(widget_5);
        widget_4->setObjectName("widget_4");
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget = new QWidget(widget_4);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        name_lan = new QLabel(widget);
        name_lan->setObjectName("name_lan");
        QFont font;
        font.setFamilies({QString::fromUtf8("\344\273\277\345\256\213")});
        font.setPointSize(16);
        font.setUnderline(false);
        name_lan->setFont(font);

        horizontalLayout->addWidget(name_lan);

        name_le = new QLineEdit(widget);
        name_le->setObjectName("name_le");
        name_le->setMinimumSize(QSize(200, 30));
        name_le->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(name_le);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pwd_lab = new QLabel(widget_2);
        pwd_lab->setObjectName("pwd_lab");
        pwd_lab->setFont(font);

        horizontalLayout_2->addWidget(pwd_lab);

        pwd_le = new QLineEdit(widget_2);
        pwd_le->setObjectName("pwd_le");
        pwd_le->setMinimumSize(QSize(200, 30));
        pwd_le->setFrame(true);
        pwd_le->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(pwd_le);


        verticalLayout_2->addWidget(widget_2);


        gridLayout->addWidget(widget_4, 2, 1, 1, 1);

        widget_3 = new QWidget(widget_5);
        widget_3->setObjectName("widget_3");
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setObjectName("verticalLayout");
        login_pb = new QPushButton(widget_3);
        login_pb->setObjectName("login_pb");

        verticalLayout->addWidget(login_pb);

        regist_pb = new QPushButton(widget_3);
        regist_pb->setObjectName("regist_pb");

        verticalLayout->addWidget(regist_pb);

        cancel_pb = new QPushButton(widget_3);
        cancel_pb->setObjectName("cancel_pb");

        verticalLayout->addWidget(cancel_pb);


        gridLayout->addWidget(widget_3, 2, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 1);


        retranslateUi(TcpClient);

        QMetaObject::connectSlotsByName(TcpClient);
    } // setupUi

    void retranslateUi(QWidget *TcpClient)
    {
        TcpClient->setWindowTitle(QCoreApplication::translate("TcpClient", "TcpClient", nullptr));
        name_lan->setText(QCoreApplication::translate("TcpClient", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        pwd_lab->setText(QCoreApplication::translate("TcpClient", "\345\257\206  \347\240\201\357\274\232", nullptr));
        login_pb->setText(QCoreApplication::translate("TcpClient", "\347\231\273\345\275\225", nullptr));
        regist_pb->setText(QCoreApplication::translate("TcpClient", "\346\263\250\345\206\214", nullptr));
        cancel_pb->setText(QCoreApplication::translate("TcpClient", "\346\263\250\351\224\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpClient: public Ui_TcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
