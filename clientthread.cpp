#include "clientthread.h"
#include "clientrecvexception.h"
ClientThread::ClientThread(SOCKET client_socket, QObject *parent) :
    QThread(parent)
{
    mSocket = client_socket;
    mTerminated = false;
    setAuthenticated(false);
    ftpFileSystem = NULL;
    mIsUTF8 = Settings::getInstance()->getForceUtf8();
    mPassiveDataSocket = INVALID_SOCKET;
    mRenameBeginned = false;
}


bool ClientThread::isAuthenticated(){
    return mIsUserAuthenticated;
}

void ClientThread::setAuthenticated(bool authenticated){
    mIsUserAuthenticated = authenticated;
}

void ClientThread::run(){
    qDebug() << "Thread id=" << QThread::currentThreadId();
    u_long flag = 0;
    ioctlsocket(mSocket, FIONBIO, &flag);
    // отправл€ем клиенту приветствие
    sendString(FTPProtocol::getInstance()->getResponse(220,""));

    while(true)
    {
        QString s = recvString();
        qDebug() << "<<" << s.trimmed();
        if (s == NULL)
            break;
        QByteArray array (s.toStdString().c_str());
        analizeCommand(array);

        if (mTerminated){
            break;
        }
    }
    // если мы здесь, то произошел выход из цикла по
    // причине возращени€ функцией recv ошибки Ц
    // соединение клиентом разорвано
    //nclients--; // уменьшаем счетчик активных клиентов
   // printf("-disconnect\n"); PRINTNUSERS

    // закрываем сокет
    closesocket(mSocket);
    qDebug() << "Close client";
    emit oncloseconnection();
}

void ClientThread::closeconnection(){
    mTerminated = true;
    closesocket(mSocket);
}

int ClientThread::sendString(QString mes){
    if (!mes.endsWith("\r\n"))
        mes += "\r\n";
    qDebug() << ">>" << mes.trimmed();
    QByteArray ba = mes.toAscii();
    const char *data = ba.constData();
    return send(mSocket,data,mes.length(),0);
}

void ClientThread::sendList()
{
    SOCKET conn;
    conn  = openDataConnection();
    if (conn == INVALID_SOCKET)
    {
        sendString(FTPProtocol::getInstance()->getResponse(425));
        return;
    }
    QString s;
    s = ftpFileSystem->listDir();
    int pos = 0;
    int sendBytes;
    QByteArray ba = toEncoding(s);
    const char* buf = ba.constData();
    qDebug()<< ba.size();
    int size = ba.size();
    int bytesToSend;
    do
    {
       bytesToSend = (size-pos);
       bytesToSend  = (bytesToSend> BUF_LENGTH) ? BUF_LENGTH: bytesToSend;
       sendBytes = send(conn,&buf[pos],bytesToSend,0);
       if (sendBytes == 0 || sendBytes == -1)
           break;
       pos += sendBytes;
    }
    while(pos < size);

    shutdown(conn,SD_BOTH);
    closesocket(conn);
}

QString ClientThread::recvString(){
      char buff[BUF_LENGTH];
      int bytesreaded;
      bytesreaded = recv(mSocket,buff, BUF_LENGTH,0);
      qDebug() << bytesreaded;
      if (bytesreaded != SOCKET_ERROR){
          buff[bytesreaded] = '\0';
          return QString(buff);
      }
      else
      {
          qDebug() << "Error listen " + QString("%1").arg(WSAGetLastError()) ;
      }
      return NULL;
}

