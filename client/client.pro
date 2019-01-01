######################################################################
# client.pro 客户端
######################################################################

TEMPLATE = app
TARGET = client
INCLUDEPATH += .

QT += network
QT   += core gui sql
QT   +=widgets
# Input
HEADERS += addFriend.h \
           changeInf.h \
           changePwd.h \
           chatRoom.h \
           constant.h \
           friendbutton.h \
           informationBox.h \
           inputTextEdit.h \
           links.h \
           loginBox.h \
           register.h \
           remark.h \
           showUserInf.h \
           tempBox.h \
           window.h
FORMS += chatRoom.ui informationBox.ui loginBox.ui window.ui
SOURCES += addFriend.cpp \
           changeInf.cpp \
           changePwd.cpp \
           chatRoom.cpp \
           friendbutton.cpp \
           informationBox.cpp \
	   inputTextEdit.cpp \
           links.cpp \
           loginBox.cpp \
           main.cpp \
           register.cpp \
           remark.cpp \
           showUserInf.cpp \
           tempBox.cpp \
           window.cpp

TRANSLATIONS += client.ts

RESOURCES +=

DISTFILES +=
