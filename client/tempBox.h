/*
 * 各种小窗口的基类
 */

#ifndef TEMPBOX_H_
#define TEMPBOX_H_
#include <QWidget>
#include "constant.h"
#include "constant.h"
#include "links.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>


class tempBox : public QWidget
{
	Q_OBJECT
private:
	//输入栏的个数
	int n;
	//输入栏和标题栏的指针
	QLabel *firstLabel;
	QLabel *secondLabel;
	QLabel *thirdLabel;
	QLineEdit *firstLineEdit;
	QLineEdit *secondLineEdit;
	QLineEdit *thirdLineEdit;
	QPushButton *OKPushButton;
	QPushButton *closePushButton;

public:
	tempBox(int temp, QWidget *parent);
	virtual ~tempBox() = 0;

	//设置各栏目的标题
	void setLabelName(const QString &one="",
		const QString &two="",
		const QString &three="");
	//获取用户输入的信息
	TempStrings getInformation() const;
	//将输入的信息设置为密码风格
	void setPasswordStyle();
	//将所有栏目设置可读（不可用）
	void setAllEnabled(bool enable);

	public slots:
		virtual void clickedOKButton() = 0;
		void clickedCloseButton();
};

#endif
