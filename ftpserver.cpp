#include "ftpserver.h"
FtpServer::FtpServer(QObject *parent) :
    QObject(parent)
{
    mSTATUS = STOPED;
    clients_count = 0;
    emit clientschanged(clients_count);
}




void FtpServer::start(){
    // create ftp thread
    if (mSTATUS == STOPED){
        ftpcore = new FTPCore();
        QObject::connect(ftpcore, SIGNAL(onstarted()),  SLOT(started()));
        QObject::connect(ftpcore, SIGNAL(onstopped()), SLOT(stoped()));
        QObject::connect(ftpcore, SIGNAL(onnewconnection(const QString&)), SLOT(newconnection(const QString&)));
        QObject::connect(ftpcore, SIGNAL(onerror(const QString&)), SLOT(servererror(const QString&)));
        QObject::connect(ftpcore,SIGNAL(oncloseconnection()),SLOT(connectionclosed()));
        ftpcore->start();
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
   Settings::getInstance();
   clients_count = 0;
   emit clientschanged(clients_count);
}

void FtpServer::stoped(){
   emit onClose("Сервер остановлен");
   mSTATUS = STOPED;
   clients_count = 0;
   ftpcore->wait();
   delete ftpcore;
   ftpcore = NULL;
}

void FtpServer::newconnection(const QString& ip){
    emit onEvent("Новое подключение ip: " + ip);
    clients_count++;
    emit clientschanged(clients_count);
}


void FtpServer::servererror(const QString& s){
    qDebug() << "Error - "+s;
    emit onError(s);
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


void FtpServer::connectionclosed(){
    emit onEvent("Соединение с клиентом закрыто");
    clients_count--;
    emit clientschanged(clients_count);
}
