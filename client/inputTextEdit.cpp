/*
 * 自定义输入栏,重载了keyPressEvent
 */


#include "inputTextEdit.h"

InputTextEdit::InputTextEdit(QWidget *parent/* =0 */)
: QTextEdit(parent)
{

}

InputTextEdit::~InputTextEdit()
{

}

void InputTextEdit::keyPressEvent(QKeyEvent *event)
{
	//如果按下Ctrl+Enter，就发送信息，否则就按默认的方式来处理
	bool isSend = (Qt::Key_Return==event->key() || Qt::Key_Enter==event->key())
		&& (event->modifiers() & Qt::ControlModifier);

	if(isSend)
		emit sendSignal();
	else
		QTextEdit::keyPressEvent(event);
}
