/*
 * 数据库类
 */

#ifndef DATABASE_H_
#define DATABASE_H_
#include "constant.h"

class ServerDatabase : public QObject
{
private:
    QSqlDatabase db;

	//检查SQL语句的正确性
	void errorSQLOrder(QSqlQuery query, QString mark);
	//创建数据库
	void createTable();
	//登录成功
	void loginSuccess(QSqlQuery &query, const LoginInformation &logInf,
		QVector<FriendInformation> &friendsVec);
	//处理好友请求
	qint32 requestFriend(const Message &mes);
	void agreeFriend(const Message &mes);
	void disagreeFriend(const Message &mes);

public:
	ServerDatabase();
	~ServerDatabase();

	//处理从客户端发过来的各种请求
	qint32 loginRequest(const LoginInformation &logInf,
		QVector<FriendInformation> &friendsVec);
	qint32 registerRequest(const UserInformation &userInf);
	qint32 quitRequest(const QString &acc);
	qint32 messageRequest(const Message &mes);
	qint32 addFriendRequest(const Message &mes);
	qint32 checkRequest(const QString &acc, QVector<Message> &messageVec);
	qint32 getFriendInfRequest(const QString &acc, FriendInformation &fri);
	qint32 deleteFriendRequest(const QString &myAcc, const QString &peerAcc);
	qint32 getUserInfRequest(const QString &acc, UserInformation &userInf);
	qint32 changeInformationRequest(const UserInformation &userInf); 
	qint32 changeRemarkRequset(const Message &message);
	qint32 changePasswordRequest(const TempStrings &tempStr);
	qint32 changeStatusRequest(const QString &acc, qint32 status);
	qint32 getAllInformationRequest(const QString &acc, QVector<FriendInformation> 
		&friendsVec, QVector<Message> &messageVec);
	void addMessageRequest(const Message &mes);
	void getFriendsAccount(const QString &acc, QVector<QString> &friVec);

	//初始化数据库（将全部用户的状态设置为OFFLINE）
	void initiDatabase();
};

#endif
