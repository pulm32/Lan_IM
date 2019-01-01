/*
 * 这个类专门负责接收和（向客户端）发送信息
 */


#include "clientsocket.h"

ClientSocket::ClientSocket(QObject *parent)
: QTcpSocket(parent)
{
	blockSize = 0;
	save.clientSocket = this;
	connect(this, SIGNAL(readyRead()),
		this, SLOT(receiveMessage()));
	connect(this, SIGNAL(disconnected()),
		this, SLOT(deleteScoket()));
}

ClientSocket::~ClientSocket()
{

}

void ClientSocket::receiveMessage()
{
	QDataStream in(this);
	in.setVersion(QDataStream::Qt_4_0);

	//
	if (blockSize == 0)
	{
		if (bytesAvailable() < (int)sizeof(quint16))
			return;
		in >> blockSize;
	}
	if (bytesAvailable() < blockSize)
		return;
	in >> save.requestKind;

	//
	if(CHECK_CONNECTION == save.requestKind)
	{
		save.replyKind = CHECK_CONNECTION;
		sendMessage(save);
		blockSize = 0;
		return;
	}
	else if(LOGIN == save.requestKind)
	{
		in >> save.logInf;
		save.myAccount = save.logInf.account;
	}
	else if(CHECK_MESSAGE == save.requestKind)
		in >> save.myAccount;
	else if(REGISTER == save.requestKind)
		in >> save.userInf;
	else if(TALK == save.requestKind)
		in >> save.message;
	else if(ADD_FRIEND == save.requestKind)
		in >> save.message;
	else if(GET_FRIEND_INFORMATION == save.requestKind)
		in >> save.peerAccount;
	else if(DISAGREE_FRIEND == save.requestKind)
		in >> save.peerAccount;
	else if(GET_USER_INFORMATION == save.requestKind)
		in >> save.peerAccount;
	else if(CHANGE_PASSWORD == save.requestKind)
		in >> save.tempStr;
	else if(CHANGE_INFORMATION == save.requestKind)
		in >> save.userInf;
	else if(DELETE_FRIEND == save.requestKind)
		in >> save.peerAccount;
	else if(CHANGE_REMARK == save.requestKind)
		in >> save.message;
	else if(CHANGE_STATUE == save.requestKind)
		in >> save.status;

	blockSize = 0;
	emit sendSignal(save);
}

void ClientSocket::sendMessage(const saveStruct &temp)
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	//
	out << (qint16)0;
	out << temp.replyKind;

	//
	if(LOGIN_SUCCESS == temp.replyKind)
	{
		qint32 len = temp.friendsVec.size();
		out << len;
		for(qint32 i=0;i<len;i++)
			out << temp.friendsVec[i];
	}
	else if(HAVE_MESSAGE == temp.replyKind)
	{
		qint32 len = temp.messageVec.size();
		out << len;
		for(qint32 i=0;i<len;i++)
			out << temp.messageVec[i];
	}
	else if(CHANGE_STATUE == temp.replyKind)
		out << temp.peerAccount << temp.status;
	else if(GET_USER_INF_SUCCESS == temp.replyKind)
		out << temp.userInf;
	else if(DELETE_FRIEND_SUCCESS == temp.replyKind)
		out << temp.peerAccount;
	else if(ADD_FRIEND == temp.replyKind)
		out << temp.message;
	else if(GET_FRIEND_SUCCESS == temp.replyKind)
		out << temp.theFriend;
	else if(TALK == temp.replyKind)
		out << temp.message;
	else if(BE_DELETED == temp.replyKind)
		out << temp.peerAccount;

	out.device()->seek(0);
	out << (qint16)(block.size() - sizeof(qint16));

	write(block);
}

void ClientSocket::deleteScoket()
{
	if(!save.myAccount.isEmpty())
		emit deleteSignal(save.myAccount);
	deleteLater();
}
