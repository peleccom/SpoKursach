#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H
#include <winsock.h>
#include <QThread>
#include <myutils.h>
#include <QCryptographicHash>
#define BUF_LENGTH 1024
class ClientThread : public QThread
{
    Q_OBJECT
public:
    explicit ClientThread(SOCKET client_socket, QObject *parent = 0);
    void run();

signals:
    void onerror(const QString &);
public slots:
    void closeconnection();
private:
    SOCKET msocket;
    bool terminated;
    QCryptographicHash *hash;
    int sendString(QString mes, SOCKET sock);
    QString recvString();
    void analizeCommand(QByteArray&);

};

#endif // CLIENTTHREAD_H
