/*
 * 显示好友详细信息时所用的窗口
 */

#include "showUserInf.h"

ShowUserInf::ShowUserInf(Links *tLink,
						 const QString &acc,
						 QWidget *parent)
: InformationBox(parent), link(tLink)
{
	setWindowTitle( tr("friend's information") );
	setAllReadOnly(true);

	//向服务器发送请求，要求获得该用户的详细信息
	link->getUserRequest(acc);

	connect(link, SIGNAL(newReplySignal(qint32)), 
		this, SLOT(result(qint32)));
}

ShowUserInf::~ShowUserInf()
{
	
}

void ShowUserInf::clickedOKButton()
{
	close();
}

void ShowUserInf::result(qint32 replyKind)
{
	//得到信息后，就将所有信息填入相应的对话栏中
	if(GET_USER_INF_SUCCESS == replyKind)
	{
		UserInformation userInf;
		userInf = link->getUserInformation();
		setUserInformation(userInf);
	}
}

void ShowUserInf::closeEvent(QCloseEvent *event)
{
	//因为link的parent不是ShowUserInf，所以不会随着的关闭而断开连接，
	//所以要手动断开连接
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
