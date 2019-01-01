/*
 * changeInf 修改个人资料
 */
#include "changeInf.h"

ChangeInf::ChangeInf(Links *tLink,
					 const QString &acc,
					 QWidget *parent/* =0 */)
: InformationBox(parent), link(tLink)
{
	//setWindowTitle("修改个人信息");
	setWindowTitle( tr("Modify Personal Information") );
	
	//向服务器发送请求个人详细信息
	link->getUserRequest(acc);
	setSomeReadOnly(true);
	connect(link, SIGNAL(newReplySignal(qint32)), 
		this, SLOT(result(qint32)));
}

ChangeInf::~ChangeInf()
{
	
}

void ChangeInf::clickedOKButton()
{
	if(!informationIsAllow())
		return;
	userInf = getUserInformation();
	userInf.password = tPassward;
	link->changeInformationRequest(userInf);
	setAllReadOnly(true);
}

void ChangeInf::result(qint32 replyKind)
{
	//获得了个人的详细信息，就把信息填入相应的输入栏中
	if(GET_USER_INF_SUCCESS == replyKind)
	{
		UserInformation userInf;
		userInf = link->getUserInformation();
		setUserInformation(userInf);
		tPassward = userInf.password;
	}
	//成功地修改了个人信息
	else if(CHANGE_INFORMATION_SUCCESS == replyKind)
	{
		//QMessageBox::critical(this, "恭喜", "修改个人信息成功");
		QMessageBox::information(this, tr("Congratulations"), 
			tr("Modify Personal Information successfully"));
		emit changeInformationSignal(userInf.avatarNumber, 
			userInf.nickName, userInf.aboutMyself);
		close();
	}
	setMostReadOnly(false);
}

void ChangeInf::closeEvent(QCloseEvent *event)
{
	//因为link的parent不是ChangeInf，所以不会随着的关闭而断开连接，
	//所以要手动断开连接
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
