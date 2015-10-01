/********************************************************************************
** Form generated from reading UI file 'saveFunc.ui'
**
** Created: Thu Oct 1 14:43:41 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEFUNC_H
#define UI_SAVEFUNC_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_saveFunc
{
public:
    QPushButton *okButton;
    QLabel *messageLabel;

    void setupUi(QDialog *saveFunc)
    {
        if (saveFunc->objectName().isEmpty())
            saveFunc->setObjectName(QString::fromUtf8("saveFunc"));
        saveFunc->resize(300, 150);
        okButton = new QPushButton(saveFunc);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(180, 110, 98, 27));
        messageLabel = new QLabel(saveFunc);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setGeometry(QRect(30, 40, 241, 51));

        retranslateUi(saveFunc);

        QMetaObject::connectSlotsByName(saveFunc);
    } // setupUi

    void retranslateUi(QDialog *saveFunc)
    {
        saveFunc->setWindowTitle(QApplication::translate("saveFunc", "saveFunc", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("saveFunc", "OK", 0, QApplication::UnicodeUTF8));
        messageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class saveFunc: public Ui_saveFunc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEFUNC_H
