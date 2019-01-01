/*
 * 服务器窗口
 */

#ifndef WIDGET_H_
#define WIDGET_H_

#include "constant.h"
#include "server.h"

class Widget : public QWidget
{
	Q_OBJECT
private:
	QLabel *label;
	QPushButton *quitButton;
	QPushButton *orderButton;
	Server *server;

public:
	Widget(QWidget *parent = 0);
	~Widget();
};

#endif
