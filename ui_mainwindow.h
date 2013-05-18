/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat 18. May 19:08:24 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStartServer;
    QAction *actionStopServer;
    QAction *actionAbout;
    QAction *action;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textlog;
    QVBoxLayout *verticalLayout_2;
    QPushButton *start;
    QPushButton *stop;
    QPushButton *clearLogBtn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLCDNumber *clientslcd;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *Utf8Cb;
    QLabel *label;
    QTableWidget *usersTable;
    QSplitter *splitter;
    QToolButton *addUserButton;
    QToolButton *editUserButton;
    QToolButton *deleteUserButton;
    QLabel *statusLabel;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(652, 495);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionStartServer = new QAction(MainWindow);
        actionStartServer->setObjectName(QString::fromUtf8("actionStartServer"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStartServer->setIcon(icon1);
        actionStopServer = new QAction(MainWindow);
        actionStopServer->setObjectName(QString::fromUtf8("actionStopServer"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStopServer->setIcon(icon2);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon3);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textlog = new QTextEdit(tab);
        textlog->setObjectName(QString::fromUtf8("textlog"));
        textlog->setReadOnly(true);

        horizontalLayout->addWidget(textlog);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        start = new QPushButton(tab);
        start->setObjectName(QString::fromUtf8("start"));
        start->setIcon(icon1);

        verticalLayout_2->addWidget(start);

        stop = new QPushButton(tab);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setIcon(icon2);

        verticalLayout_2->addWidget(stop);

        clearLogBtn = new QPushButton(tab);
        clearLogBtn->setObjectName(QString::fromUtf8("clearLogBtn"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearLogBtn->setIcon(icon4);

        verticalLayout_2->addWidget(clearLogBtn);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(1000, 100));

        horizontalLayout_2->addWidget(label_2);

        clientslcd = new QLCDNumber(tab);
        clientslcd->setObjectName(QString::fromUtf8("clientslcd"));
        clientslcd->setMaximumSize(QSize(64, 64));
        clientslcd->setLayoutDirection(Qt::RightToLeft);
        clientslcd->setAutoFillBackground(false);

        horizontalLayout_2->addWidget(clientslcd);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        Utf8Cb = new QCheckBox(tab_2);
        Utf8Cb->setObjectName(QString::fromUtf8("Utf8Cb"));

        verticalLayout_3->addWidget(Utf8Cb);

        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        usersTable = new QTableWidget(tab_2);
        if (usersTable->columnCount() < 4)
            usersTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        usersTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        usersTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        usersTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        usersTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        usersTable->setObjectName(QString::fromUtf8("usersTable"));
        usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        usersTable->setShowGrid(false);

        verticalLayout_3->addWidget(usersTable);

        splitter = new QSplitter(tab_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        addUserButton = new QToolButton(splitter);
        addUserButton->setObjectName(QString::fromUtf8("addUserButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/res/user_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addUserButton->setIcon(icon5);
        splitter->addWidget(addUserButton);
        editUserButton = new QToolButton(splitter);
        editUserButton->setObjectName(QString::fromUtf8("editUserButton"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/res/user_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        editUserButton->setIcon(icon6);
        splitter->addWidget(editUserButton);
        deleteUserButton = new QToolButton(splitter);
        deleteUserButton->setObjectName(QString::fromUtf8("deleteUserButton"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/res/user_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteUserButton->setIcon(icon7);
        splitter->addWidget(deleteUserButton);

        verticalLayout_3->addWidget(splitter);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        verticalLayout_4->addLayout(verticalLayout);

        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setEnabled(true);
        statusLabel->setMaximumSize(QSize(32, 32));
        statusLabel->setLayoutDirection(Qt::RightToLeft);
        statusLabel->setFrameShadow(QFrame::Sunken);
        statusLabel->setLineWidth(5);
        statusLabel->setMidLineWidth(0);
        statusLabel->setPixmap(QPixmap(QString::fromUtf8(":/res/red.png")));
        statusLabel->setScaledContents(true);
        statusLabel->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        verticalLayout_4->addWidget(statusLabel);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 652, 18));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(actionStartServer);
        menu->addAction(actionStopServer);
        menu_2->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FTP \321\201\320\265\321\200\320\262\320\265\321\200", 0, QApplication::UnicodeUTF8));
        actionStartServer->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272", 0, QApplication::UnicodeUTF8));
        actionStartServer->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionStopServer->setText(QApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260", 0, QApplication::UnicodeUTF8));
        actionStopServer->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", 0, QApplication::UnicodeUTF8));
        actionAbout->setShortcut(QApplication::translate("MainWindow", "F1", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\203", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272 \321\201\320\265\321\200\320\262\320\265\321\200\320\260", 0, QApplication::UnicodeUTF8));
        stop->setText(QApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\265\321\200\320\262\320\265\321\200", 0, QApplication::UnicodeUTF8));
        clearLogBtn->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\273\320\276\320\263", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\320\220\320\272\321\202\320\270\320\262\320\275\321\213\321\205 \320\272\320\273\320\270\320\265\320\275\321\202\320\276\320\262", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\320\233\320\276\320\263", 0, QApplication::UnicodeUTF8));
        Utf8Cb->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\270\320\275\321\203\320\264\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\271 UTF-8", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\270", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = usersTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\320\230\320\274\321\217", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = usersTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\276\320\273\321\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = usersTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\320\237\320\260\320\277\320\272\320\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = usersTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\320\220\321\202\321\202\321\200\320\270\320\261\321\203\321\202\321\213", 0, QApplication::UnicodeUTF8));
        addUserButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        editUserButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        deleteUserButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\265\321\200", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\320\274\320\276\321\211\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
