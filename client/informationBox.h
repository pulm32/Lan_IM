/*
 * 用于显示或修改信息时用的窗口
 */

#ifndef INFORMATIONBOX_H_
#define INFORMATIONBOX_H_

#include "constant.h"
#include "links.h"
#include "ui_informationBox.h"


class InformationBox : public QWidget
{
	Q_OBJECT
private:
	Ui::informationBoxForm ui;
	QString confirmPwd;					//验证的密码
	int num;
	static const int all = 134;			//总头像数

public:
	InformationBox(QWidget *parent);
	virtual ~InformationBox() = 0;

	//获取用户输入的信息
	UserInformation getUserInformation();

	//将所有栏目设置为只读（用于查看信息）
	void setAllReadOnly(bool enable);

	//将除帐号，密码栏之外的栏目设为只读
	void setMostReadOnly(bool enable);

	//将帐号，密码栏设置为只读
	void setSomeReadOnly(bool enable);

	//将好友信息填入栏目中
	void setUserInformation(const UserInformation &userInf);

	//（输入的）个人信息的格式是否符合要求
	//不知为什么，这个函数不能设为const
	bool informationIsAllow();

	//（输入的）密码的格式是否符合要求
	//不知为什么，这个函数不能设为const
	bool passwordIsAllow();

	public slots:
		void clickedQuitButton();
		//完成按钮（纯虚函数）
		virtual void clickedOKButton() = 0;
		void clickedPastButton();
		void clickedNextButton();
		void clickedHelpButton();
};

#endif
