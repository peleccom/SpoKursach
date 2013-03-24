#ifndef MYUTILS_H
#define MYUTILS_H
#include <QDebug>
#include <users.h>
#include <ftpprotocol.h>
typedef enum {
    STOPED,
    STARTED,
    STARTING
} STATUS;

typedef enum {
    ACTIVE,
    PASSIVE
} MODE;


class MyUtils
{
public:
    MyUtils();
};

#endif // MYUTILS_H
