#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H
#include <winsock.h>
#include <QThread>
#include <myutils.h>
#include <ftpfilesystem.h>
#include <QFile>
#include <user.h>
#define BUF_LENGTH 1024
#define BEGIN_DATA_PORT 2090
#define END_DATA_PORT 3000
class ClientThread : public QThread
{
    Q_OBJECT
public:
    explicit ClientThread(SOCKET client_socket, QObject *parent = 0);
    ~ClientThread();
    void run();

signals:
    void onerror(const QString &);
    void onlog(const QString &);
public slots:
    void closeconnection();
private:
    SOCKET mSocket;
    SOCKET mPassiveDataSocket;
    bool mTerminated;
    bool mIsUserAuthenticated;
    bool mIsActiveMode;
    bool mIsUTF8;
    bool mRenameBeginned;
    QString mRenameOldName;
    QString mType;
    QString active_addr;
    User mUser;
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
    QString getLocalIp();
};

#endif // CLIENTTHREAD_H
