#include "edituserdialog.h"
#include "ui_edituserdialog.h"

EditUserDialog::EditUserDialog(QString &user, QString &password, QString &group, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserDialog)
{
    ui->setupUi(this);
    connect(ui->selectFolderButton,SIGNAL(clicked()),SLOT(openFolderDialog()));
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

void EditUserDialog::openFolderDialog(){
    QString dir = QFileDialog::getExistingDirectory(this,"Выбирите директорию","", QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    qDebug() << "dir " << dir;
    ui->folderEdt->setText(dir);
}