void ClientThread::analizeCommand(QByteArray &bytearray){
    QString userName;
    if (bytearray.contains("USER")) {
        QRegExp rx("^USER\\s(.*)\r\n");
        rx.indexIn(bytearray);
        userName = rx.cap(1);
        mUser = User::getUser(userName);
        sendString(FTPProtocol::getInstance()->getResponse(331));
        return;
    }

    if (bytearray.contains("PASS")) {
        QRegExp rx("^PASS\\s(.*)\r\n");
        rx.indexIn(bytearray);
        QString pass = rx.cap(1);
        if (mUser.isNull())
        {
            sendString(FTPProtocol::getInstance()->getResponse(503,"PASS send before USER"));
        }
        else
        {
            if (mUser.auth(pass))
            {
                // logged in
                 sendString(FTPProtocol::getInstance()->getResponse(230));
                 setAuthenticated(true);
                 if (ftpFileSystem != NULL)
                    delete ftpFileSystem;
                 ftpFileSystem = new FtpFileSystem(mUser.getFolder(), mUser.getFileAccess());
            }
            else
            {
                // incorrect
                 sendString(FTPProtocol::getInstance()->getResponse(530));
            }
        }
        return;
    }
    if (isAuthenticated())
    {
        // RNFR -> RNTO sequence
        if (mRenameBeginned){
            if (bytearray.contains("RNTO")){
                QRegExp rx("^RNTO\\s(.*)\r\n");
                rx.indexIn(fromEncoding(bytearray));
                QString newName = rx.cap(1);
                mRenameBeginned = false;
                if (ftpFileSystem->rename(mRenameOldName, newName))
                    sendString(FTPProtocol::getInstance()->getResponse(250));
                else
                    sendString(FTPProtocol::getInstance()->getResponse(550));
                return;
            }
            sendString(FTPProtocol::getInstance()->getResponse(503));
            return;
        }
        if (bytearray.contains("SYST")){
            QString syst("Windows Type : L8");
            sendString(FTPProtocol::getInstance()->getResponse(215, syst));
            return;
        }
        if (bytearray.contains("FEAT")){
            QString syst("211-Features:\n\rMDTM\n\rREST STREAM\n\rSIZE\n\rMLST type*;size*;modify*;\n\rMLSD\n\rUTF8\n\rCLNT\n\rMFMT\n\r211 End");
            sendString(syst);
            return;
        }
        if (bytearray.contains("HELP")){
            QString syst("HELP OK");
            sendString(FTPProtocol::getInstance()->getResponse(214, syst));
            return;
        }
        if (bytearray.contains("PWD")){
            sendString(FTPProtocol::getInstance()->getResponse(257, toEncoding("\""+ftpFileSystem->getWorkingDirectory()+"\"")));
            return;
        }
        if (bytearray.contains("OPTS")){
            QRegExp rx("^OPTS ([\\w\\s]+)");
            rx.indexIn(bytearray);
            QRegExp rx2("^UTF8 (\\w+)");
            rx2.indexIn(rx.cap(1));
            if (rx2.cap(1) == "ON")
            {
                mIsUTF8 = true;
            }
            if (rx2.cap(1) == "OFF")
            {
                mIsUTF8 = false;
            }
            sendString(FTPProtocol::getInstance()->getResponse(200));
            return;
        }
        if (bytearray.contains("TYPE")){
            // set transfer type
            QRegExp rx("^TYPE (\\w)( (\\w))?");
            rx.indexIn(bytearray);
            qDebug() << "type" << rx.cap(1) << rx.cap(3);
            mType = rx.cap(1);
            sendString(FTPProtocol::getInstance()->getResponse(200));
            return;
            if (mType == "I")
            {
                sendString(FTPProtocol::getInstance()->getResponse(200));
            }
            else
            {
                sendString(FTPProtocol::getInstance()->getResponse(550));
            }
            return;
        }
        if (bytearray.contains("PORT")){
            mIsActiveMode = true;
            QRegExp rx("^PORT (\\d+),(\\d+),(\\d+),(\\d+),(\\d+),(\\d+)");
            rx.indexIn(bytearray);
            int p1,p2;
            QString buf(rx.cap(5));
            bool flag;
            p1 = rx.cap(5).toInt(&flag);
            p2 = rx.cap(6).toInt(&flag);
            QString addr = rx.cap(1)+"."+rx.cap(2)+"."+rx.cap(3)+"."+rx.cap(4);
            active_addr = addr;
            active_port = p1*256+p2;
            sendString(FTPProtocol::getInstance()->getResponse(200, "Port ok"));
            return;
        }

        if (bytearray.contains("LIST")){
            sendString(FTPProtocol::getInstance()->getResponse(150));
            sendList();
            sendString(FTPProtocol::getInstance()->getResponse(226));
            return;
        }
        if (bytearray.contains("QUIT")){
            sendString(FTPProtocol::getInstance()->getResponse(221));
            closeconnection();
            return;
        }
        if (bytearray.contains("CDUP")){
            if (ftpFileSystem->cdUp())
                sendString(FTPProtocol::getInstance()->getResponse(250));
            else
                sendString(FTPProtocol::getInstance()->getResponse(550));
            return;
        }
        if (bytearray.contains("CWD")){
            QRegExp rx("^CWD\\s(.*)\r\n");
            rx.indexIn(fromEncoding(bytearray));
            QString subFolder = rx.cap(1);
            if (ftpFileSystem->changeDir(subFolder))
                sendString(FTPProtocol::getInstance()->getResponse(250));
            else
                sendString(FTPProtocol::getInstance()->getResponse(550));
            return;
        }
        if (bytearray.contains("RETR")){
            QRegExp rx("^RETR\\s(.*)\r\n");
            rx.indexIn(fromEncoding(bytearray));
            QString filename = rx.cap(1);
            QString fullFileName = ftpFileSystem->getFileRead(filename);
            if (fullFileName != NULL)
            {
                sendString(FTPProtocol::getInstance()->getResponse(150));
                sendFile(fullFileName);
            }
            else
            {
                sendString(FTPProtocol::getInstance()->getResponse(550,"Permission denied"));
            }
            return;
        }
        if (bytearray.contains("STOR")){
            QRegExp rx("^STOR\\s(.*)\r\n");
            rx.indexIn(fromEncoding(bytearray));
            QString filename = rx.cap(1);
            QString fullFileName = ftpFileSystem->getFileWrite(filename);
            if (fullFileName != NULL)
            {
                sendString(FTPProtocol::getInstance()->getResponse(150));
                recvFile(fullFileName);
            }
            else
            {
                sendString(FTPProtocol::getInstance()->getResponse(550,"Permission denied"));
            }
            return;
        }
        if (bytearray.contains("DELE")){
            QRegExp rx("^DELE\\s(.*)\r\n");
            rx.indexIn(fromEncoding(bytearray));
            QString filename = rx.cap(1);
            if (ftpFileSystem->deleteFile(filename))
                sendString(FTPProtocol::getInstance()->getResponse(250));
            else
                sendString(FTPProtocol::getInstance()->getResponse(550));
            return;
        }
        if (bytearray.contains("MKD")){
            QRegExp rx("^MKD\\s(.*)\r\n");
            rx.indexIn(fromEncoding(bytearray));
            QString dirName = rx.cap(1);
            if (ftpFileSystem->mkDir(dirName))
                sendString(FTPProtocol::getInstance()->getResponse(250));
            else
                sendString(FTPProtocol::getInstance()->getResponse(550));
            return;
        }
        if (bytearray.contains("PASV")){
            mIsActiveMode = false;
            selectPassivePort();
            return;
        }
        if (bytearray.contains("SIZE")){
            QRegExp rx("^SIZE\\s(.*)\r\n");
            rx.indexIn(fromEncoding(bytearray));
            QString fileName = rx.cap(1);
            qint64 size;
            if (ftpFileSystem->getSize(fileName, &size))
            {
                sendString(FTPProtocol::getInstance()->getResponse(250, QString::number(size)));
            }
            else
            {
               sendString(FTPProtocol::getInstance()->getResponse(550));
            }
            return;
        }
        if (bytearray.contains("MDTM")){
            QRegExp rx("^MDTM\\s(.*)\r\n");
            rx.indexIn(fromEncoding(bytearray));
            QString fileName = rx.cap(1);
            QString sdate = ftpFileSystem->getLastModified(fileName);
            if (sdate != NULL)
            {
                sendString(FTPProtocol::getInstance()->getResponse(250, sdate));
            }
            else
            {
               sendString(FTPProtocol::getInstance()->getResponse(550));
            }
            return;
        }
        if (bytearray.contains("RNFR")){
            QRegExp rx("^RNFR\\s(.*)\r\n");
            rx.indexIn(fromEncoding(bytearray));
            mRenameOldName = rx.cap(1);

            if (ftpFileSystem->exist(mRenameOldName) && ftpFileSystem->isWritable(mRenameOldName) != NULL)
            {
                sendString(FTPProtocol::getInstance()->getResponse(350));
                mRenameBeginned = true;
            }
            else
                sendString(FTPProtocol::getInstance()->getResponse(550, "Permission denied"));
            return;
        }
    sendString(FTPProtocol::getInstance()->getResponse(500));
    }
    else
        sendString(FTPProtocol::getInstance()->getResponse(530));
}

    void ClientThread::sendFile(const QString &filename){

        SOCKET conn = openDataConnection();
        if (conn == INVALID_SOCKET)
        {
            sendString(FTPProtocol::getInstance()->getResponse(425));
            return;
        }
        char buff[1024];
        int bytesReaded;
        QFile f(filename);
        if (!f.open(QIODevice::ReadOnly))
        {
            sendString(FTPProtocol::getInstance()->getResponse(550,"Can't open file"));
            return;
        }
        while( (bytesReaded = f.read(buff,1024)) && (bytesReaded != -1))
        {
            send(conn,buff,bytesReaded,0);
        }
        f.close();
        shutdown(conn,SD_BOTH);
        closesocket(conn);
        sendString(FTPProtocol::getInstance()->getResponse(226));
    }

    QString getAddrFormat(QString ip, int port){
        int lowpartport = port % 256;
        int highpartport = port / 256;
        QRegExp rx("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)");
        rx.indexIn(ip);
       return QString("(%1,%2,%3,%4,%5,%6)").arg(rx.cap(1)).arg(rx.cap(2)).arg(rx.cap(3)).arg(rx.cap(4)).
                arg(highpartport).arg(lowpartport);
    }

    void ClientThread::recvFile(const QString &filename){

        SOCKET conn = openDataConnection();
        if (conn == INVALID_SOCKET)
        {
            sendString(FTPProtocol::getInstance()->getResponse(425));
            return;
        }
        char buff[1024];
        int bytesReaded;
        QFile f(filename);
        if (!f.open(QIODevice::WriteOnly))
        {
            sendString(FTPProtocol::getInstance()->getResponse(550,"Can't open file"));
            return;
        }
        while( (bytesReaded = recv(conn, buff, 1024,0)) && (bytesReaded != -1))
        {
             f.write(buff, bytesReaded);
        }
        f.close();
        shutdown(conn,SD_BOTH);
        closesocket(conn);
        sendString(FTPProtocol::getInstance()->getResponse(226));
    }

   ClientThread::~ClientThread()
   {
       delete ftpFileSystem;

   }

   QByteArray ClientThread::toEncoding(const QString &s)
   {
       if (mIsUTF8)
           return s.toUtf8();
       return s.toAscii();

   }

   QString ClientThread::fromEncoding(const QByteArray &s){
       if(mIsUTF8)
           return QString::fromUtf8(s.data());
                   return QString::fromAscii(s.data());
   }

   // open new data connection
   SOCKET ClientThread::openDataConnection(){
       if (mIsActiveMode)
       {
           struct hostent *hp;
           unsigned int addr;
           struct sockaddr_in server;
           SOCKET conn;
           conn=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
           if(conn==INVALID_SOCKET)
                   return INVALID_SOCKET;
                   if(inet_addr(active_addr.toAscii().data())==INADDR_NONE)
           {
                   hp=gethostbyname(active_addr.toAscii().data());
           }
           else
           {
                   addr=inet_addr(active_addr.toAscii().data());
                   hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
           }
           if(hp==NULL)
           {
                   closesocket(conn);
                   return INVALID_SOCKET;
           }
           server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
           server.sin_family=AF_INET;
           server.sin_port=htons(active_port);
           if(::connect(conn,(struct sockaddr*)&server,sizeof(server)))
           {
                   closesocket(conn);
                   return INVALID_SOCKET;
           }
           return conn;
       }
       else
       {
           return mPassiveDataSocket;

       }
   }
   QString ClientThread::getLocalIp()
   {
       HOSTENT *hp=NULL;
       struct sockaddr_in source;
       char hostname[128];

       gethostname(hostname, 128);
       hp = gethostbyname(hostname);

       if(hp == NULL)
       {
       return NULL;
       }

       memcpy(&(source.sin_addr),hp->h_addr,hp->h_length);
       source.sin_family = hp->h_addrtype;

       return inet_ntoa(source.sin_addr);
   }

   void ClientThread::selectPassivePort(){
       // Passive mode
       SOCKET conn;
       mPassiveDataSocket = INVALID_SOCKET;
       for (int port = BEGIN_DATA_PORT; port < END_DATA_PORT; port++)
       {
           if ( SOCKET_ERROR == (conn=socket(AF_INET,SOCK_STREAM,0)))
               {

                    continue;
               }

           sockaddr_in local_addr;
           local_addr.sin_family=AF_INET;
           local_addr.sin_port=htons(port);
           local_addr.sin_addr.s_addr=0;
           if (SOCKET_ERROR == bind(conn,(sockaddr *) &local_addr, sizeof(local_addr)))
           {
                return;
           }

           if (listen(conn, 1))
           {
                 // ќшибк
                 return;
           }
           SOCKET client_socket;    // сокет дл€ клиента
           sockaddr_in client_addr;    // адрес клиента
           int client_addr_size=sizeof(client_addr);

           QString saddr = QString("Entering Passive Mode " + getAddrFormat(getLocalIp(),port));
           sendString(FTPProtocol::getInstance()->getResponse(227, saddr));
           client_socket=accept(conn, (sockaddr *)&client_addr, &client_addr_size);
           closesocket(conn);
           mPassiveDataSocket = client_socket;
           return;
       }

   }


