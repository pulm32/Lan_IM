/*
 * 用于显示或修改信息时用的窗口
 */

#include "informationBox.h"

InformationBox::InformationBox(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);
	//将该窗口固定大小
	Qt::WindowFlags flag = Qt::Window
		| Qt::WindowCloseButtonHint 
		| Qt::WindowMinimizeButtonHint;
	setWindowFlags(flag);
    setFixedSize(480, 600);

	QPalette pal;
	QPixmap pixmap( QDir::toNativeSeparators
		("pictures/login.jpg") );
	pal.setBrush(QPalette::Window,QBrush(pixmap));
	setPalette(pal);

	//将密码栏和验证密码栏设置为密码风格
	ui.passwordLineEdit->setEchoMode(QLineEdit::Password);
	ui.confirmPwdLineEdit->setEchoMode(QLineEdit::Password);

	//头像设置
	num = 1;
	ui.avatarFrame->setObjectName("avatar");
	QString str = QString("QFrame#avatar{border-image:url(pictures/%1.bmp)}")
		.arg(QString::number(num));
	ui.avatarFrame->setStyleSheet(str);
	ui.avatarLabel->setText("1 / 134");

	connect(ui.pastButton, SIGNAL(clicked()), this, SLOT(clickedPastButton()));
	connect(ui.nextButton, SIGNAL(clicked()), this, SLOT(clickedNextButton()));
	connect(ui.quitPushButton, SIGNAL(clicked()), 
		this, SLOT(clickedQuitButton()) );
	connect(ui.OKPushButton, SIGNAL(clicked()),
		this, SLOT(clickedOKButton()) );
	connect(ui.helpPushButton, SIGNAL(clicked()),
		this, SLOT(clickedHelpButton()) );
}

InformationBox::~InformationBox()
{

}

bool InformationBox::informationIsAllow()
{
	QRegExp regExp;
	regExp.setPattern("^[A-Za-z][A-Za-z0-9]{5,19}$");
	if(!regExp.exactMatch(ui.accountLineEdit->text()))
	{
		//QMessageBox::critical(this, "Error", "帐号格式错误，请再试一遍");
		QMessageBox::critical(this, tr("Error"), 
			tr("Account's Format is wrong. Please try again"));
		return false;
	}
	
	if(ui.nicknameLineEdit->text().isEmpty() 
		|| ui.nicknameLineEdit->text().size() > 40)
	{
		//QMessageBox::critical(this, "Error", "呢称格式错误，请再试一遍");
		QMessageBox::critical(this, tr("Error"), 
			tr("Nickname's Format is wrong. Please try again"));
		return false;
	}
	regExp.setPattern("^\\d{0,15}$");
	if(!ui.phoneNumLineEdit->text().isEmpty() &&
		!regExp.exactMatch(ui.phoneNumLineEdit->text()))
	{
		//QMessageBox::critical(this, "Error", "密码格式错误，请再试一遍");
		QMessageBox::critical(this, tr("Error"), 
			tr("Phone number's Format is wrong. Please try again"));
		return false;
	}
	if(!ui.mobileNumLineEdit->text().isEmpty() &&
		!regExp.exactMatch(ui.mobileNumLineEdit->text()))
	{
		//QMessageBox::critical(this, "Error", "密码格式错误，请再试一遍");
		QMessageBox::critical(this, tr("Error"), 
			tr("Mobile number's Format is wrong. Please try again"));
		return false;
	}
	regExp.setPattern("^\\d{4}-\\d{1,2}-\\d{1,2}$");
	if( !regExp.exactMatch(ui.birthdayLineEdit->text())
		&& !ui.birthdayLineEdit->text().isEmpty())
	{
		//QMessageBox::critical(this, "Error", "出生日期格式错误，请再试一遍");
		QMessageBox::critical(this, tr("Error"), 
			tr("Birthday's Format is wrong. Please try again"));
		return false;
	}
	if(ui.cityLineEdit->text().size() > 40)
	{
		QMessageBox::critical(this, tr("Error"), 
			tr("City's Format is wrong. Please try again"));
		return false;
	}
	if(ui.aboutTextEdit->toPlainText().size() > 400)
	{
		QMessageBox::critical(this, tr("Error"), 
			tr("About myself's Format is wrong. Please try again"));
		return false;
	}
	return true;
}


