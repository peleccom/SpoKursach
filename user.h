#ifndef USER_H
#define USER_H
#include <QString>
#include <QCryptographicHash>
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include <myutils.h>
#include <settings.h>
#define CRYPT_SOUL "6LyOb"

class User
{
public:
    User();
    User(const User &other);
    // return user or null if no such user
    // вернет обьект пользователя если он существует
    static User getUser(const QString &username);
    static QString getHash(const QString &plainText);
    QString getName() const;
    bool auth(const QString &pass);
    bool isNull();
    bool isAuth();
    QString getFolder();
    QString getPasswordHash();
    FileAccess getFileAccess();
private:
    friend class Settings;
    friend class EditUserDialog;
    User(const QString &userName, const QString &passHash, const QString &folder, FileAccess fileAccess);
    QString mUserName;
    QString mPassswordHash;
    QString mFolder;
    bool mIsAuth;
    bool mIsBad;
    bool mIsAnonymousAccessed;
    FileAccess mFileAccess;

};

#endif // USER_H
