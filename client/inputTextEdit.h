/*
 * 自定义输入栏,重载了keyPressEvent
 */

#ifndef INPUTTEXTEDIT_H_
#define INPUTTEXTEDIT_H_
#include<QTextEdit>
#include "constant.h"


class InputTextEdit : public QTextEdit
{
	Q_OBJECT
protected:
	void keyPressEvent(QKeyEvent *event);

public:
	InputTextEdit(QWidget *parent=0);
	~InputTextEdit();

signals:
	void sendSignal();

};

#endif
