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


    connect(ui->addUserButton, SIGNAL(clicked()),SLOT(adduser()));
    connect(ui->editUserButton,SIGNAL(clicked()),SLOT(edituser()));
    connect(ui->deleteUserButton,SIGNAL(clicked()),SLOT(deleteuser()));

    ui->usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    updateUserTable();
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
    Settings::destroy();
    Users::destroy();
}


void MainWindow::edituser(){
    QModelIndexList indexList = ui->usersTable->selectionModel()->selectedIndexes();
    int row;
    foreach (QModelIndex index, indexList) {
        row = index.row();
        break;
    }
    EditUserDialog editdialog(row);
    int result = editdialog.exec();
    if (result == QDialog::Accepted)
    {
        User user = editdialog.creatUserObject();
        Settings::getInstance()->addUser(user);
        updateUserTable();
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
    int row;
    foreach (QModelIndex index, indexList) {
        row = index.row();
        break;
    }
    Settings::getInstance()->removeUser(row);
    updateUserTable();
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
        item = new QTableWidgetItem((user.getPasswordHash().size() != 0)?"*":"");
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
