#include "user.h"

User::User(QObject *parent) :
    QObject(parent)
{
    m_bAccountDisabled = FALSE;

    m_bAllowDownload = TRUE;
    m_bAllowUpload = FALSE;
    m_bAllowRename = FALSE;
    m_bAllowDelete = FALSE;
    m_bAllowCreateDirectory = FALSE;
}


