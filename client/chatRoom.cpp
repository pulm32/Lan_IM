/*
 * 与好友聊天时的窗口
 */

#include "chatRoom.h"
#include <QColorDialog>
#include <QFontDialog>
Chatroom::Chatroom(Links *tLink, 
				   const FriendInformation &theFriend, 
				   const QString &acc, 
				   const QString &name,
				   QWidget *parent/* =0 */)
: QWidget(parent), link(tLink), peer(theFriend),
	myAccount(acc), myName(name)
{
	ui.setupUi(this);

	//设置聊天窗口背景
	QPalette pal;
	QPixmap pixmap( QDir::toNativeSeparators
		("pictures/chatRoom.jpg") );
	pal.setBrush(QPalette::Window,QBrush(pixmap));
	setPalette(pal);

	if(peer.remark.isEmpty())
		peerRemark = peer.name;
	else
		peerRemark = peer.remark;

	//设置标题
	QString title = QString("%1 (%2)").arg(peerRemark)
		.arg(theFriend.account);
	setWindowTitle(title);

	//设置about栏
	ui.aboutTextEdit->append(tr("account: ") + theFriend.account);
	ui.aboutTextEdit->append(tr("nickname: ") + peerRemark);
	ui.aboutTextEdit->append(tr("Personal Description: ") + theFriend.about);
	ui.aboutTextEdit->setReadOnly(true);

	//将输出栏设置为只读
	ui.outputTextEdit->setReadOnly(true);

	//设置头像
	ui.avatarFrame->setObjectName("avatar");
	QString str = QString("QFrame#avatar{border-image:url(pictures/%1.bmp)}")
		.arg(QString::number(peer.avatarNumber));
	ui.avatarFrame->setStyleSheet(str);

	readFontColor();

	//连接各个信号/糟
	connect(ui.sendPushButton, SIGNAL(clicked()), 
		this, SLOT(clickedSendButton()));
	connect(ui.closePushButton, SIGNAL(clicked()),
		this, SLOT(close()));
	connect(ui.colorPushButton, SIGNAL(clicked()),
		this, SLOT(clickedColorButton()));
	connect(ui.FontsPushButton, SIGNAL(clicked()),
		this, SLOT(clickedFontsButton()));
	connect(ui.recordPushButton, SIGNAL(clicked()),
		this, SLOT(clickedRecordButton()));

	connect(ui.inputTextEdit, SIGNAL(textChanged()),
		this, SLOT(inputTextChanged()));
	connect(ui.inputTextEdit, SIGNAL(sendSignal()),
		this, SLOT(clickedSendButton()));
}

Chatroom::~Chatroom()
{

}


void Chatroom::clickedSendButton()
{
	//如果输入栏为空，则忽略该发送信号
	if(ui.inputTextEdit->toPlainText().isEmpty())
		return;

	//获取输入栏中的信息，并更新输出栏
	sendString = ui.inputTextEdit->toHtml();
	ui.inputTextEdit->clear();
	QString dateTime = getCurrentDateTime();
	QString temp = QString("<font size=\"4\" color=green>%1    %2: </font>%3")
		.arg(myName).arg(dateTime).arg(sendString);
	ui.outputTextEdit->append(temp);

	//向服务器发送信息，让其转发给目标用户
	Message message;
	message.kind = TALK_MESSAGE;
	message.sender = myAccount;
	message.receiver = peer.account;
	message.text = sendString;
	link->messageRequest(message);
}

void Chatroom::setOutputLine(const Message &mes)
{
	//将（收到的）信息显示在输出栏
	QString dateTime = getCurrentDateTime();
	QString temp = QString("<font size=\"4\" color=blue>%1    %2: </font>%3")
		.arg(peerRemark).arg(dateTime).arg(mes.text);
	ui.outputTextEdit->append(temp);
}

void Chatroom::closeEvent(QCloseEvent *event)
{
	//向主界面发送退出信号
	emit roomQuitSignal();
	saveTalkHistory();

	//因为link的parent不是Chatroom，所以不会随着的关闭而断开连接，
	//所以要手动断开连接
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
	event->accept();
}

