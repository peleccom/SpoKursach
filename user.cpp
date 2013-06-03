#include "user.h"

User::User()
{
    mIsBad = true;
}

User::User(const QString &userName, const QString &passHash, const QString &folder, FileAccess fileAccess)
{
    mIsBad= true;
    mUserName = userName;
    mPassswordHash = passHash;
    mFolder = folder;
    mFileAccess = fileAccess;
    if (userName == "anonymous" && passHash.isEmpty() )
    {
        mIsAnonymousAccessed = true;
    }
    else
    {
        mIsAnonymousAccessed = false;
    }
}

QString User::getName() const{
    return mUserName;
}

User::User(const User &other){
    this->mIsAuth = other.mIsAuth;
    this->mPassswordHash = other.mPassswordHash;
    this->mUserName = other.mUserName;
    this->mFileAccess = other.mFileAccess;
    this->mIsBad = other.mIsBad;
    this->mFolder = other.mFolder;
    this->mIsAnonymousAccessed = other.mIsAnonymousAccessed;
}

User User::getUser(const QString &username){
    User user = Settings::getInstance()->getUser(username);
    user.mIsBad = false;
    return user;
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

bool User::isNull(){
    return mIsBad;
}

QString User::getPasswordHash(){
    return mPassswordHash;
}

QString User::getFolder(){
    return mFolder;
}

FileAccess User::getFileAccess(){
    return mFileAccess;
}

