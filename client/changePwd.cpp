/*
 * 要修改密码时弹出的窗口
 */
#include "changePwd.h"

ChangePassword::ChangePassword(Links *tLink, 
							   const QString &acc,
							   QWidget *parent/* =0 */)
: tempBox(3, parent), account(acc), link(tLink)
{
	setWindowTitle( tr("Change password") );
	resize(200, 100);

	setLabelName(tr("Please enter the old password"),
		tr("Please enter the new password"),
		tr("Please enter the new password again"));
	setPasswordStyle();
	connect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}

ChangePassword::~ChangePassword()
{
	
}

void ChangePassword::clickedOKButton()
{
	//该temp有三栏，第一栏是旧密码，第二栏是新密码，第三栏验证新密码
	TempStrings temp = getInformation();

	QRegExp regExp;
	regExp.setPattern("^[A-Za-z0-9]{6,20}$");
	if(!regExp.exactMatch(temp.two))
	{
		//QMessageBox::critical(this, "Error", "密码格式错误，请再试一遍");
		QMessageBox::critical(this, tr("Error"), 
			tr("new password's Format is wrong. Please try again"));
		return;
	}
	//如果新密码和验证新密码不同的话，就返回
	if(temp.two != temp.three)
	{
		QMessageBox::critical(this, tr("Error"), tr("The two new passwords are different"));
		return;
	}

	//验证密码成功后，将第三行替换为自己的帐号
	temp.three = account;

	link->changePasswordRequest(temp);
	setAllEnabled(false);
}

void ChangePassword::result(qint32 replyKind)
{
	//旧密码错误
	if(OLD_PWD_IS_WRONG == replyKind)
		QMessageBox::critical(this, tr("Error"),
			tr("The old password is wrong, please try again"));
	//修改密码成功
	else if(CHANGE_PWD_SUCCESS)
	{
		QMessageBox::information(this, tr("Congratulation"), 
			tr("Change password success"));
		close();
	}
	//setAllEnabled(true);
}

void ChangePassword::closeEvent(QCloseEvent *event)
{
	//因为link的parent不是ChangePassword，所以不会随着的关闭而断开连接，
	//所以要手动断开连接
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
