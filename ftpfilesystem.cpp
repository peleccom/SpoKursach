#include "ftpfilesystem.h"

FtpFileSystem::FtpFileSystem(const QString &basedir)
{

    this->baseDir = basedir;
        this->curDir = "/";
    this->baseDir = "C:";
}

QString FtpFileSystem::appendPath(const QString& path1, const QString& path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}

QString FtpFileSystem::formatDate(const QDateTime &dateTime)
{
    QString Months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                        "Jul","Aug","Sep","Oct","Nov","Dec"};
    QString s = dateTime.toString("%1 d hh:mm").arg(Months[dateTime.date().month()-1]);
    return s;
}

QString FtpFileSystem::listDir(){
    QDir dir(appendPath(baseDir, curDir));
    dir.setSorting(QDir::Size | QDir::Reversed);
    QString buffer;
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
         QString dirLabel = fileInfo.isDir()?"d":"-";
         QString sfileSize = fileInfo.isDir()?"512":QString::number(fileInfo.size());
         QDateTime dt = fileInfo.lastModified();
         QString lastModified = formatDate(dt);
         buffer = buffer % QString("%1rw-r--r-- 1 root root %2 %3  %4\r\n").arg(dirLabel).arg(sfileSize).arg(lastModified).arg(fileInfo.fileName());

    }
    return buffer;
}


bool FtpFileSystem::cdUp(){
    int position = curDir.lastIndexOf("/");
    if (position >= 0)
    {
        curDir.remove(position, curDir.size() - position);
        if (!curDir.size())
            curDir = "/";
        return true;
    }
    return false;
}

QString FtpFileSystem::getWorkingDirectory(){
    return curDir;
}

bool FtpFileSystem::changeDir(const QString &subfolder){
    if (subfolder.startsWith("/"))
    {
        curDir = QDir::cleanPath(subfolder);
        return true;
    }
    else
    {
        curDir = appendPath(curDir, subfolder);
        curDir.replace("//","/");
        return true;
    }
}

QString FtpFileSystem::getFile(const QString& filename)
{
    return  appendPath(baseDir,appendPath(curDir,filename));
}
