/*
 * 服务器窗口
 */


#include "widget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

Widget::Widget(QWidget *parent) 
: QWidget(parent)
{
	setWindowTitle("server");
	resize(200, 100);

	label = new QLabel;  
	quitButton = new QPushButton(tr("Quit"));
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(label);
	layout->addWidget(quitButton);
	setLayout(layout);

	server = new Server(this);
/*
    //获取本地IP
    QString ipAddress;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();  
	for (int i = 0; i < ipAddressesList.size(); ++i) 
	{  
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&  
			ipAddressesList.at(i).toIPv4Address())
		{  
			ipAddress = ipAddressesList.at(i).toString();  
			break;  
		}  
	}  
	if (ipAddress.isEmpty())  
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
*/
    QString ipAddress="10.100.5.82";
    //QString ipAddress="192.168.31.147";
	label->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"  
		"Run the Fortune Client example now.")  
		.arg(ipAddress).arg(server->serverPort()));  
	connect(quitButton, SIGNAL(clicked()), 
		this, SLOT(close())); 
}

Widget::~Widget()
{

}
