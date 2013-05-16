/********************************************************************************
** Form generated from reading UI file 'edituserdialog.ui'
**
** Created: Thu 16. May 19:18:28 2013
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
#include <QtGui/QGroupBox>
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
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_5;
    QSplitter *splitter;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *usernameEdt;
    QWidget *layoutWidget11;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *passwordEdt;
    QLabel *label_5;
    QLineEdit *folderEdt;
    QPushButton *selectFolderButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *freadCb;
    QCheckBox *fwriteCb;
    QCheckBox *fdeleteCb;
    QCheckBox *fappendCb;

    void setupUi(QDialog *EditUserDialog)
    {
        if (EditUserDialog->objectName().isEmpty())
            EditUserDialog->setObjectName(QString::fromUtf8("EditUserDialog"));
        EditUserDialog->resize(238, 308);
        buttonBox = new QDialogButtonBox(EditUserDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(150, 240, 81, 311));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(EditUserDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(19, 1, 114, 300));
        verticalLayout_5 = new QVBoxLayout(layoutWidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(layoutWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        usernameEdt = new QLineEdit(layoutWidget1);
        usernameEdt->setObjectName(QString::fromUtf8("usernameEdt"));

        verticalLayout->addWidget(usernameEdt);

        splitter->addWidget(layoutWidget1);
        layoutWidget11 = new QWidget(splitter);
        layoutWidget11->setObjectName(QString::fromUtf8("layoutWidget11"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget11);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        passwordEdt = new QLineEdit(layoutWidget11);
        passwordEdt->setObjectName(QString::fromUtf8("passwordEdt"));
        passwordEdt->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(passwordEdt);

        splitter->addWidget(layoutWidget11);

        verticalLayout_5->addWidget(splitter);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_5->addWidget(label_5);

        folderEdt = new QLineEdit(layoutWidget);
        folderEdt->setObjectName(QString::fromUtf8("folderEdt"));
        folderEdt->setEnabled(true);
        folderEdt->setReadOnly(true);

        verticalLayout_5->addWidget(folderEdt);

        selectFolderButton = new QPushButton(layoutWidget);
        selectFolderButton->setObjectName(QString::fromUtf8("selectFolderButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/select_folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectFolderButton->setIcon(icon);

        verticalLayout_5->addWidget(selectFolderButton);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        freadCb = new QCheckBox(groupBox);
        freadCb->setObjectName(QString::fromUtf8("freadCb"));

        verticalLayout_3->addWidget(freadCb);

        fwriteCb = new QCheckBox(groupBox);
        fwriteCb->setObjectName(QString::fromUtf8("fwriteCb"));

        verticalLayout_3->addWidget(fwriteCb);

        fdeleteCb = new QCheckBox(groupBox);
        fdeleteCb->setObjectName(QString::fromUtf8("fdeleteCb"));

        verticalLayout_3->addWidget(fdeleteCb);

        fappendCb = new QCheckBox(groupBox);
        fappendCb->setObjectName(QString::fromUtf8("fappendCb"));

        verticalLayout_3->addWidget(fappendCb);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_5->addWidget(groupBox);


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
        groupBox->setTitle(QApplication::translate("EditUserDialog", "\320\237\321\200\320\260\320\262\320\260", 0, QApplication::UnicodeUTF8));
        freadCb->setText(QApplication::translate("EditUserDialog", "\321\207\321\202\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        fwriteCb->setText(QApplication::translate("EditUserDialog", "\320\267\320\260\320\277\320\270\321\201\321\214", 0, QApplication::UnicodeUTF8));
        fdeleteCb->setText(QApplication::translate("EditUserDialog", "\321\203\320\264\320\260\320\273\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        fappendCb->setText(QApplication::translate("EditUserDialog", "\320\264\320\276\320\267\320\260\320\277\320\270\321\201\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditUserDialog: public Ui_EditUserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITUSERDIALOG_H