bool InformationBox::passwordIsAllow()
{
	QRegExp regExp;
	regExp.setPattern("^[A-Za-z0-9]{6,20}$");
	if(!regExp.exactMatch(ui.passwordLineEdit->text()))
	{
		//QMessageBox::critical(this, "Error", "密码格式错误，请再试一遍");
		QMessageBox::critical(this, tr("Error"), 
			tr("password's Format is wrong. Please try again"));
		return false;
	}

	if(ui.passwordLineEdit->text() != ui.confirmPwdLineEdit->text())
	{
		//QMessageBox::critical(this, "Error", "两次输入密码不相同，请再试一遍");
		QMessageBox::critical(this, tr("Error"), 
			tr("The two passwords are not the same. Please try again"));
		return false;
	}
	return true;
}

void InformationBox::clickedQuitButton()
{
	close();
}

void InformationBox::clickedPastButton()
{
	num--;
	if(num < 1)
		num = all;
	QString labelStr = QString("%1 / %2").arg(QString::number(num)).
		arg(QString::number(all));
	QString str = QString("QFrame#avatar{border-image:url(pictures/%1.bmp)}")
		.arg(QString::number(num));
	ui.avatarFrame->setStyleSheet(str);
	ui.avatarLabel->setText(labelStr);
}

void InformationBox::clickedNextButton()
{
	num++;
	if(num > all)
		num = 1;
	QString labelStr = QString("%1 / %2").arg(QString::number(num)).
		arg(QString::number(all));
	QString str = QString("QFrame#avatar{border-image:url(pictures/%1.bmp)}")
		.arg(QString::number(num));
	ui.avatarFrame->setStyleSheet(str);
	ui.avatarLabel->setText(labelStr);
}

UserInformation InformationBox::getUserInformation()
{
	//
	UserInformation userInf;
	userInf.account = ui.accountLineEdit->text();
	userInf.password = ui.passwordLineEdit->text();
	if(userInf.password != ui.confirmPwdLineEdit->text())
		userInf.password.clear();
	userInf.nickName = ui.nicknameLineEdit->text();
	userInf.avatarNumber = num;
	userInf.mobileNumber = ui.mobileNumLineEdit->text();
	userInf.phoneNumber = ui.phoneNumLineEdit->text();
	userInf.birthday = ui.birthdayLineEdit->text();
	userInf.city = ui.cityLineEdit->text();
	userInf.aboutMyself = ui.aboutTextEdit->toPlainText();
	return userInf;
}

void InformationBox::setAllReadOnly(bool enable)
{
	setSomeReadOnly(enable);
	setMostReadOnly(enable);
}

void InformationBox::setSomeReadOnly(bool enable)
{
	//将帐号栏，密码栏和验证密码栏设置为自读
	ui.accountLineEdit->setReadOnly(enable);
	ui.passwordLineEdit->setEnabled(!enable);
	ui.confirmPwdLineEdit->setEnabled(!enable);
}

void InformationBox::setUserInformation(const UserInformation &userInf)
{
	ui.accountLineEdit->setText(userInf.account);
	ui.nicknameLineEdit->setText(userInf.nickName);
	ui.mobileNumLineEdit->setText(userInf.mobileNumber);
	ui.phoneNumLineEdit->setText(userInf.phoneNumber);
	ui.cityLineEdit->setText(userInf.city);
	ui.birthdayLineEdit->setText(userInf.birthday);
	ui.aboutTextEdit->setText(userInf.aboutMyself);

	num = userInf.avatarNumber;
	QString labelStr = QString("%1 / %2").arg(QString::number(num)).
		arg(QString::number(all));
	ui.avatarLabel->setText(labelStr);
	QString str = QString("QFrame#avatar{border-image:url(pictures/%1.bmp)}")
		.arg(QString::number(num));
	ui.avatarFrame->setStyleSheet(str);
}

void InformationBox::setMostReadOnly(bool enable)
{
	ui.nicknameLineEdit->setReadOnly(enable);
	ui.mobileNumLineEdit->setReadOnly(enable);
	ui.phoneNumLineEdit->setReadOnly(enable);
	ui.cityLineEdit->setReadOnly(enable);
	ui.birthdayLineEdit->setReadOnly(enable);
	ui.aboutTextEdit->setReadOnly(enable);
	ui.pastButton->setEnabled(!enable);
	ui.nextButton->setEnabled(!enable);
}


void InformationBox::clickedHelpButton()
{
	//详细的帮助条款储存在翻译文件(client.qm)中
	QMessageBox::information(this, tr("register help"), tr("help"));
}
