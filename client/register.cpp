
/*
 * 注册窗口
 */
#include "register.h"

RegisterBox::RegisterBox(Links *tlink, QWidget *parent)
: InformationBox(parent), link(tlink)
{
	setWindowTitle( tr("New user registration") );
	connect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}

RegisterBox::~RegisterBox()
{
	
}

void RegisterBox::result(qint32 replyKind)
{
	if(REGISTER_EXIST == replyKind)
		//QMessageBox::critical(this, "错误", "该用户名已被注册，请换一个用户名");
		QMessageBox::critical(this, tr("Error"), tr("This user name has been registered"));
	else if(REGISTER_SUCCESS == replyKind)
	{
		//QMessageBox::critical(this, "恭喜", "恭喜你，注册成功");
		QMessageBox::information(this, tr("Congratulations"), tr("registration successful"));
		close();
	}
	setAllReadOnly(false);
}

void RegisterBox::clickedOKButton()
{
	if(!informationIsAllow() || !passwordIsAllow())
		return;
	userInf = getUserInformation();
	//status已经初始化为0了，但为了保险起见，再强调一遍，呵呵
	userInf.status = OFFLINE;
	//发送注册请求
	link->registerRequest(userInf);
	setAllReadOnly(true);
}

void RegisterBox::closeEvent(QCloseEvent *event)
{
	//因为link的parent不是RegisterBox，所以不会随着的关闭而断开连接，
	//所以要手动断开连接
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
