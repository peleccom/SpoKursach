#include "ftpserver.h"
FtpServer::FtpServer(QObject *parent) :
    QObject(parent)
{
    mSTATUS = STOPED;
    clients_count = 0;
}




void FtpServer::start(){
    // create ftp thread
    if (mSTATUS == STOPED){
        mainthread = new QThread();
        ftpcore = new FTPCore();
        QObject::connect(mainthread, SIGNAL(started()), ftpcore, SLOT(run()));
        QObject::connect(ftpcore, SIGNAL(onstarted()),  SLOT(started()));
        QObject::connect(ftpcore, SIGNAL(onstopped()), SLOT(stoped()));
        QObject::connect(ftpcore, SIGNAL(onnewconnection(QString)), SLOT(newconnection(QString)));
        QObject::connect(ftpcore, SIGNAL(onerror(QString)), SLOT(servererror(QString)));
        ftpcore->moveToThread(mainthread);
        mainthread->start();
        mSTATUS = STARTING;

    }
    else
    {
        // send stop signal
    }
}

void FtpServer::stop(){
    // stop ftp server
    if (mSTATUS == STARTED)
    {
        // send stop signal
        ftpcore->stop();
    }
}


void FtpServer::started(){
   emit onStarted("Сервер запущен");
   mSTATUS = STARTED;
   clients_count = 0;
}

void FtpServer::stoped(){
   emit onClose("Сервер остановлен");
   mSTATUS = STOPED;
   clients_count = 0;
   delete ftpcore;
   delete mainthread;
   ftpcore = NULL;
   mainthread = NULL;
}

void FtpServer::newconnection(QString ip){
    emit onEvent("Новое подключение ip: " + ip);
    clients_count ++;
}


void FtpServer::servererror(QString s){
    qDebug() << s;
    mSTATUS =  STOPED;
}

FtpServer::~FtpServer(){
    qDebug() << "~FTPServer";
    if (ftpcore != NULL && getStatus() ==  STARTED)
        ftpcore->stop();
}

STATUS FtpServer::getStatus(){
    return mSTATUS;
}
