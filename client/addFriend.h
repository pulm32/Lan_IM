/*
 * addFriend 添加好友
 */

#ifndef ADDFRIEND_H_
#define ADDFRIEND_H_

#include "constant.h"
#include "tempBox.h"
#include "links.h"

//要添加好友时弹出的对话框
class AddFriendBox : public tempBox
{
	Q_OBJECT
private:
	Message message;
	Links *link;

protected:
	void closeEvent(QCloseEvent *event);

public:
	AddFriendBox(Links *tLink,
		const QString &myAccount, QWidget *parent=0);
	~AddFriendBox();

	public slots:
		void clickedOKButton();
		void result(qint32 replyKind);					
};

#endif

