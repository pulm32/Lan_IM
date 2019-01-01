/*
 * 服务器类 负责与客户端建立连接
 */
#ifndef SERVER_H_
#define SERVER_H_

#include "constant.h"
#include "database.h"
#include "clientsocket.h"

class Server : public QTcpServer
{
	Q_OBJECT
private:
	//网络连接的描述符
	int descriptor;	
	saveStruct temp;
	//连接与操作数据库
	ServerDatabase data;
	//已登录的用户列表
	QMap<QString, ClientSocket*> userMap;

public:
	Server(QObject *parent=0);
	~Server();

	//处理好友请求
	void friendRequest(const saveStruct &save);
	//改变用户状态
	void changeStatu(const QString &acc, qint32 status);

protected:
	void incomingConnection(int sockDescriptor);

	public slots:
		//客户端断开连接
		void clientDisconnected(const QString &acc);
		//要求clientSocket发送信息
		void sendMessage(const saveStruct &save); 
};

#endif
