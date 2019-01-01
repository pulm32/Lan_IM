/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_windowForm
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QFrame *avatarFrame;
    QTextEdit *textEdit;
    QToolBox *friendToolBox;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *changePwdButton;
    QPushButton *changeInfButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addFriendButton;
    QPushButton *aboutButton;

    void setupUi(QWidget *windowForm)
    {
        if (windowForm->objectName().isEmpty())
            windowForm->setObjectName(QStringLiteral("windowForm"));
        windowForm->resize(255, 515);
        layoutWidget = new QWidget(windowForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 191, 471));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        avatarFrame = new QFrame(layoutWidget);
        avatarFrame->setObjectName(QStringLiteral("avatarFrame"));
        avatarFrame->setMinimumSize(QSize(80, 80));
        avatarFrame->setMaximumSize(QSize(80, 80));
        avatarFrame->setFrameShape(QFrame::StyledPanel);
        avatarFrame->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(avatarFrame);

        textEdit = new QTextEdit(layoutWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(80, 80));
        textEdit->setMaximumSize(QSize(80, 80));

        horizontalLayout_2->addWidget(textEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        friendToolBox = new QToolBox(layoutWidget);
        friendToolBox->setObjectName(QStringLiteral("friendToolBox"));
        friendToolBox->setMinimumSize(QSize(0, 300));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 189, 274));
        friendToolBox->addItem(page_2, QStringLiteral("Page"));

        verticalLayout->addWidget(friendToolBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        changePwdButton = new QPushButton(layoutWidget);
        changePwdButton->setObjectName(QStringLiteral("changePwdButton"));

        horizontalLayout->addWidget(changePwdButton);

        changeInfButton = new QPushButton(layoutWidget);
        changeInfButton->setObjectName(QStringLiteral("changeInfButton"));

        horizontalLayout->addWidget(changeInfButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        addFriendButton = new QPushButton(layoutWidget);
        addFriendButton->setObjectName(QStringLiteral("addFriendButton"));

        horizontalLayout_3->addWidget(addFriendButton);

        aboutButton = new QPushButton(layoutWidget);
        aboutButton->setObjectName(QStringLiteral("aboutButton"));

        horizontalLayout_3->addWidget(aboutButton);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(windowForm);

        friendToolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(windowForm);
    } // setupUi

    void retranslateUi(QWidget *windowForm)
    {
        windowForm->setWindowTitle(QApplication::translate("windowForm", "Form", Q_NULLPTR));
        friendToolBox->setItemText(friendToolBox->indexOf(page_2), QApplication::translate("windowForm", "Page", Q_NULLPTR));
        changePwdButton->setText(QApplication::translate("windowForm", "\344\277\256\346\224\271\345\257\206\347\240\201", Q_NULLPTR));
        changeInfButton->setText(QApplication::translate("windowForm", "\344\277\256\346\224\271\344\277\241\346\201\257", Q_NULLPTR));
        addFriendButton->setText(QApplication::translate("windowForm", "\346\267\273\345\212\240\345\245\275\345\217\213", Q_NULLPTR));
        aboutButton->setText(QApplication::translate("windowForm", "\345\205\263\344\272\216", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class windowForm: public Ui_windowForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
