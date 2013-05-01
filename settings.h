#ifndef SETTINGS_H
#define SETTINGS_H
#include <QList>
#include <user.h>
#include <QDomDocument>
#include <myutils.h>
class Settings
{
public:
    Settings();
    static Settings *getInstance();
    static void destroy();
    bool save();
    bool load();
    bool addUser(User &user);
private:
    static Settings * mInstance;
    QList<User> users;
    bool utf8;

};

#endif // SETTINGS_H
