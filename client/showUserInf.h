/*
 * 显示好友详细信息时所用的窗口
 */

#ifndef SHOWUSERINF_H_
#define SHOWUSERINF_H_

#include "constant.h"
#include "informationBox.h"

class ShowUserInf : public InformationBox
{
	Q_OBJECT
private:
	Links *link;

protected:
	void closeEvent(QCloseEvent *event);

public:
	ShowUserInf(Links *tLink, const QString &acc,
		QWidget *parent=0);
	~ShowUserInf();

	public slots:
		void clickedOKButton();
		void result(qint32 replyKind);
};

#endif
