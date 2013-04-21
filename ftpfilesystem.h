#ifndef FTPFILESYSTEM_H
#define FTPFILESYSTEM_H
#include <QString>
#include <QDir>
#include <QStringBuilder>
#include <QDateTime>
class FtpFileSystem
{
public:
    FtpFileSystem(const QString &basedir);
    QString listDir();
    QString appendPath(const QString& path1, const QString& path2);
    bool cdUp();
    bool changeDir(const QString & subfolder);
    QString getWorkingDirectory();
private:
    QString curDir;
    QString baseDir;
    QString formatDate(const QDateTime &dateTime);
};

#endif // FTPFILESYSTEM_H
