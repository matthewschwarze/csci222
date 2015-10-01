/********************************************************************************
** Form generated from reading UI file 'getCommentForm.ui'
**
** Created: Thu Oct 1 20:09:26 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETCOMMENTFORM_H
#define UI_GETCOMMENTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_getCommentForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *commentLabel;
    QTextEdit *commentEdit;

    void setupUi(QDialog *getCommentForm)
    {
        if (getCommentForm->objectName().isEmpty())
            getCommentForm->setObjectName(QString::fromUtf8("getCommentForm"));
        getCommentForm->resize(400, 300);
        buttonBox = new QDialogButtonBox(getCommentForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        commentLabel = new QLabel(getCommentForm);
        commentLabel->setObjectName(QString::fromUtf8("commentLabel"));
        commentLabel->setGeometry(QRect(40, 30, 331, 17));
        commentEdit = new QTextEdit(getCommentForm);
        commentEdit->setObjectName(QString::fromUtf8("commentEdit"));
        commentEdit->setGeometry(QRect(40, 60, 331, 151));

        retranslateUi(getCommentForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), getCommentForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), getCommentForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(getCommentForm);
    } // setupUi

    void retranslateUi(QDialog *getCommentForm)
    {
        getCommentForm->setWindowTitle(QApplication::translate("getCommentForm", "getCommentForm", 0, QApplication::UnicodeUTF8));
        commentLabel->setText(QApplication::translate("getCommentForm", "Comments to go with version of file:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class getCommentForm: public Ui_getCommentForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETCOMMENTFORM_H
