/********************************************************************************
** Form generated from reading UI file 'loginBox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINBOX_H
#define UI_LOGINBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginBoxForm
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *ipLabel;
    QLineEdit *ipLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *portLineEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *idLabel;
    QLineEdit *accountLineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_2;
    QLabel *statusLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *connectionPushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *registerPushButton;
    QPushButton *loginPushButton;

    void setupUi(QWidget *loginBoxForm)
    {
        if (loginBoxForm->objectName().isEmpty())
            loginBoxForm->setObjectName(QStringLiteral("loginBoxForm"));
        loginBoxForm->resize(407, 332);
        layoutWidget = new QWidget(loginBoxForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 30, 321, 271));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        ipLabel = new QLabel(layoutWidget);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));

        horizontalLayout_3->addWidget(ipLabel);

        ipLineEdit = new QLineEdit(layoutWidget);
        ipLineEdit->setObjectName(QStringLiteral("ipLineEdit"));

        horizontalLayout_3->addWidget(ipLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        portLineEdit = new QLineEdit(layoutWidget);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));

        horizontalLayout_4->addWidget(portLineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        idLabel = new QLabel(layoutWidget);
        idLabel->setObjectName(QStringLiteral("idLabel"));

        horizontalLayout_5->addWidget(idLabel);

        accountLineEdit = new QLineEdit(layoutWidget);
        accountLineEdit->setObjectName(QStringLiteral("accountLineEdit"));

        horizontalLayout_5->addWidget(accountLineEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        passwordLabel = new QLabel(layoutWidget);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));

        horizontalLayout_6->addWidget(passwordLabel);

        passwordLineEdit = new QLineEdit(layoutWidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));

        horizontalLayout_6->addWidget(passwordLineEdit);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        statusLabel = new QLabel(layoutWidget);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));

        verticalLayout->addWidget(statusLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        connectionPushButton = new QPushButton(layoutWidget);
        connectionPushButton->setObjectName(QStringLiteral("connectionPushButton"));

        horizontalLayout->addWidget(connectionPushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        registerPushButton = new QPushButton(layoutWidget);
        registerPushButton->setObjectName(QStringLiteral("registerPushButton"));

        horizontalLayout->addWidget(registerPushButton);

        loginPushButton = new QPushButton(layoutWidget);
        loginPushButton->setObjectName(QStringLiteral("loginPushButton"));

        horizontalLayout->addWidget(loginPushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(loginBoxForm);

        QMetaObject::connectSlotsByName(loginBoxForm);
    } // setupUi

    void retranslateUi(QWidget *loginBoxForm)
    {
        loginBoxForm->setWindowTitle(QApplication::translate("loginBoxForm", "Form", Q_NULLPTR));
        ipLabel->setText(QApplication::translate("loginBoxForm", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("loginBoxForm", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\357\274\232", Q_NULLPTR));
        idLabel->setText(QApplication::translate("loginBoxForm", "\345\270\220\345\217\267\357\274\232", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("loginBoxForm", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        statusLabel->setText(QApplication::translate("loginBoxForm", "TextLabel", Q_NULLPTR));
        connectionPushButton->setText(QApplication::translate("loginBoxForm", "\350\277\236\346\216\245", Q_NULLPTR));
        registerPushButton->setText(QApplication::translate("loginBoxForm", "\346\263\250\345\206\214", Q_NULLPTR));
        loginPushButton->setText(QApplication::translate("loginBoxForm", "\347\231\273\345\275\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class loginBoxForm: public Ui_loginBoxForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINBOX_H
