/********************************************************************************
** Form generated from reading UI file 'setReference.ui'
**
** Created: Thu Oct 1 20:09:26 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETREFERENCE_H
#define UI_SETREFERENCE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_setReference
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *setReference)
    {
        if (setReference->objectName().isEmpty())
            setReference->setObjectName(QString::fromUtf8("setReference"));
        setReference->resize(300, 150);
        buttonBox = new QDialogButtonBox(setReference);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(80, 90, 181, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(setReference);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 331, 17));

        retranslateUi(setReference);

        QMetaObject::connectSlotsByName(setReference);
    } // setupUi

    void retranslateUi(QDialog *setReference)
    {
        setReference->setWindowTitle(QApplication::translate("setReference", "setReference", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("setReference", "OK to set Reference Version?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class setReference: public Ui_setReference {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETREFERENCE_H
