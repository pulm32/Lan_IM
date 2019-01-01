#include "database.h"

ServerDatabase::ServerDatabase()
{

    db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    //db.setHostName("localhost");
    //db.setUserName("root");
    //db.setPassword("9461lc");
    db.setDatabaseName("qchartdatabase"); //数据库连接命名
    bool create = !QFile::exists("qchartdatabase");
	if (!db.open())
	{
		QMessageBox::warning(NULL, tr("Error"), 
			tr("Can not open the sqlite database"));
		exit(2);
	}

	if(create)
    {
		createTable();
        QMessageBox::warning(NULL, tr("haha"),
            tr("Create successful！"));
    }
}

ServerDatabase::~ServerDatabase()
{

}

void ServerDatabase::createTable()
{
	QSqlQuery query;
	//用户表（帐号，密码，呢称，头像编号，状态，手机号码，电话号码，
	//生日，城市，自我描述）
	query.exec("create table users(account varchar(21) primary key, "
		"password varchar(21) not null, "
		"nickname nvarchar(41) not null, "
		"avatarnumber integer not null, "
		"status integer not null, "
		"mobilenumber varchar(21) not null, "
		"phonenumber varchar(21) not null, "
		" birthday varchar(20) not null, "
		"city nvarchar(41) not null, "
		"about nvarchar(201) not null)");
	errorSQLOrder(query, "createTable1");

	//好友表（好友A，好友B，关系，备注）
	query.exec("create table friends(one varchar(21) not null, "
		"two varchar(21) not null, "
		"friendKind integer not null, "
		"remark varchar(101) not null)");
	errorSQLOrder(query, "createTable2");

	//临时信息表（信息类型，发送者，接收者，信息）
	query.exec("create table save(kind integer not null, "
		"sender varchar(21) not null, "
		"receiver varchar(21) not null, "
		"message varchar(5001))");
	errorSQLOrder(query, "createTable3");
}

void ServerDatabase::errorSQLOrder(QSqlQuery query, QString mark)
{
	//如果SQL语句错误，就弹出警告信息
	if(!query.isActive())
	{
		QString str = query.lastError().text() + "\n" + mark;
		QMessageBox::warning(NULL, "ERROR", str);
	}
}

void ServerDatabase::initiDatabase()
{
	QSqlQuery query;
	query.exec("update users set status=0");
	errorSQLOrder(query, "initiDatabase1");
}

void ServerDatabase::loginSuccess(QSqlQuery &query, const LoginInformation &logInf,
								  QVector<FriendInformation> &friendsVec)
{
	friendsVec.clear();
	//先获得自己的信息
	FriendInformation fri;
	fri.account = logInf.account;
	fri.status = logInf.status;
	fri.name = query.value(NAME).toString();
	fri.avatarNumber = query.value(AVATAR_NUMBER).toInt();
	fri.about = query.value(ABOUT).toString();
	fri.friendKind = MYSELF;
	friendsVec.push_back(fri);

	//更新自己的状态
	query.prepare("update users set status=:sta where account=:acc");
	query.bindValue(":acc", logInf.account);
	query.bindValue(":sta", QString::number(logInf.status));
	query.exec();
	errorSQLOrder(query, "loginSuccess1");

	//通过外连接获得好友的信息
	query.prepare("select * from users left join friends on "
		"friends.two=users.account where friends.one=:acc");
	query.bindValue(":acc", logInf.account);
	query.exec();
	errorSQLOrder(query, "loginSuccess2");

	while(query.next())
	{
		fri.friendKind = query.value(12).toInt();
		if(0 == fri.friendKind)
			continue;

		fri.account = query.value(ACCOUNT).toString();
		fri.name = query.value(NAME).toString();
		fri.avatarNumber = query.value(AVATAR_NUMBER).toInt();
		fri.status = query.value(STATUS).toInt();
		fri.about = query.value(ABOUT).toString();
		fri.remark = query.value(13).toString();
		friendsVec.push_back(fri);
	}
}

