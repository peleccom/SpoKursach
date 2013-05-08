#include "settings.h"

Settings *Settings::mInstance = NULL;

Settings *Settings::getInstance(){
    if (mInstance == NULL)
    {
       mInstance = new Settings;
       mInstance->load();
    }
    return mInstance;
}

void Settings::destroy(){
    if (mInstance != NULL)
        delete mInstance;
}

Settings::Settings()
{
    FileAccess fileAccess;
    fileAccess.aappend = true;
    fileAccess.adelete = false;
    fileAccess.aread = true;
    fileAccess.awrite = true;
    users.append(User("sasha","sasha","D://Films",fileAccess));
    users.append(User("sasdsda","ssdha","C:/tmp",fileAccess));
}

bool parseBool(const QString &value){
    QString val = value.toLower();
    if (val == "true" || val == "yes" || val == "1")
        return true;
    return false;
}

QDomElement createUserNode(QDomDocument &doc, User& user){
    QDomElement e_user = doc.createElement("user");
    e_user.setAttribute("pass",user.getPasswordHash());
    e_user.setAttribute("name",user.getName());
    QDomElement e_p = doc.createElement("folder");
    e_p.appendChild(doc.createTextNode(user.getFolder()));
    FileAccess fileAcess = user.getFileAccess();
    e_p.setAttribute("fwrite",fileAcess.awrite);
    e_p.setAttribute("fread",fileAcess.aread);
    e_p.setAttribute("fdelete",fileAcess.adelete);
    e_p.setAttribute("fappend",fileAcess.aappend);
    e_user.appendChild(e_p);
    return e_user;
}

User parseUserNode(const QDomElement &el){

    QString folder;
    FileAccess fileAccess;
    QDomNode node = el.firstChild();
    while(!node.isNull()){
        if (node.toElement().tagName() == "folder"){
            QDomElement folderElement = node.toElement();
            folder = folderElement.text();
            fileAccess.awrite = parseBool(folderElement.attribute("fwrite","0"));
            fileAccess.aread = parseBool(folderElement.attribute("fread","0"));
            fileAccess.adelete = parseBool(folderElement.attribute("fdelete","0"));
            fileAccess.aappend = parseBool(folderElement.attribute("fappend","0"));
        }
        node = node.nextSibling();
    }
    return User(el.attribute("name",""), el.attribute("pass",""),folder,fileAccess);
}

bool Settings::save(){
    User user;
    QDomDocument domDoc("settings");
    QDomElement e_settings = domDoc.createElement("settings");
    QDomElement e_utf8 = domDoc.createElement("forceUTF8");
    e_utf8.appendChild(domDoc.createTextNode(utf8?"true":"false"));
    e_settings.appendChild(e_utf8);
    QDomElement e_users = domDoc.createElement("users");
    e_settings.appendChild(e_users);
    foreach(user ,users)
    {
        e_users.appendChild(createUserNode(domDoc,user));
    }

    domDoc.appendChild(e_settings);
    QFile file(CONFIG_FILE);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream(&file) << domDoc.toString();
        file.close();
        return true;
    }
    return false;
}

bool Settings::load(){
    utf8 = false; // default value
    users.clear();
    // parsing
    QFile f(CONFIG_FILE);
    if (!f.open(QIODevice::ReadOnly))
        {f.close();return false;}
    QDomDocument domDoc;
    if (!domDoc.setContent(&f))
        return false;
    QDomElement root = domDoc.documentElement();
    if (root.tagName() != "settings")
        return false;
    QDomNode node = root.firstChild();
    while(!node.isNull()){
        if (node.toElement().tagName() == "forceUTF8")
        {
            utf8 = parseBool(node.toElement().text());
            qDebug() <<"Setting: utf8 - "<< node.toElement().text() ;
        }
        if (node.toElement().tagName() == "users"){
            QDomNode userNode = node.firstChild();
            while (!userNode.isNull()){
                if (userNode.toElement().tagName() == "user")
                {
                    users.append(parseUserNode(userNode.toElement()));
                }
                userNode = userNode.nextSibling();
            }
        }
    node = node.nextSibling();
    }
    f.close();
    return true;
}

bool Settings::addUser(User& user){
    users.append(user);
    return save();
}

User Settings::getUser(const QString &userName){
    User user;
    foreach(user,users){
        if (user.getName() == userName){
            user.mIsBad = false;
            user.mIsAuth = false;
            return user;
        }

    }
    return User();
}


QList<User> Settings::listUsers(){
    return users;
}

bool Settings::getForceUtf8(){
    return utf8;
}

void Settings::setForceUtf8(bool value){
    utf8 = value;
    save();
}

bool Settings::removeUser(int index){
    if (index >= 0 && index < users.size())
    {
        users.removeAt(index);
        return true;
    }
    return false;
}
