#include "settings.h"

Settings *Settings::mInstance = NULL;

Settings *Settings::getInstance(){
    if (mInstance == NULL)
        mInstance = new Settings;
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
    QFile file("settings.xml");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream(&file) << domDoc.toString();
        file.close();
        return true;
    }
    return false;
}

bool Settings::load(){
    return true;
}

bool Settings::addUser(User& user){
    users.append(user);
    return save();
}
