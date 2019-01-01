/*
 * 放置在主窗口的好友按钮
 */

#ifndef FRIENDBUTTON_H_
#define FRIENDBUTTON_H_

#include "constant.h"
#include "links.h"
#include "chatRoom.h"
#include "addFriend.h"
#include "showUserInf.h"
#include "changeInf.h"
#include "remark.h"
#include "changePwd.h"
#include <QToolButton>
#include <QMenu>


class FriendButton : public QToolButton
{
	Q_OBJECT
private:
	//我自已的信息
	QString myAccount;
	QString myName;
	//以字符串形式储存好友信息
	QString strStatus;
	//好友信息
	FriendInformation friInf;
	//聊天窗口是否打开了
	bool isOpen;

	Links *link;
	//指向聊天窗口的指针
	Chatroom *room;
	//右键菜单
	QMenu *menu;

	//将好友状态从数字形式转换为字符串形式
	void getStatusFromInt(int n, QString &str) const;
	//创建右键菜单
	void creatMenu();

public:
	FriendButton(Links *tLink, const FriendInformation &theFriend, 
		const QString &acc, const QString &name, QWidget *parent=0);
	~FriendButton();
	//打开聊天窗口
	void openChatRoom();
	//设置好友按钮的状态
	void setButtonStatus();
	//关闭聊天窗口
	void closeChatRoom();

	bool isRoomOpen() const
	{	return isOpen;	}
	Chatroom *getRoomPoint() const
	{	return room;	}
	FriendInformation &getInformation()
	{	return friInf;	}
	FriendInformation getInformation() const
	{	return friInf;	}

signals:
	void deleteFriendSignal(const QString &peerAccount);

	public slots:
		//左键点击按键
		void clickedFriendButton();
		//右键点击按键
		void clickedRightButton(const QPoint &);
		//显示好友详细信息
		void clickedShowInformation();
		//点击修改好友备注按键
		void clickedChangeRemark();
		//删除好友
		void clickedRemoveFriend();
		//聊天窗口关闭了
		void chatRoomQuit();
		//修改好友状态
		void changeRemark(const QString &newRemark);
		void changeStatus(int status);
};

#endif
