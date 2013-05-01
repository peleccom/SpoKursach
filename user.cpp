#include "user.h"

User::User()
{
    mIsBad = true;
}

User::User(const QString &userName, const QString &pass, const QString &folder, FileAccess fileAccess)
{
    mIsBad= true;
    mUserName = userName;
    mPassswordHash = getHash(pass);
    mFolder = folder;
    mFileAccess = fileAccess;
}

User::User(const QString &userName){
    mIsBad = false;
    mIsAuth = false;

    mUserName = userName;
    mPassswordHash = getHash("sasha");
    mIsAnonymousAccessed = true;
}

QString User::getName(){
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
    User u(username);

    return u;
}

void traverseNode(const QDomNode &node){
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull())
    {
        if (domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if (!domElement.isNull()){
                if (domElement.tagName() == "user")
                {
                    qDebug()<< "Attr: "<< domElement.attribute("number","");
                }
                else
                {
                   qDebug()<< "tagname" << domElement.tagName() << "Text\n"<< domElement.text();
                }
            }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }

}

void User::listUsers(){
    QDomDocument domDoc;
    QFile file("config.xml");
    if (!file.open(QIODevice::ReadOnly));
    {
        return;
    }
    if (domDoc.setContent(&file))
    {
        QDomElement domElement = domDoc.documentElement();
        traverseNode(domElement);
    }
    file.close();
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

