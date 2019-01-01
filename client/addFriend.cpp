/*
 * addFriend 添加好友
 */

#include "addFriend.h"

AddFriendBox::AddFriendBox(Links *tLink,
						   const QString &myAccount,
						   QWidget *parent/* =0 */)
						   : tempBox(2, parent), link(tLink)
{
	setWindowTitle( tr("add Friend") );
	setFixedSize(200, 150);

	message.kind = REQUEST_FRIEND;
	//发送者是自己（这是废话，呵呵）
	message.sender = myAccount;

	//setLabelName("对方帐号", "验证信息");
	setLabelName(tr("other's account"), tr("Authentication information"));
	connect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}

AddFriendBox::~AddFriendBox()
{
	
}

void AddFriendBox::clickedOKButton()
{
	TempStrings temp;
	temp = getInformation();

	if(temp.one.isEmpty())
	{
		//QMessageBox::critical(this, "ERROR", "对方帐号不能为空");
		QMessageBox::critical(this, tr("Error"),
			tr("The other's account can not be empty"));
		return;
	}

	message.receiver = temp.one;
	message.text = temp.two;
	//好友不能是你自己
	if(message.sender == message.receiver)
	{
		QMessageBox::critical(this, tr("Error"),
			tr("Your friends can't be your own"));
		return;
	}
	link->addFriendRequest(message);
	setAllEnabled(false);
}

void AddFriendBox::result(qint32 replyKind)
{
	if(FRIEDN_NO_ACCOUNT == replyKind)
		//QMessageBox::critical(this, "错误", "没有这个用户名");
		QMessageBox::critical(this, tr("Error"), 
			tr("No this user, please try again"));
	
	else if(ALREAD_FRIENDS == replyKind)
		//QMessageBox::critical(this, "错误", "他（她）们已经是好友了或已经发送了好友请求");
		QMessageBox::critical(this, tr("Error"), 
			tr("They are already good friends or have sended the friend request"));
	else if(FRIEND_REQUESTED == replyKind)
	{
		//QMessageBox::critical(this, "恭喜", "好友请求已经发送，正在等待对方回复");
		QMessageBox::information(this, tr("Congratulations"),
			tr("The friend's requestion have been sended, is waiting for reply"));
		close();
	}
	setAllEnabled(true);
}

void AddFriendBox::closeEvent(QCloseEvent *event)
{
	//因为link的parent不是AddFriendBox，所以不会随着的关闭而断开连接，
	//所以要手动断开连接
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
