#ifndef FTPFILESYSTEM_H
#define FTPFILESYSTEM_H
#include <QString>
#include <QDir>
#include <QStringBuilder>
#include <QDateTime>
#include <QFile>
#include "myutils.h"
class FtpFileSystem
{
public:
    FtpFileSystem(const QString &basedir);
    QString listDir();
    QString appendPath(const QString& path1, const QString& path2);
    bool cdUp();
    bool changeDir(const QString & subfolder);
    QString getWorkingDirectory();
    QString getFile(const QString &filename);
    bool deleteFile(const QString &filename);
    bool mkDir(const QString &filename);
    bool getSize(const QString &filename, qint64 *size);
    QString getLastModified(const QString &filename);
    bool rename(const QString &oldName, const QString &newName);
    bool exist(const QString &fileName);
private:
    QString curDir;
    QString baseDir;
    QString formatDate(const QDateTime &dateTime);
    bool isWritable(const QString & fileName);
    bool isReadable(const QString & fileName);
};

#endif // FTPFILESYSTEM_H
