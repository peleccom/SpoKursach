#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <user.h>
namespace Ui {
    class EditUserDialog;
}

class EditUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserDialog(int userIndex = -1,QWidget *parent = 0);
    User creatUserObject();
    ~EditUserDialog();
public slots:
    void openFolderDialog();
    void updateHash(const QString &pass);

private:
    Ui::EditUserDialog *ui;
    QString passHash;
};

#endif // EDITUSERDIALOG_H
