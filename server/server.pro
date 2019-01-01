######################################################################
#
######################################################################

TEMPLATE = app
TARGET = server
DEPENDPATH += . GeneratedFiles
INCLUDEPATH += .

QT += network
QT  += core gui sql
QT +=widgets

# Input
HEADERS += clientsocket.h constant.h database.h server.h widget.h
SOURCES += clientSocket.cpp database.cpp main.cpp server.cpp widget.cpp
