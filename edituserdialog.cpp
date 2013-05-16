#include "edituserdialog.h"
#include "ui_edituserdialog.h"
#include <settings.h>

EditUserDialog::EditUserDialog(int userIndex, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserDialog)
{
    ui->setupUi(this);
    connect(ui->selectFolderButton,SIGNAL(clicked()),SLOT(openFolderDialog()));
    connect(ui->passwordEdt, SIGNAL(textEdited(QString)),SLOT(updateHash(QString)));
    if ( userIndex >= 0)
    {
        User user = Settings::getInstance()->listUsers().at(userIndex);
        ui->usernameEdt->setText(user.getName());
        passHash = user.getPasswordHash();
        if (passHash.isEmpty())
            ui->emptypassRB->setChecked(true);
        else
            ui->enterpassRB->setChecked(true);
        ui->folderEdt->setText(user.getFolder());
        FileAccess fileAccess = user.getFileAccess();
        ui->freadCb->setChecked(fileAccess.aread);
        ui->fwriteCb->setChecked(fileAccess.awrite);
        ui->fdeleteCb->setChecked(fileAccess.adelete);
        ui->fappendCb->setChecked(fileAccess.aappend);
    }
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
    qDebug() << "~dialog";
}

void EditUserDialog::openFolderDialog(){
    QString dir = QFileDialog::getExistingDirectory(this,"Выбирите директорию","", QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    qDebug() << "dir " << dir;
    ui->folderEdt->setText(dir);
}

User EditUserDialog::creatUserObject(){
    FileAccess fa;
    fa.aread = ui->freadCb->isChecked();
    fa.awrite = ui->fwriteCb->isChecked();
    fa.adelete = ui->fdeleteCb->isChecked();
    fa.aappend= ui->fappendCb->isChecked();
    return User(ui->usernameEdt->text(), ui->enterpassRB->isChecked()?passHash:"", ui->folderEdt->text(),fa);
}


void EditUserDialog::updateHash(const QString &pass){
    passHash = User::getHash(pass);
}