void ServerDatabase::addMessageRequest(const Message &mes)
{
	QSqlQuery query;
	//将信息存入数据库
	query.prepare("insert into save values(:kind, :sender, :receiver, :text)");
	query.bindValue(":kind", QString::number(mes.kind));
	query.bindValue(":sender", mes.sender);
	query.bindValue(":receiver", mes.receiver);
	query.bindValue(":text", mes.text);
	query.exec();
	errorSQLOrder(query, "addMessageRequest1");
}

qint32 ServerDatabase::loginRequest(const LoginInformation &logInf,
									QVector<FriendInformation> &friendsVec)
{
	QSqlQuery query;
	int have = 0;

	//判断有没有这个用户
	query.prepare("select * from users where account=:account");
    query.bindValue(":account", logInf.account);
	query.exec();
	errorSQLOrder(query, "loginRequest1");
	if(query.next())
		have++;
	if(0 == have)
		return LOGIN_NO_ACCOUNT;
	//判断密码是否正确
	else if(query.value(PASSWORD).toString() != logInf.password)
		return LOGIN_WRONG_PWD;
	//判断用户是否已经登录了
	else if(query.value(STATUS) != OFFLINE)
		return HAVE_LOGINED;
	else
	{
		loginSuccess(query, logInf, friendsVec);
		return LOGIN_SUCCESS; 
	}
}

qint32 ServerDatabase::registerRequest(const UserInformation &userInf)
{
	qint32 replyKind;
	QSqlQuery query;
	query.prepare("select count(account) from users where account=:account");
	query.bindValue(":account", userInf.account);
	query.exec();
	errorSQLOrder(query, "registerRequest1");
	query.next();
	//判断该用户名是否已经注册
	if(query.value(0).toInt() != 0)
	{
		replyKind = REGISTER_EXIST;
		return replyKind;
	}
	//添加用户
	query.prepare("insert into users values(:acc, :pwd, :name, :avatar, :status,"
		":mobile, :phone, :birthday, :city, :about)");
	query.bindValue(":acc", userInf.account);
	query.bindValue(":pwd", userInf.password);
	query.bindValue(":name", userInf.nickName);
	query.bindValue(":avatar", QString::number(userInf.avatarNumber));
	query.bindValue(":status", QString::number(userInf.status));
	query.bindValue(":mobile", userInf.mobileNumber);
	query.bindValue(":phone", userInf.phoneNumber);
	query.bindValue(":birthday", userInf.birthday);
	query.bindValue(":city", userInf.city);
	query.bindValue(":about", userInf.aboutMyself);
	query.exec();
	errorSQLOrder(query, "registerRequest2");
	replyKind = REGISTER_SUCCESS;
	return replyKind;
}

qint32 ServerDatabase::quitRequest(const QString &acc)
{
	QSqlQuery query;
	//更新用户状态
	query.prepare("update users set status=0 where account=:acc");
	query.bindValue(":acc", acc);
	query.exec();
	errorSQLOrder(query, "quitRequest1");
	changeStatusRequest(acc, OFFLINE);
	return 0;
}

qint32 ServerDatabase::messageRequest(const Message &mes)
{
	addMessageRequest(mes);
	return 0;
}

qint32 ServerDatabase::addFriendRequest(const Message &mes)
{
	QSqlQuery query;
	if(REQUEST_FRIEND == mes.kind)
		return requestFriend(mes);

	if(AGREE_FRIEND == mes.kind)
	{
		agreeFriend(mes);
		return GET_FRIEND_SUCCESS;
	}

	else if(DISAGREE_FRIEND == mes.kind)
	{
		disagreeFriend(mes);
		return DISAGREE_FRIEND;
	}
	return 0;
}

qint32 ServerDatabase::checkRequest(const QString &acc,
									QVector<Message> &messageVec)
{
	QSqlQuery query;
	Message mes;
	messageVec.clear();
	//判断是否有发送给acc的信息
	query.prepare("select * from save where receiver=:rec");
	query.bindValue(":rec", acc);
	query.exec();
	errorSQLOrder(query, "checkRequest1");
	while(query.next())
	{
		mes.kind = query.value(KIND).toInt();
		mes.sender = query.value(SENDER).toString();
		mes.receiver = query.value(RECEIVER).toString();
		mes.text = query.value(TEXT).toString();
		messageVec.push_back(mes);
	}
	if(messageVec.isEmpty())
		return NO_MESSAGE;

	//将发送出去的信息删除
	query.prepare("delete from save where receiver=:rec");
	query.bindValue(":rec", acc);
	query.exec();
	errorSQLOrder(query, "checkRequest2");
	return HAVE_MESSAGE;
}

