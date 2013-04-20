#include "clientthread.h"

ClientThread::ClientThread(SOCKET client_socket, QObject *parent) :
    QThread(parent)
{
    msocket = client_socket;
    terminated = false;
    hash = new QCryptographicHash(QCryptographicHash::Md5);
}



void ClientThread::run(){
    qDebug() << "Thread id=" << QThread::currentThreadId();
    // отправл€ем клиенту приветствие
    sendString(FTPProtocol::getInstance()->getResponse(220,""), msocket);
    QString s = recvString();
    qDebug() << "'"<<s << "'";
    QByteArray array (s.toStdString().c_str());
    analizeCommand(array);
    while(true)
    {

        if (terminated){
            break;
        }
        sleep(200);
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
                sendString(FTPProtocol::getInstance()->getResponse(331), msocket);
            } else {
                 sendString(FTPProtocol::getInstance()->getResponse(230), msocket);
            }
        } else {
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
             sendString(FTPProtocol::getInstance()->getResponse(230), msocket);
        } else {
             sendString(FTPProtocol::getInstance()->getResponse(530), msocket);
        }
        hash->reset();
        return;
    }
}
