/*
 * 与好友聊天时的窗口
 */
#ifndef CHATROOM_H_
#define CHATROOM_H_

#include "constant.h"
#include "links.h"
#include "inputTextEdit.h"
#include "ui_chatRoom.h"


class Chatroom : public QWidget
{
	Q_OBJECT
private:
	Ui::chatroomWidget ui;
	Links *link;
	FriendInformation peer;				//储存对方信息
	QString myAccount;					//自已的帐号
	QString myName;						//自已的名字
	QString peerRemark;
	QString sendString;					//要发送的信息
	SaveFile saveFile;					//字体和颜色

	void saveTalkHistory() const;
	QString readTalkHistory();
	//（从文件中）读取和写入字体，颜色设置
	void readFontColor();
	void saveFontColor() const;
	//获取当前的日期和时间
	QString getCurrentDateTime();

protected:
	//重载关闭事件
	void closeEvent(QCloseEvent *event);

public:
	Chatroom(Links *tLink, const FriendInformation &theFriend, 
		const QString &acc, const QString &name, QWidget *parent=0);
	~Chatroom();

	//设置输出栏
	void setOutputLine(const Message &mes);

signals:
	//退出信号
	void roomQuitSignal();
	//让主界面来发送聊天信息
	void messageSignal(const Message &mes);

	public slots:
		void clickedSendButton();
		void clickedColorButton();
		void clickedFontsButton();
		void clickedRecordButton();
		void inputTextChanged();
};

#endif
