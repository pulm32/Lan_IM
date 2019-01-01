/*
 * 要修改密码时弹出的窗口
 */

#ifndef CHANGEPWD_H_
#define CHANGEPWD_H_

#include "constant.h"
#include "tempBox.h"
#include "links.h"


class ChangePassword : public tempBox
{
	Q_OBJECT
private:
	QString account;				//自己的帐号
	Links *link;

protected:
	void closeEvent(QCloseEvent *event);

public:
	ChangePassword(Links *tLink,
		const QString &acc, QWidget *parent=0);
	~ChangePassword();

	public slots:
		void result(qint32 replyKind);
		void clickedOKButton();
};

#endif
