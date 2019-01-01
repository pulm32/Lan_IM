/*
 * 登录窗口
 */
#ifndef LOGINBOX_H_
#define LOGINBOX_H_

#include "constant.h"
#include "links.h"
#include "register.h"
#include "window.h"
#include "ui_loginBox.h"


class LoginBox : public QWidget
{
	Q_OBJECT
private:
	Ui::loginBoxForm ui;
	ServerNode serverNode;
	LoginInformation logInf;		//储存登录信息
	Links *link;
	//获取登录信息
	bool getString(QString &str, QLineEdit *edit, const QString &message);

public:
	LoginBox(QWidget *parent = 0);
	~LoginBox();

	public slots:
		void result(qint32 replyKind);
		void checkConnectionButton();
		void clickedRegisterButton();
		void clickedLoginButton();	

		//设置用户登录状态
		void setStatus(const QString &statusStr);
		//和服务器断开连接了
		void ServerDisconnected();
		//初始化状态
		void initStatus();
		//连接建立后的状态
		void connectedStatus();
};

#endif
