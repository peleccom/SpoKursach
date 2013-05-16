#ifndef SETTINGS_H
#define SETTINGS_H
#include <QList>
#include <user.h>
#include <QDomDocument>
#include <myutils.h>
#define CONFIG_FILE "settings.xml"
class User;
class Settings
{
public:
    static Settings *getInstance();
    static void destroy();
    bool save();
    User getUser(const QString &userName);
    bool addUser(User &user);
    bool replaceUser(int index,User &user);
    QList<User> listUsers();
    bool getForceUtf8();
    void setForceUtf8(bool value);
    bool removeUser(int index);
private:
    Settings();
    bool load();
    static Settings * mInstance;
    QList<User> users;
    bool utf8;

};

#endif // SETTINGS_H