qint32 ServerDatabase::getFriendInfRequest(const QString &acc, FriendInformation &fri)
{
	QSqlQuery query;
	query.prepare("select * from users where account=:acc");
	query.bindValue(":acc", acc);
	query.exec();
	errorSQLOrder(query, "getFriendRequest1");
	while(query.next())
	{
		fri.account = query.value(ACCOUNT).toString();
		fri.name = query.value(NAME).toString();
		fri.avatarNumber = query.value(AVATAR_NUMBER).toInt();
		fri.status = query.value(STATUS).toInt();
		fri.about = query.value(ABOUT).toString();
		fri.friendKind = VERIFYING;
		fri.remark.clear();
	}
	return GET_FRIEND_SUCCESS;
}

qint32 ServerDatabase::deleteFriendRequest(const QString &myAcc, const QString &peerAcc)
{
	QSqlQuery query;
	//删除这两个用户的好友关系
	query.prepare("delete from friends where one=:one and two=:two");
	query.bindValue(":one", myAcc);
	query.bindValue(":two", peerAcc);
	query.exec();
	errorSQLOrder(query, "deleteFriendRequest1");

	query.prepare("delete from friends where one=:one and two=:two");
	query.bindValue(":one", peerAcc);
	query.bindValue(":two", myAcc);
	query.exec();
	errorSQLOrder(query, "deleteFriendRequest2");
	return DELETE_FRIEND_SUCCESS;
}

qint32 ServerDatabase::getUserInfRequest(const QString &acc, UserInformation &userInf)
{
	QSqlQuery query;
	query.prepare("select * from users where account=:acc");
	query.bindValue(":acc", acc);
	query.exec();
	errorSQLOrder(query, "getUserInfRequest1");
	while(query.next())
	{
		userInf.account = query.value(ACCOUNT).toString();
		userInf.password = query.value(PASSWORD).toString();
		userInf.nickName = query.value(NAME).toString();
		userInf.avatarNumber = query.value(AVATAR_NUMBER).toInt();
		userInf.status = query.value(STATUS).toInt();
		userInf.mobileNumber = query.value(MOBILE_NUMBER).toString();
		userInf.phoneNumber = query.value(PHONE_NUMBER).toString();
		userInf.birthday = query.value(BIRTHDAY).toString();
		userInf.city = query.value(CITY).toString();
		userInf.aboutMyself = query.value(ABOUT).toString();
	}
	return GET_USER_INF_SUCCESS;
}

qint32 ServerDatabase::changeInformationRequest(const UserInformation &userInf)
{
	QSqlQuery query;
	//先删除这个用户，再重新插入
	query.prepare("delete from users where account=:acc");
	query.bindValue(":acc", userInf.account);
	query.exec();
	errorSQLOrder(query, "changeInformationRequest1");
	query.prepare("insert into users values(:acc, :pwd, :name, :avatar, :status,"
		":mobile, :phone, :birthday, :city, :about)");
	query.bindValue(":acc", userInf.account);
	query.bindValue(":pwd", userInf.password);
	query.bindValue(":name", userInf.nickName);
	query.bindValue(":avatar", QString::number(userInf.avatarNumber));
	query.bindValue(":status", QString::number(userInf.status));
	query.bindValue(":mobile", userInf.mobileNumber);
	query.bindValue(":phone", userInf.phoneNumber);
	query.bindValue(":birthday", userInf.birthday);
	query.bindValue(":city", userInf.city);
	query.bindValue(":about", userInf.aboutMyself);
	query.exec();
	errorSQLOrder(query, "changeInformationRequest2");
	return CHANGE_INFORMATION_SUCCESS;
}

