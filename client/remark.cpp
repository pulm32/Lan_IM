/*
 *修改好友备注时所用的窗口
 */

#include "remark.h"

ChangeRemark::ChangeRemark(Links *tLink,
						   const Message &mes,
						   QWidget *parent)
						   : tempBox(1, parent), link(tLink),
						   message(mes)
{
	setWindowTitle( tr("Change remark") );
	resize(200, 100);

	setLabelName( tr("Please enter the new remark") );
	connect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}

ChangeRemark::~ChangeRemark()
{
	
}

void ChangeRemark::clickedOKButton()
{
	TempStrings temp = getInformation();
	message.text = temp.one;
	//发送修改备注请求
	link->changeRemarkRequest(message);
	setAllEnabled(false);
}

void ChangeRemark::result(qint32 replyKind)
{
	if(CHANGE_REMARK_SUCCESS == replyKind)
	{
		//QMessageBox::critical(this, "恭喜", "修改备注成功");
		QMessageBox::information(this, tr("Congratulation"),
			tr("Successfully change the remark"));
		emit changeRemarkSignal(message.text);
		close();
	}
	setAllEnabled(true);
}

void ChangeRemark::closeEvent(QCloseEvent *event)
{
	//因为link的parent不是ChangeRemark，所以不会随着的关闭而断开连接，
	//所以要手动断开连接
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
