#include "ftpprotocol.h"
FTPProtocol* FTPProtocol ::instance=NULL;
FTPProtocol::FTPProtocol()
{
    mResponseCodes.insert(110,"Restart marker reply.");
    mResponseCodes.insert(120,"Service ready in nnn minutes.");
    mResponseCodes.insert(125,"Data connection already open; transfer starting.");
    mResponseCodes.insert(150,"File status okay; about to open data connection.");
    mResponseCodes.insert(200,"Command okay.");
    mResponseCodes.insert(202,"Command not implemented, superfluous at this site.");
    mResponseCodes.insert(211,"System status, nothing to report.");
    mResponseCodes.insert(212,"Directory status.");
    mResponseCodes.insert(213,"End of status.");
    mResponseCodes.insert(214,"Help command successful.");
    mResponseCodes.insert(215,"UNIX Type: L8.");
    mResponseCodes.insert(220,"Service ready for new user.");
    mResponseCodes.insert(221,"Service closing control connection.");
    mResponseCodes.insert(225,"Data connection open; no transfer in progress.");
    mResponseCodes.insert(226,"Closing data connection.");
    mResponseCodes.insert(227,"Entering Passive Mode (h1,h2,h3,h4,p1,p2).");
    mResponseCodes.insert(230,"User logged in, proceed.");
    mResponseCodes.insert(250,"Requested file action okay, completed.");
    mResponseCodes.insert(257,"Path was created.");
    mResponseCodes.insert(331,"Password required.");
    mResponseCodes.insert(332,"Need account for login.");
    mResponseCodes.insert(350,"Requested file action pending further information.");
    mResponseCodes.insert(421,"Service not available, closing control connection.");
    mResponseCodes.insert(425,"Can't open data connection.");
    mResponseCodes.insert(426,"Connection closed; transfer aborted.");
    mResponseCodes.insert(450,"Requested file action not taken.");
    mResponseCodes.insert(451,"Requested action aborted: local error in processing.");
    mResponseCodes.insert(452,"Requested action not taken.");
    mResponseCodes.insert(500,"Syntax error, command unrecognized.");
    mResponseCodes.insert(501,"Syntax error in parameters or arguments.");
    mResponseCodes.insert(502,"Command not implemented.");
    mResponseCodes.insert(503,"Bad sequence of commands.");
    mResponseCodes.insert(504,"Command not implemented for that parameter.");
    mResponseCodes.insert(530,"Not logged in.");
    mResponseCodes.insert(532,"Need account for storing files.");
    mResponseCodes.insert(550,"Requested action not taken.");
    mResponseCodes.insert(551,"Requested action aborted: page type unknown.");
    mResponseCodes.insert(552,"Requested file action aborted.");
    mResponseCodes.insert(553,"Requested action not taken.");
    mResponseCodes.insert(550,"The filename, directory name, or volume label syntax is incorrect.");
}

QString FTPProtocol::getResponse(int code, QString customMessage){
    if (customMessage.isEmpty()) {
        return QString("%1 %2").arg(code).arg(mResponseCodes.value(code));
    } else {
        return QString("%1 %2").arg(code).arg(customMessage);
    }
}

FTPProtocol* FTPProtocol::getInstance(){
    if (instance==NULL)
        instance = new FTPProtocol();
    return instance;
}

void FTPProtocol::destroy() {
   if (instance)
      {delete instance;
       instance = NULL;}
}

FTPProtocol::~FTPProtocol(){
    qDebug()<< "~FTPProtocol";
}