qint32 ServerDatabase::requestFriend(const Message &mes)
{
	QSqlQuery query;
	query.prepare("select count(account) from users where account=:account");
	query.bindValue(":account", mes.receiver);
	query.exec();
	errorSQLOrder(query, "requestFriend1");
	query.next();
	if(0 == query.value(0).toInt())
		return FRIEDN_NO_ACCOUNT;

	query.prepare("select count() from friends where one=:one and two=:two");
	query.bindValue(":one", mes.sender);
	query.bindValue(":two", mes.receiver);
	query.exec();
	errorSQLOrder(query, "requestFriend2");
	query.next();
	if(0 != query.value(0).toInt())
		return ALREAD_FRIENDS;

	query.prepare("insert into friends values(:one, :two, 0, '')");
	query.bindValue(":one", mes.sender);
	query.bindValue(":two", mes.receiver);
	query.exec();
	errorSQLOrder(query, "requestFriend3");
	query.prepare("insert into friends values(:one, :two, 0, '')");
	query.bindValue(":one", mes.receiver);
	query.bindValue(":two", mes.sender);
	query.exec();
	errorSQLOrder(query, "requestFriend4");
	return FRIEND_REQUESTED;
}

void ServerDatabase::agreeFriend(const Message &mes)
{
	QSqlQuery query;
	//更新好友关系
	query.prepare("update friends set friendKind=1 where one=:one and two=:two");
	query.bindValue(":one", mes.receiver);
	query.bindValue(":two", mes.sender);
	query.exec();
	errorSQLOrder(query, "agreeFriend1");
	query.prepare("update friends set friendKind=1 where one=:one and two=:two");
	query.bindValue(":one", mes.sender);
	query.bindValue(":two", mes.receiver);
	query.exec();
	errorSQLOrder(query, "agreeFriend2");
}

void ServerDatabase::disagreeFriend(const Message &mes)
{
	QSqlQuery query;
	//删除该好友关系
	query.prepare("delete from friends where one=:one and two=:two");
	query.bindValue(":one", mes.receiver);
	query.bindValue(":two", mes.sender);
	query.exec();
	errorSQLOrder(query, "disagreeFriend1");

	query.prepare("delete from friends where one=:one and two=:two");
	query.bindValue(":one", mes.sender);
	query.bindValue(":two", mes.receiver);
	query.exec();
	errorSQLOrder(query, "disagreeFriend2");
}

qint32 ServerDatabase::changeRemarkRequset(const Message &message)
{
	QSqlQuery query;
	//更新好友备注
	query.prepare("update friends set remark=:remark where one=:one and two=:two");
	query.bindValue(":one", message.sender);
	query.bindValue(":two", message.receiver);
	query.bindValue(":remark", message.text);
	query.exec();
	errorSQLOrder(query, "changeRemarkRequset1");
	return CHANGE_REMARK_SUCCESS;
}

qint32 ServerDatabase::changePasswordRequest(const TempStrings &tempStr)
{
	QSqlQuery query;
	//判断旧密码是否正确
	query.prepare("select * from users where account=:acc");
	query.bindValue(":acc", tempStr.three);
	query.exec();
	errorSQLOrder(query, "changePasswordRequest1");
	query.next();
	if(query.value(PASSWORD).toString() != tempStr.one)
		return OLD_PWD_IS_WRONG;
	//更新密码
	query.prepare("update users set password=:pwd where account=:acc");
	query.bindValue(":pwd", tempStr.two);
	query.bindValue(":acc", tempStr.three);
	query.exec();
	errorSQLOrder(query, "changePasswordRequest2");
	return CHANGE_PWD_SUCCESS;
}

qint32 ServerDatabase::changeStatusRequest(const QString &acc, qint32 status)
{
	QSqlQuery query;
	query.prepare("update users set status=:status where account=:acc");
	query.bindValue(":acc", acc);
	query.bindValue(":status", QString::number(status));
	query.exec();
	errorSQLOrder(query, "changeStatusRequest1");
	return 0;
}

void ServerDatabase::getFriendsAccount(const QString &acc, 
									   QVector<QString> &friVec)
{
	friVec.clear();
	QSqlQuery query;
	query.prepare("select * from friends where one=:acc");
	query.bindValue(":acc", acc);
	query.exec();
	errorSQLOrder(query, "getFriendsAccount1");

	while(query.next())
	{
		if(query.value(2).toInt() != 0)
			friVec.push_back(query.value(1).toString());
	}
}
