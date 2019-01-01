/*
 * 网络连接专用类
 */


#include "links.h"
#include <QStringList>
#include <QMessageBox>

Links::Links(const ServerNode &node,
			 QObject *parent/* =0 */)
: QObject(parent), serverNode(node)
{
	isConnected = false;
	tcpClient = new QTcpSocket(this);

	connect(tcpClient, SIGNAL(connected()), this, SLOT(sendRequest()) );
	connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readResult()) );
	connect(tcpClient, SIGNAL(disconnected()), 
		this, SLOT(ServerDisconnected()));
	connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
		this, SLOT(displayError(QAbstractSocket::SocketError)));
}

Links::~Links()
{

}

void Links::newConnect()
{
	blockSize = 0;
	if(!isConnected)
	{
		tcpClient->abort();
		tcpClient->connectToHost(serverNode.ipAddress, serverNode.port);
	}
	else
		sendRequest();
}

void Links::sendRequest()
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	out << (qint16)0;
	out << requestKind;


	if(LOGIN == requestKind)
		out << logInf;
	else if(CHECK_MESSAGE == requestKind)
		out << myAccount;
	else if(REGISTER == requestKind)
		out << userInf;
	else if(QUIT == requestKind)
		out << myAccount;
	else if(TALK == requestKind)
		out << message;
	else if(ADD_FRIEND == requestKind)
		out << message;
	else if(GET_FRIEND_INFORMATION == requestKind)
		out << myAccount;
	else if(DELETE_FRIEND == requestKind)
		out << peerAcc;
	else if(GET_USER_INFORMATION == requestKind)
		out << myAccount;
	else if(CHANGE_INFORMATION == requestKind)
		out << userInf;
	else if(CHANGE_REMARK == requestKind)
		out << message;
	else if(CHANGE_PASSWORD == requestKind)
		out << tempStr;
	else if(CHANGE_STATUE == requestKind)
		out << status;

	out.device()->seek(0);
	out << (qint16)(block.size() - sizeof(qint16));
	tcpClient->write(block);

	if(!isConnected)
		isConnected = true;
}

void Links::readResult()
{
	QDataStream in(tcpClient);
	in.setVersion(QDataStream::Qt_4_0);

	if (blockSize == 0)
	{
		if (tcpClient->bytesAvailable() < (int)sizeof(qint16))
			return;
		in >> blockSize;
	}

	if (tcpClient->bytesAvailable() < blockSize)
		return;

	in >> replyKind;
	QString outputStr;
	
	if(LOGIN_SUCCESS == replyKind)
	{
		friendsVec.clear();
		FriendInformation tFriend;
		qint32 len;
		in >> len;
		for(int i=0;i<len;i++)
		{
			in >> tFriend;
			friendsVec.push_back(tFriend);
		}
	}
	else if(HAVE_MESSAGE == replyKind)
	{
		messageVec.clear();
		Message tMessage;
		qint32 len;
		in >> len;
		for(int i=0;i<len;i++)
		{
			in >> tMessage;
			messageVec.push_back(tMessage);
		}
	}
	else if(GET_FRIEND_SUCCESS == replyKind)
		in >> theFriend;
	else if(GET_USER_INF_SUCCESS == replyKind)
		in >> userInf;
	else if(CHANGE_STATUE == replyKind)
		in >> peerAcc >> status;
	else if(DELETE_FRIEND_SUCCESS == replyKind)
		in >> peerAcc;
	else if(ADD_FRIEND == replyKind)
		in >> message;
	else if(TALK == replyKind)
		in >> message;
	else if(CHANGE_STATUE == replyKind)
		in >> peerAcc >> status;
	else if(BE_DELETED == replyKind)
		in >> peerAcc;

	blockSize = 0;
	emit newReplySignal(replyKind);
}


void Links::displayError(QAbstractSocket::SocketError socketError)
{
	switch (socketError)
	{
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		QMessageBox::information(NULL, tr("Client"),
			tr("The host was not found. Please check the "
			"host name and port settings."));
		emit connectionFailedSignal();
		break;
	case QAbstractSocket::ConnectionRefusedError:
		
		QMessageBox::information(NULL, tr("Client"),
			tr("The connection was refused by the peer. "
			"Make sure the fortune server is running, "
			"and check that the host name and port "
			"settings are correct."));
		emit connectionFailedSignal();
		break;
	default:
		QMessageBox::information(NULL, tr("Client"),
			tr("For unknown reasons, connected failed"));
		emit connectionFailedSignal();
	}
}

void Links::ServerDisconnected()
{
	emit disconnectedSignal();
}

void Links::loginRequest(const LoginInformation &li)
{
	requestKind = LOGIN;
	logInf = li;
	newConnect();
}

void Links::registerRequest(const UserInformation &usin)
{
	requestKind = REGISTER;
	userInf = usin;
	newConnect();
}

void Links::quitRequest(const QString &acc)
{
	requestKind = QUIT;
	myAccount = acc;
	newConnect();
}

void Links::messageRequest(const Message &mes)
{
	requestKind = TALK;
	message = mes;
	newConnect();
}

void Links::checkConnectionRequest()
{
	requestKind = CHECK_CONNECTION;
	newConnect();
}

void Links::checkMessageRequest(const QString &acc)
{
	requestKind = CHECK_MESSAGE;
	myAccount = acc;
	newConnect();
}

void Links::addFriendRequest(const Message &mes)
{
	requestKind = ADD_FRIEND;
	message = mes;
	newConnect();
}

void Links::getFriendRequest(const QString &acc)
{
	requestKind = GET_FRIEND_INFORMATION;
	myAccount = acc;
	newConnect();
}

void Links::deleteFriendRequest(const QString &peer)
{
	requestKind = DELETE_FRIEND;
	peerAcc = peer;
	newConnect();
}

void Links::getUserRequest(const QString &acc)
{
	requestKind = GET_USER_INFORMATION;
	myAccount = acc;
	newConnect();
}

void Links::changeInformationRequest(const UserInformation &usin)
{
	requestKind = CHANGE_INFORMATION;
	userInf = usin;
	newConnect();
}

void Links::changeRemarkRequest(const Message &mes)
{
	requestKind = CHANGE_REMARK;
	message = mes;
	newConnect();
}

void Links::changePasswordRequest(const TempStrings &temp)
{
	requestKind = CHANGE_PASSWORD;
	tempStr = temp;
	newConnect();
}

void Links::changeStatusRequest(const QString &acc, const qint32 n)
{
	requestKind = CHANGE_STATUE;
	myAccount = acc;
	status = n;
	newConnect();
}
