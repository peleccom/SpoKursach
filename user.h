#ifndef USER_H
#define USER_H
#include <QString>
#include <QCryptographicHash>

#define CRYPT_SOUL "6LyOb"

class User
{
public:
    // return user or null if no such user
    // вернет обьект пользователя если он существует
    static User getUser(const QString &username);
    User(const User &other);
    QString getName();
    bool auth(const QString &pass);
    bool isAuth();
private:
    User();
    QString getHash(const QString &plainText);
    QString mUserName;
    QString mPassswordHash;
    bool mIsAuth;

};

#endif // USER_H
