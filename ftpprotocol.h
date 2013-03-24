#ifndef FTPPROTOCOL_H
#define FTPPROTOCOL_H
#include <myutils.h>
#include <QHash>
class FTPProtocol
{
public:

    static FTPProtocol* getInstance();
    static void destroy();
    QString getResponse(int code, QString customMessage="");
 private:
    static FTPProtocol *instance;
    QHash<int, QString> mResponseCodes;
    FTPProtocol();
    ~FTPProtocol();

};
//
#endif // FTPPROTOCOL_H
