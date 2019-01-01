/*
 * 主窗口
 */

#include "window.h"
#include "changeInf.h"

Window::Window(const ServerNode &node,
			   const QVector<FriendInformation> &friendsVec,
			   QWidget *parent)
				   : QWidget(parent), serverNode(node)
{
	ui.setupUi(this);
	//设置窗口风格
	Qt::WindowFlags flag = Qt::Window
		| Qt::WindowCloseButtonHint 
		| Qt::WindowMinimizeButtonHint;
	setWindowFlags(flag);
	setFixedSize(250, 500);

	//设置窗口背景
	QPalette pal;
	QPixmap pixmap( QDir::toNativeSeparators
		("pictures/window.jpg") );
	pal.setBrush(QPalette::Window,QBrush(pixmap));
	setPalette(pal);

	//friendsVec[0]是自己的个人资料
	myself = friendsVec[0];

	trayIcon = new QSystemTrayIcon(this);
	link = new Links(serverNode, this);
	setMyInformation();
	createFolder();

	//定义一个组框
	groupBox = new QGroupBox(this);
	layout = new QVBoxLayout(groupBox);
	//设置当前所布局的组件与四周的边界
	layout->setMargin(10);
	//居中对齐
	layout->setAlignment(Qt::AlignTop);

	//创建各个好友按钮
	for(int i=1;i<friendsVec.size();i++)
		addFriendButton(friendsVec[i]);

	//item(0)在Qt designer里删不了，只好在这里手动删除了
	ui.friendToolBox->removeItem(0);
	//增加好友列表
	ui.friendToolBox->addItem( groupBox , tr("my good friends"));

	//检查服务器中有没有储存到发送给自己的信息
	//同时也和服务器建立连接
	link->checkMessageRequest(myself.account);

	//连接各个信号/糟
	connect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
	connect(ui.addFriendButton, SIGNAL(clicked()), 
		this, SLOT(clickedAddFriendButton()));
	connect(ui.aboutButton, SIGNAL(clicked()),
		this, SLOT(clickedAboutButton()));
	connect(ui.changeInfButton, SIGNAL(clicked()),
		this, SLOT(clickedChangeInfButton()));
	connect(ui.changePwdButton, SIGNAL(clicked()),
		this, SLOT(clickedChangePwdButton()));

	connect(link, SIGNAL(disconnectedSignal()), 
		this, SLOT(linkDisconnected()));
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

Window::~Window()
{

}

void Window::closeEvent(QCloseEvent *event)
{
	if(continueToClose())
	{
		//关闭主窗口之前，先关闭所有聊天窗口
		QMap<QString, FriendButton*>::iterator iter;
		for(iter=friButtonMap.begin(); iter!=friButtonMap.end(); ++iter)
			iter.value()->closeChatRoom();
		event->accept();
	}
	else
		event->ignore();
}

bool Window::continueToClose()
{
	int num = 0;
	//如果还有聊天窗口没有关闭，就弹出信息窗口
	QMap<QString, FriendButton*>::iterator iter;
	for(iter=friButtonMap.begin(); iter!=friButtonMap.end(); ++iter)
	{
		if(iter.value()->isRoomOpen())
			num++;
	}
	QString temp;
	if(num != 0)
		temp = tr("There is also") + QString::number(num)
			+ tr(" chat room(s) did not close");
	temp += tr("Do you really want to quit?");
	QMessageBox::StandardButton rb;
	rb = QMessageBox::question(this, tr("Quit"), temp,
		QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
	if(rb == QMessageBox::Yes)
			return true;
	else
		return false;
}

void Window::result(qint32 replyKind)
{
	//处理各种从服务器传回来的信息
	if(TALK == replyKind)
	{
		Message message;
		message = link->getSimpleMessage();
		receivedTalkMessage(message);
	}
	else if(HAVE_MESSAGE == replyKind)
	{
		QVector<Message> messageVec;
		messageVec = link->getMessages();
		int len = messageVec.size();
		for(int i=0;i<len;i++)
			processingMessage(messageVec[i]);
	}
	else if(CHANGE_STATUE == replyKind)
	{
		QString peerAccount;
		qint32 status;
		peerAccount = link->getPeerAccount();
		status = link->getStatus();
		changeFriendStatus(peerAccount, status);
	}
	else if(DELETE_FRIEND_SUCCESS == replyKind)
	{
		QString peerAccount;
		peerAccount = link->getPeerAccount();
		removeFriend(peerAccount);
	}
	else if(GET_FRIEND_SUCCESS == replyKind)
	{
		FriendInformation tFriend;
		tFriend = link->getFriendInformation();
		QMap<QString, FriendButton*>::iterator iter;
		iter = friButtonMap.find(tFriend.account);
		if(iter == friButtonMap.end())
			addFriendButton(tFriend);
	}
	else if(ADD_FRIEND == replyKind)
	{
		Message message;
		message = link->getSimpleMessage();
		processingMessage(message);
	}
	else if(BE_DELETED == replyKind)
	{
		QString account = link->getPeerAccount();
		QString temp = tr("you are deleted by ") + account;
		QMessageBox::information(this, tr("Information"), temp);
		removeFriend(account);
	}

}


void Window::clickedAddFriendButton()
{
	AddFriendBox *box = new AddFriendBox(link, myself.account, NULL);
	box->show();
}

void Window::clickedChangeInfButton()
{
	ChangeInf *change = new ChangeInf(link, myself.account, this);
	change->show();
	//切记，一定要连接信号/糟
	connect(change, SIGNAL(changeInformationSignal(int, QString, QString)),
		this, SLOT(changeInformation(int, QString, QString)));
}

void Window::clickedAboutButton()
{
    //暂时无内容
}


void Window::sendRoomsMessage(const Message &mes)
{
	link->messageRequest(mes);
}

void Window::addFriendButton(const FriendInformation &friInf)
{
	FriendButton *button = new FriendButton(link, friInf, 
		myself.account, myself.name, this);
	layout->addWidget(button);
	friButtonMap.insert(friInf.account, button);
}


void Window::clickedChangePwdButton()
{
	ChangePassword *changePwd = new ChangePassword(link,
		myself.account, this);
	changePwd->show();
}

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	if(QSystemTrayIcon::Trigger == reason)
	{
		trayIcon->showMessage(myself.account, myself.name, 
			QSystemTrayIcon::Information);
	}
}

void Window::createTrayIcon()
{
	trayMap = new QSignalMapper(this);
	connect(trayMap, SIGNAL(mapped(int)), this, SLOT(changeState(int)));

	//创建托盘图标中的各个按钮，并连接信号/糟
	onlineAction = new QAction(tr("online"), this);
	connect(onlineAction, SIGNAL(triggered()), trayMap, SLOT(map()));
	trayMap->setMapping(onlineAction, ONLINE);

	talkAction = new QAction(tr("talk with me"), this);
	connect(talkAction, SIGNAL(triggered()), trayMap, SLOT(map()));
	trayMap->setMapping(talkAction, TALK_WITH_ME);

	busyAction = new QAction(tr("busy"), this);
	connect(busyAction, SIGNAL(triggered()), trayMap, SLOT(map()));
	trayMap->setMapping(busyAction, BUSY);

	leaveAction = new QAction(tr("leave"), this);
	connect(leaveAction, SIGNAL(triggered()), trayMap, SLOT(map()));
	trayMap->setMapping(leaveAction, LEAVE);

	disturbAction = new QAction(tr("disturb"), this);
	connect(disturbAction, SIGNAL(triggered()), trayMap, SLOT(map()));
	trayMap->setMapping(disturbAction, DISTURB);

	stealthAction = new QAction(tr("stealth"), this);
	connect(stealthAction, SIGNAL(triggered()), trayMap, SLOT(map()));
	trayMap->setMapping(stealthAction, STEALTH);

	quitAction = new QAction(tr("quit"), this);
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

	trayIconMenu = new QMenu(this);
	//将各个按钮加入到托盘菜单中
	trayIconMenu->addAction(onlineAction);
	trayIconMenu->addAction(talkAction);
	trayIconMenu->addAction(busyAction);
	trayIconMenu->addAction(leaveAction);
	trayIconMenu->addAction(disturbAction);
	trayIconMenu->addAction(stealthAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);
	trayIcon->setContextMenu(trayIconMenu);
}

void Window::changeState(int n)
{
	myself.status = n;
	QString tStatus, title;
	setStatusFromInt(myself.status, tStatus);
	title = QString("%1(%2)").arg(myself.account).arg(tStatus);
	setWindowTitle(title);
	link->changeStatusRequest(myself.account, n);
}

void Window::setStatusFromInt(int n, QString &str) const
{
	if(ONLINE == n)
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

void Window::setButtonStatus(const FriendInformation &friInf, QToolButton *button)
{
	QString str = QString("pictures/%1.bmp").
		arg(QString::number(friInf.avatarNumber));

	QString text, mark, tStatus;
	setStatusFromInt(friInf.status, tStatus);
	if(friInf.remark.isEmpty())
		mark = friInf.name;
	else
		mark = friInf.remark;

	//如果对方离线或隐身，就将他们的图标设为黑白
	if(OFFLINE==friInf.status || STEALTH==friInf.status)
	{
		QPixmap pixmap;
		QIcon icon(str);
		pixmap = icon.pixmap(QSize(AVATAR_SIZE, AVATAR_SIZE), QIcon::Disabled, QIcon::On);
		button->setIcon(pixmap);
		text = QString("%1\n(%2)").arg(mark).arg(friInf.account);
	}
	else
	{
		button->setIcon( QIcon(str) );
		text = QString("%1(%2)\n%3").arg(mark).arg(tStatus).arg(friInf.account);
	}
	button->setText(text);
}

void Window::processingMessage(const Message &mes)
{
	if(TALK_MESSAGE == mes.kind)
		receivedTalkMessage(mes);
	else if(REQUEST_FRIEND == mes.kind)
		replyAddFriend(mes);
	else if(DISAGREE_FRIEND == mes.kind)
	{
		QMessageBox::information(this, tr("message"), 
			mes.sender + tr(" disagreed your friend question"));
	}
	else if(AGREE_FRIEND == mes.kind)
	{
		QMessageBox::information(this, tr("message"), 
			mes.sender + tr("agreed your friend question"));
		link->getFriendRequest(mes.sender);
	}
	else if(BE_DELETED == mes.kind)
	{
		QString temp = tr("you are deleted by ") + mes.sender;
		QMessageBox::information(this, tr("Information"), temp);
		removeFriend(mes.sender);
	}

}

void Window::changeFriendStatus(const QString &acc, qint32 status)
{
	QMap<QString, FriendButton*>::iterator iter;
	iter = friButtonMap.find(acc);

	//如果好友列表中不存在这个人，就直接返回
	if(friButtonMap.end() == iter)
		return;

	iter.value()->getInformation().status = status;
	iter.value()->setButtonStatus();
}

void Window::setMyInformation()
{
	//设置程序图标，标题
	QString tIcon = QString("pictures/%1.bmp").
		arg(QString::number(myself.avatarNumber));
	QIcon icon = QIcon(tIcon);
	setWindowIcon(icon);
	QString tStatus, title;
	setStatusFromInt(myself.status, tStatus);
	title = QString("%1(%2)").arg(myself.account).arg(tStatus);
	setWindowTitle(title);

	//设置自己的头像
	ui.avatarFrame->setObjectName("avatar");
	QString str = QString("QFrame#avatar{border-image:url(pictures/%1.bmp)}")
		.arg(QString::number(myself.avatarNumber));
	ui.avatarFrame->setStyleSheet(str);

	ui.textEdit->setText(myself.about);
	ui.textEdit->setReadOnly(true);

	//设置托盘图标
	trayIcon->setIcon(icon);
	createTrayIcon();
	trayIcon->show();
}

void Window::changeInformation(int avaNum, QString name, QString about)
{
	myself.avatarNumber = avaNum;
	myself.name = name;
	myself.about = about;
	setMyInformation();
}

void Window::removeFriend(const QString &peerAccount)
{
	QMap<QString, FriendButton*>::iterator iter;
	iter = friButtonMap.find(peerAccount);
	//如果该好友不存在，就直接返回
	if(friButtonMap.end() == iter)
		return;

	iter.value()->closeChatRoom();
	layout->removeWidget(iter.value());
	iter.value()->deleteLater();
	friButtonMap.erase(iter);
}

void Window::receivedTalkMessage(const Message &mes)
{
	QMap<QString, FriendButton*>::iterator iter;
	iter = friButtonMap.find(mes.sender);
	if(friButtonMap.end() == iter)
		return;

	//打开聊天窗口，并显示对方发来的信息
	iter.value()->openChatRoom();
	iter.value()->getRoomPoint()->setOutputLine(mes);
}

void Window::replyAddFriend(const Message &tMessage)
{
	Message mes = tMessage;
	QMessageBox::StandardButton rb;
	//QString("用户%1想加你为好友，是否同意？\n验证信息：%2")
	QString temp = tr("Do you agree make friends with ") + mes.sender
		+ tr("?\nAuthentication information: ") + mes.text;
	rb = QMessageBox::question(NULL, tr("friend request"), temp,  
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Close,  QMessageBox::Yes); 

	if(QMessageBox::Close == rb)
		return;
	else if(QMessageBox::Yes == rb)
		mes.kind = AGREE_FRIEND;
	else if(QMessageBox::No == rb)
		mes.kind = DISAGREE_FRIEND;

	mes.sender = tMessage.receiver;
	mes.receiver = tMessage.sender;
	link->addFriendRequest(mes);
}

void Window::createFolder() const
{
	//创建“save/(自己帐号）”这个文件夹（如果没有的话）
	//用于储存设置和聊天信息
	QDir tempDir;
	if(!tempDir.exists("save"))
		tempDir.mkdir("save");
	tempDir.cd("save");
	if(!tempDir.exists(myself.account))
        tempDir.mkdir(myself.account);
}

void Window::linkDisconnected()
{
    //程序如果和服务器断开连接的话，弹出警告，直接退出
    QMessageBox::critical(this, tr("error"),
        tr("Because of network problems, the client is disconnected with the server"
		"Please quit now"));
	qApp->quit();
}
