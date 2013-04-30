#ifndef USER_H
#define USER_H
#include <QString>
#include <QCryptographicHash>

#define CRYPT_SOUL "6LyOb"

class User
{
public:
    User();
    // return user or null if no such user
    // вернет обьект пользователя если он существует
    static User getUser(const QString &username);
    User(const User &other);
    QString getName();
    bool auth(const QString &pass);
    bool isBadObject();
    bool isAuth();
private:
    User(const QString &userName);
    QString getHash(const QString &plainText);
    QString mUserName;
    QString mPassswordHash;
    bool mIsAuth;
    bool mIsBad;
    bool mIsAnonymousAccessed;

};

#endif // USER_H
