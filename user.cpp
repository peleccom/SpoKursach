#include "user.h"

User::User()
{
    mIsBad = true;
}

User::User(const QString &userName){
    mIsBad = false;
    mIsAuth = false;

    mUserName = userName;
    mPassswordHash = getHash("sasha");
    mIsAnonymousAccessed = true;
}

QString User::getName(){

}

User::User(const User &other){
    this->mIsAuth = other.mIsAuth;
    this->mPassswordHash = other.mPassswordHash;
    this->mUserName = other.mUserName;
}

User User::getUser(const QString &username){
    User u(username);
    return u;
}

bool User::isAuth(){
    return mIsAuth;
}

QString User::getHash(const QString &plainText){
    return QString(QCryptographicHash::hash(((plainText + CRYPT_SOUL).toAscii()),QCryptographicHash::Md5).toHex());
}


bool User::auth(const QString &pass){
    QString enteredHash = getHash(pass);
    mIsAuth = false;
    if (mUserName == "anonymous" && mIsAnonymousAccessed){
        mIsAuth = true;
    }
    else
    {
        mIsAuth = (enteredHash == mPassswordHash);
    }
    return mIsAuth;
}

bool User::isBadObject(){
    return mIsBad;
}
