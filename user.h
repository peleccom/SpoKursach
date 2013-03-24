#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = 0);
signals:

public slots:

private:
    QString m_strName;
    QString m_strPassword;
    bool m_bAccountDisabled;

    bool m_bAllowDownload;
    bool m_bAllowUpload;
    bool m_bAllowRename;
    bool m_bAllowDelete;
    bool m_bAllowCreateDirectory;
};

#endif // USER_H
