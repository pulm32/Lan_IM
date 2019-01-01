/*
 * 放置在主窗口的好友按钮
 */


#include "friendbutton.h"

FriendButton::FriendButton(Links *tLink,
						   const FriendInformation &theFriend, 
						   const QString &acc, 
						   const QString &name,
						   QWidget *parent)
						   : link(tLink), friInf(theFriend),
						   myAccount(acc), myName(name)
{

	isOpen = false;

	getStatusFromInt(friInf.status, strStatus);
	QString mark;
	if(friInf.remark.isEmpty())
		mark = friInf.name;
	else 
		mark = friInf.remark;

	//创建右键菜单
	creatMenu();
	//设置图标
	setContextMenuPolicy(Qt::CustomContextMenu);
	setIconSize( QSize(AVATAR_SIZE, AVATAR_SIZE) );
	setAutoRaise(TRUE);
	setToolButtonStyle( Qt::ToolButtonTextBesideIcon );

	setButtonStatus();
	connect(this, SIGNAL(clicked()), this, SLOT(clickedFriendButton()));
	connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
		this, SLOT(clickedRightButton(const QPoint &)));
}

FriendButton::~FriendButton()
{

}

void FriendButton::getStatusFromInt(int n, QString &str) const
{
	if(OFFLINE == n)
		str = tr("offline");
	else if(ONLINE == n)
		str = tr("online");
	else if(TALK_WITH_ME == n)
		str = tr("talk");
	else if(BUSY == n)
		str = tr("busy");
	else if(LEAVE == n)
		str = tr("leave");
	else if(DISTURB == n)
		str = tr("disturb");
	else if(STEALTH == n)
		str = tr("stealth");
}

void FriendButton::creatMenu()
{
	menu = new QMenu(this);
	QAction *actDelete = new QAction(tr("Remove this friend"), this);
	QAction *actShow = new QAction(tr("Show his(her) information"), this);
	QAction *actRemark = new QAction(tr("Change remark"), this);

	connect(actDelete, SIGNAL(triggered()),
		this, SLOT(clickedRemoveFriend()));
	connect(actShow, SIGNAL(triggered()), 
		this, SLOT(clickedShowInformation()));
	connect(actRemark, SIGNAL(triggered()), 
		this, SLOT(clickedChangeRemark()));

	menu->addAction(actDelete);
	menu->addAction(actShow);
	menu->addAction(actRemark);
}

void FriendButton::clickedShowInformation()
{
	ShowUserInf *showUser = new ShowUserInf(link, friInf.account, this);
	showUser->show();
}

void FriendButton::clickedChangeRemark()
{
	Message mes;
	mes.kind = CHANGE_REMARK;
	mes.sender = myAccount;
	mes.receiver = friInf.account;
	ChangeRemark *theRemark = new ChangeRemark(link, mes, this);
	connect(theRemark, SIGNAL(changeRemarkSignal(const QString &)),
		this, SLOT(changeRemark(const QString &)));
	theRemark->show();

}

void FriendButton::clickedRemoveFriend()
{
	QMessageBox::StandardButton rb;
	rb = QMessageBox::question(NULL, tr("Remove friend"),  //QString("你确定要删除该好友吗？"),  
		tr("Are you really want to remove the friend?"), 
		QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);
	if(QMessageBox::No == rb)
		return;
	//emit deleteFriendSignal(friInf.account);
	link->deleteFriendRequest(friInf.account);
}

void FriendButton::clickedFriendButton()
{
	openChatRoom();
}

void FriendButton::setButtonStatus()
{
	QString str = QString("pictures/%1.bmp").
		arg(QString::number(friInf.avatarNumber));

	QString text, mark;
	getStatusFromInt(friInf.status, strStatus);
	if(friInf.remark.isEmpty())
		mark = friInf.name;
	else
		mark = friInf.remark;
	if(OFFLINE==friInf.status || STEALTH==friInf.status)
	{
		QPixmap pixmap;
		QIcon icon(str);
		pixmap = icon.pixmap(QSize(AVATAR_SIZE, AVATAR_SIZE), QIcon::Disabled, QIcon::On);
		setIcon(pixmap);
		text = QString("%1 (%2)\n%3").arg(mark).arg(friInf.account).arg(strStatus);
	}
	else
	{
		setIcon( QIcon(str) );
		text = QString("%1(%2)\n%3").arg(mark).arg(friInf.account).arg(strStatus);
	}
	setText(text);
}

void FriendButton::clickedRightButton(const QPoint &point)
{
	menu->exec(QCursor::pos());
}

void FriendButton::openChatRoom()
{
	if(isOpen)
		return;
	isOpen = true;
	room = new Chatroom(link, friInf, myAccount, myName, NULL);
	connect(room, SIGNAL(roomQuitSignal()),  this, SLOT(chatRoomQuit()));
	room->show();
}

void FriendButton::chatRoomQuit()
{
	isOpen = false;
}

void FriendButton::changeRemark(const QString &newRemark)
{
	friInf.remark = newRemark;
	QString text = QString("%1(%2)\n%3").arg(newRemark)
		.arg(friInf.account).arg(strStatus);
	setText(text);
}

void FriendButton::changeStatus(int status)
{
	getStatusFromInt(status, strStatus);
	QString text = QString("%1(%2)\n%3").arg(friInf.remark)
		.arg(friInf.account).arg(strStatus);
	setText(text);
}

void FriendButton::closeChatRoom()
{
	if(isOpen)
	{
		room->close();
		isOpen = false;
	}
}
