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
        QObject::connect(ftpcore, SIGNAL(onstopped()),mainthread,SLOT(quit()));
        QObject::connect(ftpcore, SIGNAL(onstarted()),  SLOT(started()));
        QObject::connect(ftpcore, SIGNAL(onstopped()), SLOT(stoped()));
        QObject::connect(ftpcore, SIGNAL(onnewconnection(const QString&)), SLOT(newconnection(const QString&)));
        QObject::connect(ftpcore, SIGNAL(onerror(const QString&)), SLOT(servererror(const QString&)));
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
   emit onStarted("������ �������");
   mSTATUS = STARTED;
   clients_count = 0;Settings set; set.save();
}

void FtpServer::stoped(){
   emit onClose("������ ����������");
   mSTATUS = STOPED;
   clients_count = 0;
   mainthread->wait();
   delete ftpcore;
   delete mainthread;
   ftpcore = NULL;
   mainthread = NULL;
}

void FtpServer::newconnection(const QString& ip){
    emit onEvent("����� ����������� ip: " + ip);
    clients_count ++;
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
