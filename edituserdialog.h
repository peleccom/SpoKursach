#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
namespace Ui {
    class EditUserDialog;
}

class EditUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserDialog(QString &user, QString &password,QString &group,QWidget *parent = 0);
    ~EditUserDialog();
public slots:
    void openFolderDialog();

private:
    Ui::EditUserDialog *ui;
};

#endif // EDITUSERDIALOG_H
