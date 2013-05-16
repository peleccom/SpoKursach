/********************************************************************************
** Form generated from reading UI file 'edituserdialog.ui'
**
** Created: Thu 16. May 20:51:32 2013
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
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditUserDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QLineEdit *usernameEdt;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *enterpassRB;
    QVBoxLayout *verticalLayout;
    QLineEdit *passwordEdt;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *emptypassRB;
    QVBoxLayout *verticalLayout_7;
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
        EditUserDialog->resize(323, 348);
        buttonBox = new QDialogButtonBox(EditUserDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(230, 270, 81, 311));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(EditUserDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 5, 138, 336));
        verticalLayout_9 = new QVBoxLayout(widget);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_5->addWidget(label);

        usernameEdt = new QLineEdit(widget);
        usernameEdt->setObjectName(QString::fromUtf8("usernameEdt"));

        verticalLayout_5->addWidget(usernameEdt);


        verticalLayout_9->addLayout(verticalLayout_5);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_8->addWidget(label_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        enterpassRB = new QRadioButton(widget);
        enterpassRB->setObjectName(QString::fromUtf8("enterpassRB"));
        enterpassRB->setChecked(true);

        horizontalLayout->addWidget(enterpassRB);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        passwordEdt = new QLineEdit(widget);
        passwordEdt->setObjectName(QString::fromUtf8("passwordEdt"));
        passwordEdt->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordEdt);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        emptypassRB = new QRadioButton(widget);
        emptypassRB->setObjectName(QString::fromUtf8("emptypassRB"));

        verticalLayout_6->addWidget(emptypassRB);


        verticalLayout_2->addLayout(verticalLayout_6);


        verticalLayout_8->addLayout(verticalLayout_2);


        verticalLayout_9->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_7->addWidget(label_5);

        folderEdt = new QLineEdit(widget);
        folderEdt->setObjectName(QString::fromUtf8("folderEdt"));
        folderEdt->setEnabled(true);
        folderEdt->setReadOnly(true);

        verticalLayout_7->addWidget(folderEdt);

        selectFolderButton = new QPushButton(widget);
        selectFolderButton->setObjectName(QString::fromUtf8("selectFolderButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/select_folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectFolderButton->setIcon(icon);

        verticalLayout_7->addWidget(selectFolderButton);


        verticalLayout_9->addLayout(verticalLayout_7);

        groupBox = new QGroupBox(widget);
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


        verticalLayout_9->addWidget(groupBox);

        buttonBox->raise();
        enterpassRB->raise();
        emptypassRB->raise();
        folderEdt->raise();
        label_5->raise();
        emptypassRB->raise();

        retranslateUi(EditUserDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), EditUserDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EditUserDialog, SLOT(reject()));
        QObject::connect(emptypassRB, SIGNAL(toggled(bool)), passwordEdt, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(EditUserDialog);
    } // setupUi

    void retranslateUi(QDialog *EditUserDialog)
    {
        EditUserDialog->setWindowTitle(QApplication::translate("EditUserDialog", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EditUserDialog", "\320\230\320\274\321\217:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EditUserDialog", "\320\237\320\260\321\200\320\276\320\273\321\214:", 0, QApplication::UnicodeUTF8));
        enterpassRB->setText(QString());
        passwordEdt->setInputMask(QString());
        passwordEdt->setText(QString());
        emptypassRB->setText(QApplication::translate("EditUserDialog", "\320\277\321\203\321\201\321\202\320\276\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("EditUserDialog", "\320\237\320\260\320\277\320\272\320\260:", 0, QApplication::UnicodeUTF8));
        selectFolderButton->setText(QApplication::translate("EditUserDialog", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("EditUserDialog", "\320\237\321\200\320\260\320\262\320\260:", 0, QApplication::UnicodeUTF8));
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
