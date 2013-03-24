#include "ftpcore.h"

FTPCore::FTPCore(QObject *parent) :
    QObject(parent)
{
    terminated = false;
}
FTPCore::~FTPCore(){
    qDebug()<< "~FTPCore";
}

void FTPCore::run(){
    ClientThread *clientthread;
    if (!InitWinsock())
    {
        emit onerror("WinSock init failed");
        return;
    }
    if ((msocket=socket(AF_INET,SOCK_STREAM,0))<0)
        {
          emit onerror("Error socket " + WSAGetLastError());
          WSACleanup();
          return;
        }

    sockaddr_in local_addr;
    local_addr.sin_family=AF_INET;
    local_addr.sin_port=htons(CONTROL_PORT);
    local_addr.sin_addr.s_addr=0;

    // �������� bind ��� ����������
    if (bind(msocket,(sockaddr *) &local_addr, sizeof(local_addr)))
    {
          emit onerror("Error bind "+WSAGetLastError());
          closesocket(msocket);
          WSACleanup();
          return;
        }

     if (listen(msocket, MAX_CLIENTS))
        {
          // ������
          emit onerror("Error listen "+WSAGetLastError());
          closesocket(msocket);
          WSACleanup();
          return;
        }

        SOCKET client_socket;    // ����� ��� �������
        sockaddr_in client_addr;    // ����� �������
        int client_addr_size=sizeof(client_addr);

        ioctlsocket(msocket, FIONBIO,(unsigned long* ) 1);
        fd_set read_s; // ���������
        timeval time_out; // �������
        int res;
        emit onstarted();
        while (true)
        {
            FD_ZERO (&read_s); // �������� ���������
            FD_SET (msocket, &read_s); // ������� � ���� ��� �����
            time_out.tv_sec = 0;time_out.tv_usec = 500000; //������� 0.5 �������.
            if (SOCKET_ERROR == (res = select (0, &read_s, NULL, NULL, &time_out) ) )
            {
                emit onerror("Select error in FTPCore");
                closesocket(msocket);
                WSACleanup();
                return;
            }

            if ((res!=0) && (FD_ISSET (msocket, &read_s)) ) // ��������� FD_ISSET ������ ��� �������! :)
            {
                client_socket=accept(msocket, (sockaddr *)&client_addr, &client_addr_size);
                //plususer();      // ����������� �������
                         // �������������� ��������

                emit onnewconnection(inet_ntoa(client_addr.sin_addr));

                clientthread = new ClientThread(client_socket);
               QObject::connect(this, SIGNAL(onshutdownserver()),clientthread, SLOT(closeconnection()));
                 clientthread->start();
           }
            if (terminated){
                break;
            }
        }
        closesocket(msocket);
        if (WSACleanup() != 0){
            emit onerror("WSACleanup failed");
        }
        qDebug() << "Winsock stopped";
        emit onstopped();
        return;

}

void FTPCore::stop(){
    terminated = true;
}

bool FTPCore::InitWinsock(){
    if (WSAStartup(MAKEWORD(2,0),&wsaData) != 0){
        qCritical("Winsock initialisation error") ;
        return false;
    }
    qDebug() << "Winsock started";
    return true;
}
