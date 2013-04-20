#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ftpServer = new FtpServer();
    log = new Log;
    connect(log, SIGNAL(appendLog(QString)), ui->textlog, SLOT(append(QString)));
    connect(ui->clearLogBtn, SIGNAL(clicked()), ui->textlog, SLOT(clear()));

    connect(ftpServer, SIGNAL(onError(QString)), this, SLOT(eventHandler(QString)));
    connect(ftpServer, SIGNAL(onStarted(QString)), this, SLOT(eventHandler(QString)));
    connect(ftpServer, SIGNAL(onClose(QString)), this, SLOT(eventHandler(QString)));
    connect(ftpServer, SIGNAL(onEvent(QString)), this, SLOT(eventHandler(QString)));


    connect(ui->addUserButton, SIGNAL(clicked()),SLOT(edituser()));
}

MainWindow::~MainWindow()
{
    delete ftpServer;
    delete ui;
}


void MainWindow::on_start_clicked(){
    if (ftpServer == NULL)
        ftpServer = new FtpServer(this);
   ftpServer->start();
}

void MainWindow::on_stop_clicked(){
   if (ftpServer != NULL)
        ftpServer->stop();
}

void MainWindow::addlog(QString s){
    ui->textlog->append(s);
}

void MainWindow::eventHandler(QString str){
    ui->textlog->append(str);
}

void MainWindow::closeEvent(QCloseEvent *event){
    if (ftpServer != NULL)
         ftpServer->stop();
    FTPProtocol::destroy();
    Users::destroy();
}

void MainWindow::edituser(){
    QString user = "Alex";
    QString pass = "Pass";
    QString group = "group";
    EditUserDialog *editdialog = new EditUserDialog(user, pass, group);
    editdialog->exec();

}
