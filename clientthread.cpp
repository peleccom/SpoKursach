#include "clientthread.h"
#include "clientrecvexception.h"
ClientThread::ClientThread(SOCKET client_socket, QObject *parent) :
    QThread(parent)
{
    msocket = client_socket;
    terminated = false;
    setAuthenticated(false);
    hash = new QCryptographicHash(QCryptographicHash::Md5);
    workingDirectory = "/";
    ftpFileSystem = NULL;
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
    ioctlsocket(msocket, FIONBIO, &flag);
    // отправл€ем клиенту приветствие
    sendString(FTPProtocol::getInstance()->getResponse(220,""), msocket);

    while(true)
    {
        QString s = recvString();
        qDebug() << "Command received: '"<<s << "'";
        if (s == NULL)
            break;
        QByteArray array (s.toStdString().c_str());
        analizeCommand(array);

        if (terminated){
            break;
        }
    }
    // если мы здесь, то произошел выход из цикла по
    // причине возращени€ функцией recv ошибки Ц
    // соединение клиентом разорвано
    //nclients--; // уменьшаем счетчик активных клиентов
   // printf("-disconnect\n"); PRINTNUSERS

    // закрываем сокет
    closesocket(msocket);
    qDebug() << "Close client";
}

void ClientThread::closeconnection(){
    terminated = true;
}

int ClientThread::sendString(QString mes, SOCKET sock){
    if (!mes.endsWith("\r\n"))
        mes += "\r\n";
    return send(sock,mes.toAscii().data(),mes.length(),0);
}

void ClientThread::newconnection(QString &servername, int port)
{
    WSADATA wsaData;
    struct hostent *hp;
    unsigned int addr;
    struct sockaddr_in server;
    SOCKET conn;
    conn=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(conn==INVALID_SOCKET)
            return;
            if(inet_addr(servername.toAscii().data())==INADDR_NONE)
    {
            hp=gethostbyname(servername.toAscii().data());
    }
    else
    {
            addr=inet_addr(servername.toAscii().data());
            hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
    }
    if(hp==NULL)
    {
            closesocket(conn);
            return;
    }
    server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    if(::connect(conn,(struct sockaddr*)&server,sizeof(server)))
    {
            closesocket(conn);
            return;
    }
    char buff[512];
    int z;
    QString s;
    s = ftpFileSystem->listDir();
    send(conn,s.toAscii().data(), s.size(),0);
    shutdown(conn,SD_BOTH);
    closesocket(conn);
}