void Chatroom::clickedColorButton()
{
	//设置字体的颜色，并将其写入文件
	QColorDialog *colorDialog = new QColorDialog(this);
	colorDialog->setCurrentColor(ui.inputTextEdit->textColor());

	if(QDialog::Accepted == colorDialog->exec())
	{
		saveFile.color = colorDialog->currentColor();
		ui.inputTextEdit->setTextColor(saveFile.color);
		saveFontColor();
	}
}

void Chatroom::clickedFontsButton()
{
	//设置字体，并将其写入文件
	QFontDialog *fontDialog = new QFontDialog(this);
	fontDialog->setCurrentFont(ui.inputTextEdit->font());
	fontDialog->setModal(true);
	if(QDialog::Accepted == fontDialog->exec())
	{
		saveFile.font = fontDialog->currentFont();
		ui.inputTextEdit->setCurrentFont(saveFile.font);
		saveFontColor();
	}
}

void Chatroom::readFontColor()
{
	//从文件中读取字体和颜色，并设置输入栏的字体格式
	QString filename = QString("./save/%1/colorFont.cf").arg(myAccount);
	filename = QDir::toNativeSeparators(filename);
	QFile file(filename);

	//如果不能打开储存文件的话，就直接跳过这一步
	if( !file.open(QIODevice::ReadOnly) )
		return;

	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_4_0);
	in >> saveFile;
	ui.inputTextEdit->setCurrentFont(saveFile.font);
	ui.inputTextEdit->setTextColor(saveFile.color);
	file.close();
}

void Chatroom::saveFontColor() const
{

	//将自己的设置写入文件
	QString filename = QString("./save/%1/colorFont.cf").arg(myAccount);
	filename = QDir::toNativeSeparators(filename);
	QFile file(filename);
	if( !file.open(QIODevice::WriteOnly) )
		return;
	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_4_0);
	out << saveFile;
	file.close();
}

void Chatroom::clickedRecordButton()
{
	//显示聊天记录
	QString record = readTalkHistory();
	QTextEdit *textEdit = new QTextEdit(record, this);
	textEdit->resize(300, 500);
	Qt::WindowFlags flag = Qt::Window
		| Qt::WindowCloseButtonHint 
		| Qt::WindowMinimizeButtonHint;
	textEdit->setWindowFlags(flag);
	textEdit->setReadOnly(true);
	textEdit->show();
}

void Chatroom::inputTextChanged()
{
	if(ui.inputTextEdit->toPlainText().isEmpty())
	{
		ui.inputTextEdit->setTextColor(saveFile.color);
		ui.inputTextEdit->setCurrentFont(saveFile.font);
	}
}

void Chatroom::saveTalkHistory() const
{
	//关闭聊天窗口时，保存聊天记录
	QString fileLoad = QString("./save/%1/%2.re")
		.arg(myAccount).arg(peer.account);
	fileLoad = QDir::toNativeSeparators(fileLoad);
	QFile file(fileLoad);
	bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Append);
	if(!isOpen)
		return;

	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_4_0);

	//如果聊天记录是空的，就不用保存了
	if(ui.outputTextEdit->toPlainText().isEmpty())
		return;

	QString talkRecord = ui.outputTextEdit->toHtml();
	out << talkRecord;
	file.close();
}

QString Chatroom::readTalkHistory()
{
	//读取聊天记录，并加上输入栏中的字符
	QString allRecord;
	QString fileLoad = QString("./save/%1/%2.re")
		.arg(myAccount).arg(peer.account);
	fileLoad = QDir::toNativeSeparators(fileLoad);
	QFile file(fileLoad);
	bool isOpen = file.open(QIODevice::ReadOnly);

	//如果读取聊天记录失败，就直接返回输入栏的字符
	if(!isOpen)
		return ui.outputTextEdit->toHtml();

	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_4_0);

	QString tempString;
	//从文件中读取全部的字符串
	while( !file.atEnd() )
	{
		in >> tempString;
		allRecord += tempString;
	}
	file.close();
	allRecord += ui.outputTextEdit->toHtml();
	return allRecord;
}

QString Chatroom::getCurrentDateTime()
{
	QTime time = QTime::currentTime();
	QDate date = QDate::currentDate();

	return QString("%1  %2").arg(date.toString(Qt::ISODate))
		.arg(time.toString(Qt::ISODate));
}
