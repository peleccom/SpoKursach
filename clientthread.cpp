#include "clientthread.h"

ClientThread::ClientThread(SOCKET client_socket, QObject *parent) :
    QThread(parent)
{
    msocket = client_socket;
    terminated = false;
    hash = new QCryptographicHash(QCryptographicHash::Md5);
}



void ClientThread::run(){
    char buff[20*1024];
    QByteArray bytearray;
int bytes_recv;
    // отправл€ем клиенту приветствие
    sendString(FTPProtocol::getInstance()->getResponse(220,""), msocket);
    // цикл эхо-сервера: прием строки от клиента и
    // возвращение ее клиенту
    while(
          ( bytes_recv=recv(msocket,&buff[0],sizeof(buff),0))
              && bytes_recv !=SOCKET_ERROR)
      //send(msocket,&buff[0],bytes_recv,0);
    {
        buff[bytes_recv] = '\0';
        qDebug() << buff;
        bytearray = QByteArray(buff, bytes_recv);
        analizeCommand(bytearray);
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
}

void ClientThread::closeconnection(){
    terminated = true;
}

int ClientThread::sendString(QString mes, SOCKET sock){
    if (!mes.endsWith("\r\n"))
        mes += "\r\n";
    return send(sock,mes.toAscii().data(),mes.length(),0);
}

void ClientThread::analizeCommand(QByteArray &bytearray){
    QString user;
    if (bytearray.contains("USER")) {
        qDebug() << "USER";
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
