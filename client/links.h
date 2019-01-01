/*
 * 网络连接专用类
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "constant.h"

class Links : public QObject
{
	Q_OBJECT
private:
	bool isConnected;

	ServerNode serverNode;
	qint32 requestKind, replyKind;				//请求类型，应答类型
	QString myAccount;
	QString peerAcc;
	qint32 status;
	UserInformation userInf;					//用户信息
	LoginInformation logInf;					//登录信息
	FriendInformation theFriend;				//
	Message message;							//
	TempStrings tempStr;						
	QVector<Message> messageVec;				//	
	QVector<FriendInformation> friendsVec;		//存储好友列表（从服务器返回的）

	QTcpSocket *tcpClient;						
	qint16 blockSize;							
	void newConnect();							//新建链接

public:
	Links(const ServerNode &node, QObject *parent=0);
	~Links();

	//返回各种数据
	void setIpAddress(const ServerNode &node)
	{
		serverNode.ipAddress = node.ipAddress;
		serverNode.port = node.port;
	}
	LoginInformation getLoginInformation() const
	{	return logInf;	}
	UserInformation getUserInformation() const
	{	return userInf;	}
	FriendInformation getFriendInformation() const
	{	return theFriend;	}
	QVector<FriendInformation> getFriends() const
	{	return friendsVec;	}
	Message getSimpleMessage() const
	{	return message;		}
	QVector<Message> getMessages() const
	{	return messageVec;	}
	qint32 getStatus() const
	{	return status;	}
	QString getPeerAccount() const
	{	return peerAcc;		}

	//发送各种用户请求
	void loginRequest(const LoginInformation &li);	
	void registerRequest(const UserInformation &usin);	
	void quitRequest(const QString &acc);
	void messageRequest(const Message &mes);
	void checkConnectionRequest();
	void checkMessageRequest(const QString &acc);
	void addFriendRequest(const Message &mes);
	void getFriendRequest(const QString &acc);
	void deleteFriendRequest(const QString &peer);
	void getUserRequest(const QString &acc);
	void changeInformationRequest(const UserInformation &usin);
	void changeRemarkRequest(const Message &mes);
	void changePasswordRequest(const TempStrings &temp);
	void changeStatusRequest(const QString &acc, const qint32 n);

	public slots:
		//发送信息
		void sendRequest();				
		//读取信息
		void readResult();		
		//与服务器断开连接了
		void ServerDisconnected();		
		//提示错误信息
		void displayError(QAbstractSocket::SocketError socketError);

	signals:
		void newReplySignal(qint32 replyKind);
		void connectionFailedSignal();
		void disconnectedSignal();
		

};

#endif
