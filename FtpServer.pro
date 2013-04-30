#-------------------------------------------------
#
# Project created by QtCreator 2013-02-28T21:32:30
#
#-------------------------------------------------

QT       += core gui network

TARGET = FtpServer
TEMPLATE = app
LIBS += -lws2_32

SOURCES += main.cpp\
        mainwindow.cpp \
    ftpserver.cpp \
    clientthread.cpp \
    ftpcore.cpp \
    log.cpp \
    myutils.cpp \
    ftpprotocol.cpp \
    users.cpp \
    edituserdialog.cpp \
    clientrecvexception.cpp \
    ftpfilesystem.cpp \
    filetransferthread.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    ftpserver.h \
    clientthread.h \
    ftpcore.h \
    log.h \
    myutils.h \
    ftpprotocol.h \
    users.h \
    edituserdialog.h \
    clientrecvexception.h \
    ftpfilesystem.h \
    filetransferthread.h \
    user.h

FORMS    += mainwindow.ui \
    edituserdialog.ui

RESOURCES += \
    res.qrc


































