#ifndef FILETRANSFERTHREAD_H
#define FILETRANSFERTHREAD_H

#include <QThread>

class FileTransferThread : public QThread
{
    Q_OBJECT
public:
    explicit FileTransferThread(QObject *parent = 0);
    void run();

signals:

public slots:

};

#endif // FILETRANSFERTHREAD_H
