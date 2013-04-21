#ifndef FTPFILESYSTEM_H
#define FTPFILESYSTEM_H
#include <QString>
#include <QDir>
#include <QStringBuilder>
#include <QDateTime>
#include <QFile>
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
private:
    QString curDir;
    QString baseDir;
    QString formatDate(const QDateTime &dateTime);
};

#endif // FTPFILESYSTEM_H
