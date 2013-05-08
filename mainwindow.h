#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ftpserver.h>
#include <edituserdialog.h>
#include <log.h>
#include <settings.h>
#include <myutils.h>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    FtpServer *ftpServer;
    Log* log;
    void updateUserTable();

public slots:
    void eventHandler(QString str);

    void on_start_clicked();
     void on_stop_clicked();
     void addlog(QString s);
     void edituser();
     void adduser();
     void deleteuser();
     bool changeUTF8Flag(bool);
protected:
     void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H

