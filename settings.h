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
    Settings();
    static Settings *getInstance();
    static void destroy();
    bool save();
    bool load();
    bool addUser(User &user);
    User getUser(const QString &userName);
private:
    static Settings * mInstance;
    QList<User> users;
    bool utf8;

};

#endif // SETTINGS_H
