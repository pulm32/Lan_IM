/*
 *修改好友备注时所用的窗口
 */

#ifndef REMARK_H_
#define REMARK_H_

#include "constant.h"
#include "tempBox.h"

class ChangeRemark : public tempBox
{
	Q_OBJECT
private:
	Message message;
	Links *link;

protected:
	void closeEvent(QCloseEvent *event);

public:
	ChangeRemark(Links *tLink, const Message &mes,
		QWidget *parent=0);
	~ChangeRemark();

signals:
	void changeRemarkSignal(const QString &newRemark);

	public slots:
		void clickedOKButton();
		void result(qint32 replyKind);
};

#endif
