/********************************************************************************
** Form generated from reading UI file 'retrieveVersion.ui'
**
** Created: Thu Oct 1 20:09:26 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RETRIEVEVERSION_H
#define UI_RETRIEVEVERSION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_retrieveVersion
{
public:
    QLabel *fileLabel;
    QLabel *fileNameLabel;
    QLineEdit *fileRow;
    QPushButton *browseButton;
    QLineEdit *nameRow;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *retrieveVersion)
    {
        if (retrieveVersion->objectName().isEmpty())
            retrieveVersion->setObjectName(QString::fromUtf8("retrieveVersion"));
        retrieveVersion->resize(400, 300);
        fileLabel = new QLabel(retrieveVersion);
        fileLabel->setObjectName(QString::fromUtf8("fileLabel"));
        fileLabel->setGeometry(QRect(30, 50, 66, 17));
        fileNameLabel = new QLabel(retrieveVersion);
        fileNameLabel->setObjectName(QString::fromUtf8("fileNameLabel"));
        fileNameLabel->setGeometry(QRect(30, 120, 71, 17));
        fileRow = new QLineEdit(retrieveVersion);
        fileRow->setObjectName(QString::fromUtf8("fileRow"));
        fileRow->setEnabled(false);
        fileRow->setGeometry(QRect(80, 40, 191, 27));
        browseButton = new QPushButton(retrieveVersion);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setGeometry(QRect(280, 40, 98, 27));
        nameRow = new QLineEdit(retrieveVersion);
        nameRow->setObjectName(QString::fromUtf8("nameRow"));
        nameRow->setGeometry(QRect(120, 110, 261, 27));
        buttonBox = new QDialogButtonBox(retrieveVersion);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(200, 260, 176, 27));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(retrieveVersion);

        QMetaObject::connectSlotsByName(retrieveVersion);
    } // setupUi

    void retranslateUi(QDialog *retrieveVersion)
    {
        retrieveVersion->setWindowTitle(QApplication::translate("retrieveVersion", "retrieveVersion", 0, QApplication::UnicodeUTF8));
        fileLabel->setText(QApplication::translate("retrieveVersion", "File:", 0, QApplication::UnicodeUTF8));
        fileNameLabel->setText(QApplication::translate("retrieveVersion", "File Name:", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("retrieveVersion", "Browse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class retrieveVersion: public Ui_retrieveVersion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RETRIEVEVERSION_H
