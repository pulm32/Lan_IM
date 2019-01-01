/*
 * 各种小窗口的基类
 */


#include "tempBox.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
tempBox::tempBox(int temp, QWidget *parent)
: QWidget(parent)
{
	Qt::WindowFlags flag = Qt::Window
		| Qt::WindowCloseButtonHint 
		| Qt::WindowMinimizeButtonHint;
	setWindowFlags(flag);

	//temp是输入栏的个数
	n = temp;
	OKPushButton = new QPushButton(tr("OK"), this);
	closePushButton = new QPushButton(tr("Cancle"), this);

	//设置主界面
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	QHBoxLayout *buttonLayout = new QHBoxLayout(this);
	buttonLayout->addStretch();
	buttonLayout->addWidget(OKPushButton);
	buttonLayout->addWidget(closePushButton);

	firstLabel = new QLabel(this);
	firstLineEdit = new QLineEdit(this);
	mainLayout->addWidget(firstLabel);
	mainLayout->addWidget(firstLineEdit);
	if(n >= 2)
	{
		secondLabel = new QLabel(this);
		secondLineEdit = new QLineEdit(this);
		mainLayout->addWidget(secondLabel);
		mainLayout->addWidget(secondLineEdit);
	}
	if(n >= 3)
	{
		thirdLabel = new QLabel(this);
		thirdLineEdit = new QLineEdit(this);
		mainLayout->addWidget(thirdLabel);
		mainLayout->addWidget(thirdLineEdit);
	}
	mainLayout->addStretch();
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	connect(OKPushButton, SIGNAL(clicked()),
		this, SLOT(clickedOKButton()));
	connect(closePushButton, SIGNAL(clicked()), 
		this, SLOT(clickedCloseButton()));
}

tempBox::~tempBox()
{

}

void tempBox::clickedCloseButton()
{
	close();
}

void tempBox::setLabelName(const QString &one/* = */, 
						   const QString &two/* = */, 
						   const QString &three/* = */)
{
	if(n>=1 && !one.isEmpty())
		firstLabel->setText(one);
	if(n>=2 && !two.isEmpty())
		secondLabel->setText(two);
	if(n>=3 && !three.isEmpty())
		thirdLabel->setText(three);
}

TempStrings tempBox::getInformation() const
{
	TempStrings temp;
	temp.one = firstLineEdit->text();
	if(n >= 2)
		temp.two = secondLineEdit->text();
	if(n >= 3)
		temp.three = thirdLineEdit->text();
	return temp;
}

void tempBox::setPasswordStyle()
{
	firstLineEdit->setEchoMode(QLineEdit::Password);
	if(n >= 2)
		secondLineEdit->setEchoMode(QLineEdit::Password);
	if(n >= 3)
		thirdLineEdit->setEchoMode(QLineEdit::Password);
}

void tempBox::setAllEnabled(bool enable)
{
	firstLineEdit->setEnabled(enable);
	if(n >= 2)
		secondLineEdit->setEnabled(enable);
	if(n >= 3)
		thirdLineEdit->setEnabled(enable);
	OKPushButton->setEnabled(enable);
	closePushButton->setEnabled(enable);
}