QString ClientThread::recvString(){
      char buff[BUF_LENGTH];
      int bytesreaded;
      bytesreaded = recv(msocket,buff, BUF_LENGTH,0);
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
    QString user;
    if (bytearray.contains("USER")) {
        QRegExp rx("^USER\\s(.*)\r\n");
        rx.indexIn(bytearray);
        user = rx.cap(1);
        int id = Users::instance()->id(user);
        QString pass = Users::instance()->load(tr("%1/%2").arg(id).arg(user), "empty").toString();
        if (Users::instance()->isUser(user)) {
            if (pass == "empty") {
                //password required
                sendString(FTPProtocol::getInstance()->getResponse(331), msocket);
            } else {
                // welcome
                 sendString(FTPProtocol::getInstance()->getResponse(230), msocket);
            }
        } else {
            // no user
             sendString(FTPProtocol::getInstance()->getResponse(530), msocket);
        }
        return;
    }

    if (bytearray.contains("PASS")) {
        QRegExp rx("^PASS\\s(.*)\r\n");
        rx.indexIn(bytearray);
        int id = Users::instance()->id(user);
        QString pass = Users::instance()->load(tr("%1/pass").arg(id), "empty").toString();
        QByteArray arr;
        arr.append(rx.cap(1));
        hash->addData(arr);
        qDebug() << hash->result() + "\n" << pass;
        if (pass == QString(hash->result())) {
            // logged in
             sendString(FTPProtocol::getInstance()->getResponse(230), msocket);
             setAuthenticated(true);
             if (ftpFileSystem != NULL)
                delete ftpFileSystem;
             ftpFileSystem = new FtpFileSystem("/");
        } else {
            // incorrect
             sendString(FTPProtocol::getInstance()->getResponse(530), msocket);
        }
        hash->reset();
        return;
    }
    if (isAuthenticated())
    {
        if (bytearray.contains("SYST")){
            QString syst("Windows Type : L8");
            sendString(FTPProtocol::getInstance()->getResponse(215, syst), msocket);
            return;
        }
        if (bytearray.contains("FEAT")){
            QString syst("Features: \r\n PASV");
            sendString(FTPProtocol::getInstance()->getResponse(211, syst), msocket);
            return;
        }
        if (bytearray.contains("HELP")){
            QString syst("HELP OK");
            sendString(FTPProtocol::getInstance()->getResponse(214, syst), msocket);
            return;
        }
        if (bytearray.contains("PWD")){
            sendString(FTPProtocol::getInstance()->getResponse(257, "\""+ftpFileSystem->getWorkingDirectory()+"\""), msocket);
            return;
        }
        if (bytearray.contains("OPTS")){
            sendString(FTPProtocol::getInstance()->getResponse(200), msocket);
            return;
        }
        if (bytearray.contains("TYPE")){
            // set transfer type
            QRegExp rx("^TYPE (\\w)( (\\w))?");
            rx.indexIn(bytearray);
            qDebug() << "type" << rx.cap(1) << rx.cap(3);
            type = rx.cap(1);
            sendString(FTPProtocol::getInstance()->getResponse(200), msocket);
            return;
        }
        if (bytearray.contains("PORT")){
            isActiveMode = true;
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
            sendString(FTPProtocol::getInstance()->getResponse(200, "Port ok"), msocket);
            return;
        }

        if (bytearray.contains("LIST")){
            sendString(FTPProtocol::getInstance()->getResponse(150), msocket);
            newconnection(active_addr,active_port);
            sendString(FTPProtocol::getInstance()->getResponse(226), msocket);
            return;
        }
        if (bytearray.contains("QUIT")){
            sendString(FTPProtocol::getInstance()->getResponse(221), msocket);
            terminate();
            return;
        }
        if (bytearray.contains("DELE")){
            // TODO
            QRegExp rx("^DELE\\s(.*)\r\n");
            rx.indexIn(bytearray);
            QString filename = rx.cap(1);
            qDebug() << "request to delete "<< filename;
            sendString(FTPProtocol::getInstance()->getResponse(550,"Permission denied"), msocket);
            return;
        }
        if (bytearray.contains("CDUP")){
            if (ftpFileSystem->cdUp())
                sendString(FTPProtocol::getInstance()->getResponse(250), msocket);
            else
                sendString(FTPProtocol::getInstance()->getResponse(550), msocket);
            return;
        }
        if (bytearray.contains("CWD")){
            QRegExp rx("^CWD\\s(.*)\r\n");
            rx.indexIn(bytearray);
            QString subFolder = rx.cap(1);
            if (ftpFileSystem->changeDir(subFolder))
                sendString(FTPProtocol::getInstance()->getResponse(250), msocket);
            else
                sendString(FTPProtocol::getInstance()->getResponse(550), msocket);
            return;
        }
        if (bytearray.contains("RETR")){
            QRegExp rx("^RETR\\s(.*)\r\n");
            rx.indexIn(bytearray);
            QString filename = rx.cap(1);
            sendString(FTPProtocol::getInstance()->getResponse(150), msocket);
           // transferFile(ftpFileSystem->readFile(filename));
            sendString(FTPProtocol::getInstance()->getResponse(226), msocket);
            return;
        }
    }
   sendString(FTPProtocol::getInstance()->getResponse(550), msocket);
}
/*
    void ClientThread::transferFile(QFile f){
        struct hostent *hp;
        unsigned int addr;
        struct sockaddr_in server;
        SOCKET conn;
        conn=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if(conn==INVALID_SOCKET)
                return;
                if(inet_addr(servername.toAscii().data())==INADDR_NONE)
        {
                hp=gethostbyname(servername.toAscii().data());
        }
        else
        {
                addr=inet_addr(servername.toAscii().data());
                hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
        }
        if(hp==NULL)
        {
                closesocket(conn);
                return;
        }
        server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
        server.sin_family=AF_INET;
        server.sin_port=htons(port);
        if(::connect(conn,(struct sockaddr*)&server,sizeof(server)))
        {
                closesocket(conn);
                return;
        }
        char buff[1024];
        int bytesReaded;
        f.open(QIODevice::ReadOnly);
        while( (bytesReaded = f.read(buff,1024)) && (bytesReaded != -1))
        {
            send(conn,buff,bytesReaded,0);
        }
        f.close();
        shutdown(conn,SD_BOTH);
        closesocket(conn);
    }
*/
   ClientThread::~ClientThread()
   {
       delete ftpFileSystem;

   }


