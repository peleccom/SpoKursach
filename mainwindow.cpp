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
    connect(ftpServer,SIGNAL(onStarted(QString)),SLOT(serverstarted()));
    connect(ftpServer,SIGNAL(onClose(QString)),SLOT(serverstopped()));
    connect(ftpServer,SIGNAL(clientschanged(int)), ui->clientslcd, SLOT(display(int)));

    connect(ui->addUserButton, SIGNAL(clicked()),SLOT(adduser()));
    connect(ui->editUserButton,SIGNAL(clicked()),SLOT(edituser()));
    connect(ui->deleteUserButton,SIGNAL(clicked()),SLOT(deleteuser()));
    connect(ui->Utf8Cb, SIGNAL(clicked(bool)), SLOT(changeUTF8Flag(bool)));


    connect(ui->actionStartServer, SIGNAL(triggered()), SLOT(on_start_clicked()));
    connect(ui->actionStopServer, SIGNAL(triggered()),SLOT(on_stop_clicked()));
    connect(ui->actionAbout, SIGNAL(triggered()),SLOT(showAbout()));

    ui->usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    updateUserTable();
    ui->Utf8Cb->setChecked(Settings::getInstance()->getForceUtf8());

    }

MainWindow::~MainWindow()
{
    delete ftpServer;
    delete ui;
}


void MainWindow::on_start_clicked(){
    if (ftpServer == NULL)
    {
        ftpServer = new FtpServer(this);
    }
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
    Settings::destroy();
}


void MainWindow::edituser(){
    QModelIndexList indexList = ui->usersTable->selectionModel()->selectedIndexes();
    int row = -1;
    foreach (QModelIndex index, indexList) {
        row = index.row();
        break;
    }
    if (row != -1)
    {
        EditUserDialog editdialog(row);
        int result = editdialog.exec();
        if (result == QDialog::Accepted)
        {
            User user = editdialog.creatUserObject();
            Settings::getInstance()->replaceUser(row, user);
            updateUserTable();
        }
     }
}


void MainWindow::adduser(){
    EditUserDialog editdialog;
    int result = editdialog.exec();
    if (result == QDialog::Accepted)
    {
        User user = editdialog.creatUserObject();
        Settings::getInstance()->addUser(user);
        updateUserTable();
    }
}

void MainWindow::deleteuser(){
    QModelIndexList indexList = ui->usersTable->selectionModel()->selectedIndexes();
    int row = -1;
    foreach (QModelIndex index, indexList) {
        row = index.row();
        break;
    }
    if (row != -1 )
    {
        Settings::getInstance()->removeUser(row);
        updateUserTable();
    }
}

void MainWindow::updateUserTable(){
    User user;
    QList<User> users = Settings::getInstance()->listUsers();
    ui->usersTable->clearContents();
    ui->usersTable->setRowCount(users.count());
    QTableWidgetItem *item;
    for (int i=0;i < users.size(); i++ ){
        user = users.at(i);
        item = new QTableWidgetItem(user.getName());
        ui->usersTable->setItem(i,0,item);
        item = new QTableWidgetItem((user.getPasswordHash().isEmpty())?"Нет":"*");
        ui->usersTable->setItem(i,1,item);
        item = new QTableWidgetItem(user.getFolder());
        ui->usersTable->setItem(i,2,item);
        FileAccess fileAccess = user.getFileAccess();
        item = new QTableWidgetItem(QString("%1%2%3%4")
                                    .arg(fileAccess.aread?"r":"-")
                                    .arg(fileAccess.awrite?"w":"-")
                                    .arg(fileAccess.adelete?"d":"-")
                                    .arg(fileAccess.aappend?"a":"-"));
        ui->usersTable->setItem(i,3,item);
    }

}

bool MainWindow::changeUTF8Flag(bool value){
    Settings::getInstance()->setForceUtf8(value);
}

void MainWindow::showAbout(){
    QMessageBox::about(this, "FTP сервер","Курсовой проект на тему \"Реализиция FTP сервера\"");
}

void MainWindow::serverstarted(){
    ui->statusLabel->setPixmap(QPixmap(":/res/green.png"));
}

void MainWindow::serverstopped(){
    ui->statusLabel->setPixmap(QPixmap(":/res/red.png"));
}
