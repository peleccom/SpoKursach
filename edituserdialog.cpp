#include "edituserdialog.h"
#include "ui_edituserdialog.h"

EditUserDialog::EditUserDialog(QString &user, QString &password, QString &group, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserDialog)
{
    ui->setupUi(this);
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}
