/*
 * 这个文件主要是定义了一个常用的结构体与常量
 */
#ifndef CONSTANT_H_
#define CONSTANT_H_


#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#include <QMessageBox>

struct ServerNode
{
	QString ipAddress;			//服务器地址
	int port;					//服务器窗口
	ServerNode()
	{	port = 0;	}
};

//存储聊天的字体和颜色
struct SaveFile
{
	QFont font;
	QColor color;
	friend QDataStream & operator<< (QDataStream &qos, const SaveFile &sf)
	{
		qos << sf.font << sf.color;
		return qos;
	}
	friend QDataStream & operator>> (QDataStream &qis, SaveFile &sf)
	{
		qis >> sf.font >> sf.color;
		return qis;
	}
};

//用户详细信息
struct UserInformation
{
	QString account;			//帐号
	QString password;			//密码
	QString nickName;			//呢称
	int avatarNumber;			//头像编号
	int status;					//登录状态
	QString mobileNumber;		//手机号码
	QString phoneNumber;		//电话号码
	QString birthday;			//生日
	QString city;				//所在城市
	QString aboutMyself;		//个人描述

	UserInformation()
	{	avatarNumber = status = 0;	}

	//重载输入输出操作符
	friend QDataStream & operator<< (QDataStream &qos, const UserInformation &pi)
	{	
		qos << pi.account << pi.password << pi.nickName << pi.avatarNumber
			<< pi.status << pi.mobileNumber 
			<< pi.phoneNumber << pi.birthday<< pi.city << pi.aboutMyself;
		return qos;
	}
	friend QDataStream & operator>> (QDataStream &qis, UserInformation &pi)
	{	
		qis >> pi.account >> pi.password >> pi.nickName >> pi.avatarNumber
			>> pi.status >> pi.mobileNumber 
			>> pi.phoneNumber >> pi.birthday >> pi.city >> pi.aboutMyself;	
		return qis;
	}
};

//储存在各种小窗口中填写的信息
struct TempStrings
{
	QString one;
	QString two;
	QString three;
	friend QDataStream & operator<< (QDataStream &qos, const TempStrings &ti)
	{
		qos << ti.one << ti.two << ti.three;
		return qos;
	}
	friend QDataStream & operator>> (QDataStream &qis, TempStrings &ti)
	{
		qis >> ti.one >> ti.two >> ti.three;
		return qis;
	}
};

//登录信息
struct LoginInformation
{
	QString account;
	QString password;
	int status;

	LoginInformation()
	{	status = 0;	}
	friend QDataStream & operator<< (QDataStream &qos, LoginInformation &li)
	{	
		qos << li.account << li.password << li.status;	
		return qos;
	}
	friend QDataStream & operator>> (QDataStream &qis, LoginInformation &li)
	{	
		qis >> li.account >> li.password >> li.status;	
		return qis;
	}
};

//好友信息
struct FriendInformation
{
	QString account;
	QString name;
	int avatarNumber;
	int status;
	QString about;
	int friendKind;			//好友类型
	QString remark;			//好友备注

	FriendInformation()
	{	avatarNumber = status = friendKind = 0;	}

	friend QDataStream & operator<< (QDataStream &qos, const FriendInformation &fi)
	{	
		qos << fi.account << fi.name << fi.avatarNumber << fi.status 
			<< fi.about << fi.friendKind << fi.remark;	
		return qos;
	}
	friend QDataStream & operator>> (QDataStream &qis, FriendInformation &fi)
	{	
		qis >> fi.account >> fi.name >> fi.avatarNumber >> fi.status 
			>> fi.about >> fi.friendKind >> fi.remark;	
		return qis;
	}
};

struct Message
{
	int kind;				//消息类型
	QString sender;			//发送者
	QString receiver;		//接收者
	QString text;			//消息内容

	Message()
	{	kind = 0;	}
	friend QDataStream & operator<< (QDataStream &qos, const Message &mes)
	{
		qos << mes.kind << mes.sender << mes.receiver << mes.text;
		return qos;
	}
	friend QDataStream & operator>> (QDataStream &qis, Message &mes)
	{
		qis >> mes.kind >> mes.sender >> mes.receiver >> mes.text;
		return qis;
	}
};

//头像尺寸
const int AVATAR_SIZE = 50;

enum
{
	LOGIN = 1,						//登录
	REGISTER = 2,					//注册
	TALK = 3,						//保存信息
	CHECK_MESSAGE = 4,				//检查有无给自己的信息（登录时检查）
	ADD_FRIEND = 5,					//添加好友
	GET_FRIEND_INFORMATION = 6,		//获取好友信息
	DELETE_FRIEND = 7,				//删除好友
	GET_USER_INFORMATION = 8,		//获取用户（好友）信息
	CHANGE_INFORMATION = 9,			//改变自己的信息
	CHANGE_REMARK = 10,				//改变（好友）备注
	CHANGE_PASSWORD = 11,			//修改密码
	CHANGE_STATUE = 12,				//改变自身状态
	CHECK_CONNECTION = 19,			//检查是否能与服务器连接
	QUIT = 20						//退出
};

enum
{
	LOGIN_SUCCESS = 11,				//登录成功
	LOGIN_NO_ACCOUNT = 12,			//没有这个用户名
	LOGIN_WRONG_PWD = 13,			//密码错误
	HAVE_LOGINED = 14,				//该用户已经登录了
	GET_ALL_SUCCESS = 16,

	REGISTER_EXIST = 21,			//该帐号已被注册了
	REGISTER_SUCCESS = 22,			//注册成功

	NO_MESSAGE = 41,				//没有信息
	HAVE_MESSAGE = 42,				//有信息
	HAVE_TALK_MESSAGE = 43,

	FRIEND_REQUESTED = 51,			//好友请求
	FRIEDN_NO_ACCOUNT = 52,			//没有这个用户名
	ALREAD_FRIENDS = 53,			//回应好友请求

	GET_FRIEND_SUCCESS = 61,			//获得好友资料
	DELETE_FRIEND_SUCCESS = 62,				//删除好友成功
	GET_USER_INF_SUCCESS = 63,				//获得（好友的）详细资料
	CHANGE_INFORMATION_SUCCESS = 64,	//改变自身资料成功
	CHANGE_REMARK_SUCCESS = 65,			//修改备注成功

	OLD_PWD_IS_WRONG = 70,				//旧密码是错的
	CHANGE_PWD_SUCCESS = 71,			//修改密码成功
};

enum
{
	MESSAGE = 1,				//普通信息
	REQUEST_FRIEND = 2,			//请求添加好友
	AGREE_FRIEND = 3,			//同意好友请求
	DISAGREE_FRIEND = 4,		//不同意好友请求
	END_FRIEND = 5,				//好友添加结束
	BE_DELETED = 8,				//自己被好友删除了
	TALK_MESSAGE = 9			//聊天信息
};

enum
{
	OFFLINE = 0,			//离线
	ONLINE = 1,				//在线
	TALK_WITH_ME = 2,		//Q我吧
	BUSY = 3,				//忙碌
	LEAVE = 4,				//离开
	DISTURB = 5,			//请勿打扰
	STEALTH = 6				//隐身
};

#endif
