#include "ftpfilesystem.h"

FtpFileSystem::FtpFileSystem(const QString &basedir, FileAccess fileAccess)
{

    this->mBaseDir = basedir;
    this->mFileAccess = fileAccess;
    this->mCurDir = "/";
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
    QString fullPath = appendPath(mBaseDir, mCurDir);
    QDir dir(fullPath);
    if (!(dir.exists()))
        return NULL;

    dir.setSorting(QDir::Size | QDir::Reversed);
    QString buffer;
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName()=="." || fileInfo.fileName() == "..")
            continue;
         QString dirLabel = fileInfo.isDir()?"d":"-";
         bool writable = isWritable(fileInfo.fileName());
         bool readable =  isReadable(fileInfo.fileName());
         QString sfileSize = fileInfo.isDir()?"512":QString::number(fileInfo.size());
         QDateTime dt = fileInfo.lastModified();
         QString lastModified = formatDate(dt);
//         qDebug() << fileInfo.fileName();
         buffer = buffer % QString("%1%5%6-r--r-- 1 root root %2 %3 %4\r\n").arg(dirLabel).arg(sfileSize).arg(lastModified).arg(fileInfo.fileName())
                .arg(readable?"r":"-").arg(writable?"w":"-");
    }
    return buffer;
}


bool FtpFileSystem::cdUp(){
    int position = mCurDir.lastIndexOf("/");
    if (position >= 0)
    {
        mCurDir.remove(position, mCurDir.size() - position);
        if (!mCurDir.size())
            mCurDir = "/";
        return true;
    }
    return false;
}

QString FtpFileSystem::getWorkingDirectory(){
    return mCurDir;
}

bool FtpFileSystem::changeDir(const QString &subfolder){
    QString newDir;
    QString newFullPathDir;
    if (subfolder.startsWith("/"))
    {
        newDir = QDir::cleanPath(subfolder);
        newDir.replace("/..","/");
        newFullPathDir = appendPath(mBaseDir,newDir);
        if ((QDir(newFullPathDir).exists()) && (newFullPathDir.size() >= mBaseDir.size()))
        {
            mCurDir = newDir;
            return true;
        }
        else
            return false;
    }
    else
    {
        newDir = appendPath(mCurDir, subfolder);
        newDir.replace("//","/");
        newDir.replace("/..","/");
        newFullPathDir = appendPath(mBaseDir,newDir);
        if ((QDir(newFullPathDir).exists()) && (newFullPathDir.size() >= mBaseDir.size()))
        {
            mCurDir = newDir;
            return true;
        }
        else
            return false;
    }
}

// Return file real path
QString FtpFileSystem::getFileFullPath(const QString& filename)
{
    return  appendPath(mBaseDir,appendPath(mCurDir,filename));
}

bool FtpFileSystem::deleteFile(const QString &filename){
    QString fullFileName = getFileFullPath(filename);
    QFile f(fullFileName);
    QDir d(fullFileName);
    if (isDeleteable(filename)){
        if (d.exists())
        {
            return d.rmdir(fullFileName);
        }
        if (f.exists())
        {
            return f.remove();
        }
    }
    return false;
}

bool FtpFileSystem::mkDir(const QString &filename){

     QString fullDirPath = getFileFullPath(filename);
     QDir dir;
     return dir.mkdir(fullDirPath);
}

bool FtpFileSystem::getSize(const QString &filename,qint64 *size )
{
        QString fullFileName = getFileFullPath(filename);
        QFile f(fullFileName);
        if (f.exists())
        {
            *size = f.size();
            return true;
        }
        return false;

}

QString FtpFileSystem::getLastModified(const QString &filename)
{
        QString fullFileName = getFileFullPath(filename);
        QFile f(fullFileName);
        if (f.exists())
        {
            QFileInfo fi(f);
            return fi.lastModified().toString("yyyyMMddhhmmss");
        }
        return NULL;

}


bool FtpFileSystem::isReadable(const QString &fileName){
    QFileInfo fi(getFileFullPath(fileName));
    return fi.isReadable() && mFileAccess.aread;
}

bool FtpFileSystem::isWritable(const QString &fileName){
    QFileInfo fi(getFileFullPath(fileName));
    return (fi.isWritable() && mFileAccess.awrite) || (!fi.exists() && mFileAccess.awrite);
}

bool FtpFileSystem::isDeleteable(const QString &fileName){
    QFileInfo fi(getFileFullPath(fileName));
    return fi.isWritable() && mFileAccess.adelete;
}

bool FtpFileSystem::isAppendable(const QString &fileName){
    return isWritable(fileName) && isReadable(fileName) && mFileAccess.aappend;
}

bool FtpFileSystem::rename(const QString &oldName, const QString &newName){
    QString oldFullPath = getFileFullPath(oldName);
    QString newFullPath = getFileFullPath(newName);
    return QFile::rename(oldFullPath, newFullPath);
}

bool FtpFileSystem::exist(const QString &fileName){
    QFile f(getFileFullPath(fileName));
    return f.exists();
}

QString FtpFileSystem::getFileRead(const QString &filename){
    if (isReadable(filename))
        return getFileFullPath(filename);
    return NULL;
}

QString FtpFileSystem::getFileWrite(const QString &filename){
    if (isWritable(filename))
        return getFileFullPath(filename);
    else
        return NULL;
}
