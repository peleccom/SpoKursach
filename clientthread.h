#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H
#include <winsock.h>
#include <QThread>
#include <myutils.h>
#include <QCryptographicHash>
#include <ftpfilesystem.h>
#include <QFile>
#define BUF_LENGTH 1024
#define BEGIN_DATA_PORT 6000
#define END_DATA_PORT 6100
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
    SOCKET passiveDataSocket;
    bool terminated;
    bool mIsUserAuthenticated;
    bool isActiveMode;
    bool isUTF8;
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
    void sendList();
    SOCKET openDataConnection();
    void recvFile(const QString &filename);
    void sendFile(const QString &filename);
    void selectPassivePort();
    QByteArray toEncoding(const QString& s);
    QString fromEncoding(const QByteArray& s);
};

#endif // CLIENTTHREAD_H
