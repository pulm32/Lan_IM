/********************************************************************************
** Form generated from reading UI file 'informationBox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORMATIONBOX_H
#define UI_INFORMATIONBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_informationBoxForm
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_10;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QLabel *LoginLabel;
    QLineEdit *accountLineEdit;
    QLabel *label_2;
    QLineEdit *passwordLineEdit;
    QLabel *label_3;
    QLineEdit *confirmPwdLineEdit;
    QLabel *label_4;
    QLineEdit *nicknameLineEdit;
    QGridLayout *gridLayout_2;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QFrame *avatarFrame;
    QLabel *avatarLabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pastButton;
    QPushButton *nextButton;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *mobileNumLineEdit;
    QLabel *label_7;
    QLineEdit *phoneNumLineEdit;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *cityLineEdit;
    QTextEdit *aboutTextEdit;
    QLineEdit *birthdayLineEdit;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *helpPushButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *quitPushButton;
    QPushButton *OKPushButton;

    void setupUi(QWidget *informationBoxForm)
    {
        if (informationBoxForm->objectName().isEmpty())
            informationBoxForm->setObjectName(QStringLiteral("informationBoxForm"));
        informationBoxForm->setWindowModality(Qt::NonModal);
        informationBoxForm->setEnabled(true);
        informationBoxForm->resize(483, 607);
        layoutWidget = new QWidget(informationBoxForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 20, 415, 576));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_3->addWidget(label_10);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        LoginLabel = new QLabel(layoutWidget);
        LoginLabel->setObjectName(QStringLiteral("LoginLabel"));

        verticalLayout->addWidget(LoginLabel);

        accountLineEdit = new QLineEdit(layoutWidget);
        accountLineEdit->setObjectName(QStringLiteral("accountLineEdit"));

        verticalLayout->addWidget(accountLineEdit);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        passwordLineEdit = new QLineEdit(layoutWidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));

        verticalLayout->addWidget(passwordLineEdit);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        confirmPwdLineEdit = new QLineEdit(layoutWidget);
        confirmPwdLineEdit->setObjectName(QStringLiteral("confirmPwdLineEdit"));

        verticalLayout->addWidget(confirmPwdLineEdit);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        nicknameLineEdit = new QLineEdit(layoutWidget);
        nicknameLineEdit->setObjectName(QStringLiteral("nicknameLineEdit"));

        verticalLayout->addWidget(nicknameLineEdit);


        gridLayout_3->addLayout(verticalLayout, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        avatarFrame = new QFrame(layoutWidget);
        avatarFrame->setObjectName(QStringLiteral("avatarFrame"));
        avatarFrame->setMinimumSize(QSize(80, 80));
        avatarFrame->setMaximumSize(QSize(80, 80));
        avatarFrame->setFrameShape(QFrame::StyledPanel);
        avatarFrame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(avatarFrame);

        avatarLabel = new QLabel(layoutWidget);
        avatarLabel->setObjectName(QStringLiteral("avatarLabel"));

        verticalLayout_2->addWidget(avatarLabel);


        gridLayout_2->addLayout(verticalLayout_2, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pastButton = new QPushButton(layoutWidget);
        pastButton->setObjectName(QStringLiteral("pastButton"));

        horizontalLayout->addWidget(pastButton);

        nextButton = new QPushButton(layoutWidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));

        horizontalLayout->addWidget(nextButton);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 3);


        gridLayout_3->addLayout(gridLayout_2, 1, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_3);

        verticalSpacer = new QSpacerItem(356, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 2);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        mobileNumLineEdit = new QLineEdit(layoutWidget);
        mobileNumLineEdit->setObjectName(QStringLiteral("mobileNumLineEdit"));

        gridLayout->addWidget(mobileNumLineEdit, 1, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        phoneNumLineEdit = new QLineEdit(layoutWidget);
        phoneNumLineEdit->setObjectName(QStringLiteral("phoneNumLineEdit"));

        gridLayout->addWidget(phoneNumLineEdit, 2, 1, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 3, 0, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 4, 0, 1, 1);

        cityLineEdit = new QLineEdit(layoutWidget);
        cityLineEdit->setObjectName(QStringLiteral("cityLineEdit"));

        gridLayout->addWidget(cityLineEdit, 4, 1, 1, 1);

        aboutTextEdit = new QTextEdit(layoutWidget);
        aboutTextEdit->setObjectName(QStringLiteral("aboutTextEdit"));
        aboutTextEdit->setMinimumSize(QSize(0, 0));
        aboutTextEdit->setMaximumSize(QSize(16777215, 80));

        gridLayout->addWidget(aboutTextEdit, 5, 1, 1, 1);

        birthdayLineEdit = new QLineEdit(layoutWidget);
        birthdayLineEdit->setObjectName(QStringLiteral("birthdayLineEdit"));

        gridLayout->addWidget(birthdayLineEdit, 3, 1, 1, 1);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 5, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        helpPushButton = new QPushButton(layoutWidget);
        helpPushButton->setObjectName(QStringLiteral("helpPushButton"));

        horizontalLayout_2->addWidget(helpPushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        quitPushButton = new QPushButton(layoutWidget);
        quitPushButton->setObjectName(QStringLiteral("quitPushButton"));

        horizontalLayout_2->addWidget(quitPushButton);

        OKPushButton = new QPushButton(layoutWidget);
        OKPushButton->setObjectName(QStringLiteral("OKPushButton"));

        horizontalLayout_2->addWidget(OKPushButton);


        verticalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(informationBoxForm);

        QMetaObject::connectSlotsByName(informationBoxForm);
    } // setupUi

    void retranslateUi(QWidget *informationBoxForm)
    {
        informationBoxForm->setWindowTitle(QApplication::translate("informationBoxForm", "Form", Q_NULLPTR));
        label_10->setText(QApplication::translate("informationBoxForm", "\346\217\220\347\244\272\357\274\232\346\263\250\345\206\214\344\271\213\345\211\215\357\274\214\350\257\267\345\205\210\351\230\205\350\257\273\345\270\256\345\212\251\345\206\205\347\232\204\346\240\274\345\274\217\350\246\201\346\261\202\357\274\214\350\260\242\350\260\242\343\200\202", Q_NULLPTR));
        label->setText(QApplication::translate("informationBoxForm", "\345\277\205\345\241\253\345\206\205\345\256\271------------------------------------------------", Q_NULLPTR));
        LoginLabel->setText(QApplication::translate("informationBoxForm", "\345\270\220\345\217\267\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("informationBoxForm", "\350\276\223\345\205\245\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("informationBoxForm", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("informationBoxForm", "\345\221\242\347\247\260\357\274\232", Q_NULLPTR));
        label_11->setText(QApplication::translate("informationBoxForm", "\351\200\211\346\213\251\345\244\264\345\203\217\357\274\232", Q_NULLPTR));
        avatarLabel->setText(QApplication::translate("informationBoxForm", "TextLabel", Q_NULLPTR));
        pastButton->setText(QApplication::translate("informationBoxForm", "\344\270\212\344\270\200\345\274\240", Q_NULLPTR));
        nextButton->setText(QApplication::translate("informationBoxForm", "\344\270\213\344\270\200\345\274\240", Q_NULLPTR));
        label_5->setText(QApplication::translate("informationBoxForm", "\351\200\211\345\241\253\345\206\205\345\256\271\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215\357\274\215", Q_NULLPTR));
        label_6->setText(QApplication::translate("informationBoxForm", "\346\211\213\346\234\272\345\217\267\347\240\201\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("informationBoxForm", "\347\224\265\350\257\235\345\217\267\347\240\201\357\274\232", Q_NULLPTR));
        label_8->setText(QApplication::translate("informationBoxForm", "\347\224\237\346\227\245\357\274\232", Q_NULLPTR));
        label_9->setText(QApplication::translate("informationBoxForm", "\345\237\216\345\270\202\357\274\232", Q_NULLPTR));
        label_12->setText(QApplication::translate("informationBoxForm", "\344\270\252\344\272\272\346\217\217\350\277\260\357\274\232", Q_NULLPTR));
        helpPushButton->setText(QApplication::translate("informationBoxForm", "\345\270\256\345\212\251", Q_NULLPTR));
        quitPushButton->setText(QApplication::translate("informationBoxForm", "\345\217\226\346\266\210", Q_NULLPTR));
        OKPushButton->setText(QApplication::translate("informationBoxForm", "\345\256\214\346\210\220", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class informationBoxForm: public Ui_informationBoxForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONBOX_H
