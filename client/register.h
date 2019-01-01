/*
 * 注册窗口
 */
#ifndef REGISTERBOX_H_
#define REGISTERBOX_H_

#include "constant.h"
#include "links.h"
#include "informationBox.h"


class RegisterBox : public InformationBox
{
	Q_OBJECT
private:
	UserInformation userInf;				//储存用户信息
	Links *link;

protected:
	void closeEvent(QCloseEvent *event);

public:
	RegisterBox(Links *tlink, QWidget *parent=0);
	~RegisterBox();
	
	public slots:
		void result(qint32 replyKind);
		void clickedOKButton();	

};

#endif
