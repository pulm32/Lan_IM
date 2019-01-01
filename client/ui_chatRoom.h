/********************************************************************************
** Form generated from reading UI file 'chatRoom.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOM_H
#define UI_CHATROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "inputtextedit.h"

QT_BEGIN_NAMESPACE

class Ui_chatroomWidget
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *outputTextEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *FontsPushButton;
    QPushButton *colorPushButton;
    QPushButton *recordPushButton;
    InputTextEdit *inputTextEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *closePushButton;
    QPushButton *sendPushButton;
    QVBoxLayout *verticalLayout;
    QFrame *avatarFrame;
    QLabel *label;
    QTextEdit *aboutTextEdit;

    void setupUi(QWidget *chatroomWidget)
    {
        if (chatroomWidget->objectName().isEmpty())
            chatroomWidget->setObjectName(QStringLiteral("chatroomWidget"));
        chatroomWidget->resize(461, 423);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chatroomWidget->sizePolicy().hasHeightForWidth());
        chatroomWidget->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(chatroomWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        outputTextEdit = new QTextEdit(chatroomWidget);
        outputTextEdit->setObjectName(QStringLiteral("outputTextEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(80);
        sizePolicy1.setHeightForWidth(outputTextEdit->sizePolicy().hasHeightForWidth());
        outputTextEdit->setSizePolicy(sizePolicy1);
        outputTextEdit->setMinimumSize(QSize(0, 0));

        verticalLayout_2->addWidget(outputTextEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        FontsPushButton = new QPushButton(chatroomWidget);
        FontsPushButton->setObjectName(QStringLiteral("FontsPushButton"));

        horizontalLayout->addWidget(FontsPushButton);

        colorPushButton = new QPushButton(chatroomWidget);
        colorPushButton->setObjectName(QStringLiteral("colorPushButton"));

        horizontalLayout->addWidget(colorPushButton);

        recordPushButton = new QPushButton(chatroomWidget);
        recordPushButton->setObjectName(QStringLiteral("recordPushButton"));

        horizontalLayout->addWidget(recordPushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        inputTextEdit = new InputTextEdit(chatroomWidget);
        inputTextEdit->setObjectName(QStringLiteral("inputTextEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(100);
        sizePolicy2.setVerticalStretch(20);
        sizePolicy2.setHeightForWidth(inputTextEdit->sizePolicy().hasHeightForWidth());
        inputTextEdit->setSizePolicy(sizePolicy2);
        inputTextEdit->setMinimumSize(QSize(0, 80));
        inputTextEdit->setMaximumSize(QSize(16777215, 80));

        verticalLayout_2->addWidget(inputTextEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        closePushButton = new QPushButton(chatroomWidget);
        closePushButton->setObjectName(QStringLiteral("closePushButton"));

        horizontalLayout_2->addWidget(closePushButton);

        sendPushButton = new QPushButton(chatroomWidget);
        sendPushButton->setObjectName(QStringLiteral("sendPushButton"));

        horizontalLayout_2->addWidget(sendPushButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        avatarFrame = new QFrame(chatroomWidget);
        avatarFrame->setObjectName(QStringLiteral("avatarFrame"));
        avatarFrame->setMinimumSize(QSize(100, 100));
        avatarFrame->setMaximumSize(QSize(100, 100));
        avatarFrame->setFrameShape(QFrame::StyledPanel);
        avatarFrame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(avatarFrame);

        label = new QLabel(chatroomWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        aboutTextEdit = new QTextEdit(chatroomWidget);
        aboutTextEdit->setObjectName(QStringLiteral("aboutTextEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(100);
        sizePolicy3.setHeightForWidth(aboutTextEdit->sizePolicy().hasHeightForWidth());
        aboutTextEdit->setSizePolicy(sizePolicy3);
        aboutTextEdit->setMinimumSize(QSize(120, 200));
        aboutTextEdit->setMaximumSize(QSize(120, 1000));

        verticalLayout->addWidget(aboutTextEdit);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(chatroomWidget);

        QMetaObject::connectSlotsByName(chatroomWidget);
    } // setupUi

    void retranslateUi(QWidget *chatroomWidget)
    {
        chatroomWidget->setWindowTitle(QApplication::translate("chatroomWidget", "Form", Q_NULLPTR));
        FontsPushButton->setText(QApplication::translate("chatroomWidget", "\350\256\276\347\275\256\345\255\227\344\275\223", Q_NULLPTR));
        colorPushButton->setText(QApplication::translate("chatroomWidget", "\350\256\276\347\275\256\351\242\234\350\211\262", Q_NULLPTR));
        recordPushButton->setText(QApplication::translate("chatroomWidget", "\350\201\212\345\244\251\350\256\260\345\275\225", Q_NULLPTR));
        closePushButton->setText(QApplication::translate("chatroomWidget", "\345\205\263\351\227\255", Q_NULLPTR));
        sendPushButton->setText(QApplication::translate("chatroomWidget", "\345\217\221\351\200\201", Q_NULLPTR));
        label->setText(QApplication::translate("chatroomWidget", "\346\217\220\347\244\272\357\274\232\n"
"\346\214\211\344\270\213Ctrl+Enter\n"
"\345\217\257\344\273\245\347\233\264\346\216\245\345\217\221\351\200\201\344\277\241\346\201\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class chatroomWidget: public Ui_chatroomWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOM_H
