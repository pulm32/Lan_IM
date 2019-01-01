/*
 * 程序的主窗口
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "constant.h"
#include "friendbutton.h"
#include "ui_window.h"
#include <QGroupBox>
#include <QSystemTrayIcon>

class Window : public QWidget
{
	Q_OBJECT
private:
	Ui::windowForm ui;
	Links *link;
	ServerNode serverNode;
	FriendInformation myself;
	QVBoxLayout *layout;
	QGroupBox *groupBox;
	UserInformation userInf;
	QMap<QString, FriendButton*> friButtonMap;

	//询问用户是否真的要退出
	bool continueToClose();

	//创建文件夹，用于记录设置和聊天记录
	void createFolder() const;

	//创建托盘图标
	void createTrayIcon();

	//设置我自己的个人信息
	void setMyInformation();

	//添加好友按钮
	void addFriendButton(const FriendInformation &friInf);

	//改变好友的状态
	void changeFriendStatus(const QString &acc, qint32 status);

	//将某个好友从列表中删除
	void deleteFromTable(const QString &acc);

	//将状态值转换成字符串形式
	void setStatusFromInt(int n, QString &str) const;

	//设置好友按钮图标的状态
	void setButtonStatus(const FriendInformation &friInf, QToolButton *button);

	//处理信息
	void processingMessage(const Message &mes);
	void receivedTalkMessage(const Message &mes);
	void replyAddFriend(const Message &tMessage);

	//托盘图标和它的按钮
	QSystemTrayIcon *trayIcon;
	QAction *onlineAction;
	QAction *talkAction;
	QAction *busyAction;
	QAction *leaveAction;
	QAction *disturbAction;
	QAction *stealthAction;
	QAction *quitAction;
	QMenu *trayIconMenu;
	QSignalMapper *trayMap;
	
protected:
	void closeEvent(QCloseEvent *event);

public:
	Window(const ServerNode &node, 
		const QVector<FriendInformation> &friendsVec,
		QWidget *parent=0);
	~Window();

	public slots:
		void result(qint32 replyKind);
		void clickedAddFriendButton();
		void clickedChangeInfButton();
		void clickedChangePwdButton();
		void clickedAboutButton();
		void sendRoomsMessage(const Message &mes);
		void changeState(int n);
		void changeInformation(int avaNum, 
			QString name, QString about);
		void removeFriend(const QString &peerAccount);

		void iconActivated(QSystemTrayIcon::ActivationReason reason);
		void linkDisconnected();
};

#endif
