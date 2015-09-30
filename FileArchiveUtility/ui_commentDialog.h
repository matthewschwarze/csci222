/********************************************************************************
** Form generated from reading UI file 'commentDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENTDIALOG_H
#define UI_COMMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_commentDialog
{
public:
    QPushButton *okButton;
    QTextEdit *commentField;

    void setupUi(QDialog *commentDialog)
    {
        if (commentDialog->objectName().isEmpty())
            commentDialog->setObjectName(QString::fromUtf8("commentDialog"));
        commentDialog->setEnabled(true);
        commentDialog->resize(250, 150);
        okButton = new QPushButton(commentDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(130, 100, 98, 27));
        commentField = new QTextEdit(commentDialog);
        commentField->setObjectName(QString::fromUtf8("commentField"));
        commentField->setEnabled(false);
        commentField->setGeometry(QRect(20, 30, 211, 51));

        retranslateUi(commentDialog);

        QMetaObject::connectSlotsByName(commentDialog);
    } // setupUi

    void retranslateUi(QDialog *commentDialog)
    {
        commentDialog->setWindowTitle(QApplication::translate("commentDialog", "commentDialog", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("commentDialog", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class commentDialog: public Ui_commentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENTDIALOG_H
