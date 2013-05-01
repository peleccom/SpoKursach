#ifndef USER_H
#define USER_H
#include <QString>
#include <QCryptographicHash>
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include <myutils.h>
#define CRYPT_SOUL "6LyOb"

class User
{
public:
    User();
    User(const QString &userName, const QString &pass, const QString &folder, FileAccess fileAccess);
    // return user or null if no such user
    // вернет обьект пользователя если он существует
    static User getUser(const QString &username);
    static void listUsers();
    static void deleteUser(const QString &userName);
    static void saveUser(const QString& userName, const QString &pass, const QString &folder);
    User(const User &other);
    QString getName();
    bool auth(const QString &pass);
    bool isNull();
    bool isAuth();
    // to friend
    QString getFolder();
    QString getPasswordHash();
    FileAccess getFileAccess();
private:
    User(const QString &userName);
    QString getHash(const QString &plainText);
    QString mUserName;
    QString mPassswordHash;
    QString mFolder;
    bool mIsAuth;
    bool mIsBad;
    bool mIsAnonymousAccessed;
    FileAccess mFileAccess;

};

#endif // USER_H
