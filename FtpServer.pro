#-------------------------------------------------
#
# Project created by QtCreator 2013-02-28T21:32:30
#
#-------------------------------------------------

QT       += core gui network xml

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
    edituserdialog.cpp \
    ftpfilesystem.cpp \
    user.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    ftpserver.h \
    clientthread.h \
    ftpcore.h \
    log.h \
    myutils.h \
    ftpprotocol.h \
    edituserdialog.h \
    ftpfilesystem.h \
    user.h \
    settings.h

FORMS    += mainwindow.ui \
    edituserdialog.ui

RESOURCES += \
    res.qrc
RC_FILE = myapp.rc














































