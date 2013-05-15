/********************************************************************************
** Form generated from reading UI file 'edituserdialog.ui'
**
** Created: Wed 15. May 23:31:32 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITUSERDIALOG_H
#define UI_EDITUSERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditUserDialog
{
public:
    QDialogButtonBox *buttonBox;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *usernameEdt;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *passwordEdt;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLineEdit *folderEdt;
    QPushButton *selectFolderButton;
    QCheckBox *freadCb;
    QCheckBox *fwriteCb;
    QCheckBox *fdeleteCb;
    QCheckBox *fappendCb;

    void setupUi(QDialog *EditUserDialog)
    {
        if (EditUserDialog->objectName().isEmpty())
            EditUserDialog->setObjectName(QString::fromUtf8("EditUserDialog"));
        EditUserDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(EditUserDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        splitter = new QSplitter(EditUserDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(19, 1, 191, 123));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        usernameEdt = new QLineEdit(layoutWidget);
        usernameEdt->setObjectName(QString::fromUtf8("usernameEdt"));

        verticalLayout->addWidget(usernameEdt);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        passwordEdt = new QLineEdit(layoutWidget1);
        passwordEdt->setObjectName(QString::fromUtf8("passwordEdt"));
        passwordEdt->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(passwordEdt);

        splitter->addWidget(layoutWidget1);
        widget = new QWidget(EditUserDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 130, 191, 173));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);


        verticalLayout_4->addLayout(horizontalLayout);

        folderEdt = new QLineEdit(widget);
        folderEdt->setObjectName(QString::fromUtf8("folderEdt"));
        folderEdt->setEnabled(true);
        folderEdt->setReadOnly(true);

        verticalLayout_4->addWidget(folderEdt);

        selectFolderButton = new QPushButton(widget);
        selectFolderButton->setObjectName(QString::fromUtf8("selectFolderButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/select_folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectFolderButton->setIcon(icon);

        verticalLayout_4->addWidget(selectFolderButton);

        freadCb = new QCheckBox(widget);
        freadCb->setObjectName(QString::fromUtf8("freadCb"));

        verticalLayout_4->addWidget(freadCb);

        fwriteCb = new QCheckBox(widget);
        fwriteCb->setObjectName(QString::fromUtf8("fwriteCb"));

        verticalLayout_4->addWidget(fwriteCb);

        fdeleteCb = new QCheckBox(widget);
        fdeleteCb->setObjectName(QString::fromUtf8("fdeleteCb"));

        verticalLayout_4->addWidget(fdeleteCb);

        fappendCb = new QCheckBox(widget);
        fappendCb->setObjectName(QString::fromUtf8("fappendCb"));

        verticalLayout_4->addWidget(fappendCb);


        retranslateUi(EditUserDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), EditUserDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EditUserDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(EditUserDialog);
    } // setupUi

    void retranslateUi(QDialog *EditUserDialog)
    {
        EditUserDialog->setWindowTitle(QApplication::translate("EditUserDialog", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EditUserDialog", "\320\230\320\274\321\217:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EditUserDialog", "\320\237\320\260\321\200\320\276\320\273\321\214:", 0, QApplication::UnicodeUTF8));
        passwordEdt->setInputMask(QString());
        passwordEdt->setText(QString());
        label_5->setText(QApplication::translate("EditUserDialog", "\320\237\320\260\320\277\320\272\320\260", 0, QApplication::UnicodeUTF8));
        selectFolderButton->setText(QApplication::translate("EditUserDialog", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        freadCb->setText(QApplication::translate("EditUserDialog", "\321\204\320\260\320\271\320\273 \321\207\321\202\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        fwriteCb->setText(QApplication::translate("EditUserDialog", "\321\204\320\260\320\271\320\273 \320\267\320\260\320\277\320\270\321\201\321\214", 0, QApplication::UnicodeUTF8));
        fdeleteCb->setText(QApplication::translate("EditUserDialog", "\321\204\320\260\320\271\320\273 \321\203\320\264\320\260\320\273\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        fappendCb->setText(QApplication::translate("EditUserDialog", "\321\204\320\260\320\271\320\273 \320\264\320\276\320\267\320\260\320\277\320\270\321\201\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditUserDialog: public Ui_EditUserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITUSERDIALOG_H
