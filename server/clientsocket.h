/*
 * 这个类专门负责接收和（向客户端）发送信息
 */

#ifndef CLIENTSOCKET_H_
#define CLIENTSOCKET_H_

#include "constant.h"


class ClientSocket : public QTcpSocket
{
	Q_OBJECT
private:
	saveStruct save;			//储存各种信息
	qint16 blockSize;

public:
	ClientSocket(QObject *parent = 0);
	~ClientSocket();

signals:
	//请求Server处理信息
	void sendSignal(const saveStruct &temp);
	//用户登录
	void userLoginSignal(const UserInformation &user);
	//用户断开连接了
	void deleteSignal(const QString &acc);

public slots:
		//接收和发送信息
		void receiveMessage();
		void sendMessage(const saveStruct &temp);
		void deleteScoket();
};

#endif
