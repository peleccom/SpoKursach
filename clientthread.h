#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H
#include <winsock.h>
#include <QThread>
#include <myutils.h>
#include <QCryptographicHash>
#include <ftpfilesystem.h>
#include <QFile>
#define BUF_LENGTH 1024
class ClientThread : public QThread
{
    Q_OBJECT
public:
    explicit ClientThread(SOCKET client_socket, QObject *parent = 0);
    ~ClientThread();
    void run();

signals:
    void onerror(const QString &);
public slots:
    void closeconnection();
private:
    SOCKET msocket;
    bool terminated;
    bool mIsUserAuthenticated;
    bool isActiveMode;
    QString type;
    QString workingDirectory;
    QCryptographicHash *hash;
    QString active_addr;
    FtpFileSystem *ftpFileSystem;
    int active_port;
    int sendString(QString mes, SOCKET sock);
    QString recvString();
    void analizeCommand(QByteArray&);
    bool isAuthenticated();
    void setAuthenticated(bool);
    void newconnection(QString & anndr, int port);
    void transferFile(const QString &filename);
};

#endif // CLIENTTHREAD_H
