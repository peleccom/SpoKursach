#ifndef FTPSERVER_H
#define FTPSERVER_H
#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include  <ftpcore.h>
#include <myutils.h>
#include <QThread>




class FtpServer : public QObject
{
    Q_OBJECT

public:
    explicit FtpServer(QObject *parent = 0);
    ~FtpServer();
    void start(); // start server
    void stop(); // stop server
    STATUS getStatus();
signals:
    void onStarted(QString);
    void onError(QString);
    void onClose(QString);
    void onEvent(QString);
public slots:
    void started();
    void stoped();
    void newconnection(const QString&);
    void servererror(const QString&);

private:
    STATUS mSTATUS;
    FTPCore *ftpcore;
    QThread *mainthread;
    int clients_count;



};

#endif // FTPSERVER_H
