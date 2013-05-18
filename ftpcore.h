#ifndef FTPCORE_H
#define FTPCORE_H

#include <QThread>
#include <clientthread.h>
#include <winsock.h>
#include <myutils.h>
#define CONTROL_PORT 21
#define MAX_CLIENTS 100
#include <QList>

class FTPCore : public QObject
{
    Q_OBJECT
public:
    explicit FTPCore(QObject *parent = 0);
    ~FTPCore();
signals:
    void onshutdownserver();
    void onstarted();
    void onstopped();
    void onerror(const QString& s);
    void onnewconnection(const QString& ip);
    void oncloseconnection();
public slots:
     void run();
     void stop();
     void connectionclosed();
private:

    bool InitWinsock();

    QThread thread;
    WSADATA wsaData;
    SOCKET msocket;
    int server_status;
    int nclients;


    bool terminated;


};

#endif // FTPCORE_H
