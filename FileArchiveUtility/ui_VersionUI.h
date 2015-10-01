/********************************************************************************
** Form generated from reading UI file 'VersionUI.ui'
**
** Created: Thu Oct 1 20:09:26 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERSIONUI_H
#define UI_VERSIONUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_VersionUI
{
public:
    QLineEdit *fileLine;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame;
    QTableView *tableView;
    QPushButton *browseButton;
    QPushButton *saveButton;
    QPushButton *historyButton;
    QPushButton *refButton;
    QPushButton *commentButton;

    void setupUi(QDialog *VersionUI)
    {
        if (VersionUI->objectName().isEmpty())
            VersionUI->setObjectName(QString::fromUtf8("VersionUI"));
        VersionUI->resize(800, 600);
        fileLine = new QLineEdit(VersionUI);
        fileLine->setObjectName(QString::fromUtf8("fileLine"));
        fileLine->setEnabled(false);
        fileLine->setGeometry(QRect(110, 40, 511, 27));
        label = new QLabel(VersionUI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 40, 61, 21));
        label_2 = new QLabel(VersionUI);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 170, 161, 17));
        frame = new QFrame(VersionUI);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(50, 200, 571, 351));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        tableView = new QTableView(frame);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 10, 551, 331));
        browseButton = new QPushButton(VersionUI);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setGeometry(QRect(647, 40, 131, 27));
        saveButton = new QPushButton(VersionUI);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(650, 200, 131, 27));
        historyButton = new QPushButton(VersionUI);
        historyButton->setObjectName(QString::fromUtf8("historyButton"));
        historyButton->setGeometry(QRect(650, 280, 131, 27));
        refButton = new QPushButton(VersionUI);
        refButton->setObjectName(QString::fromUtf8("refButton"));
        refButton->setGeometry(QRect(650, 360, 131, 27));
        commentButton = new QPushButton(VersionUI);
        commentButton->setObjectName(QString::fromUtf8("commentButton"));
        commentButton->setGeometry(QRect(650, 440, 131, 27));

        retranslateUi(VersionUI);

        QMetaObject::connectSlotsByName(VersionUI);
    } // setupUi

    void retranslateUi(QDialog *VersionUI)
    {
        VersionUI->setWindowTitle(QApplication::translate("VersionUI", "VersionUI", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("VersionUI", "File:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("VersionUI", "Version History Table", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("VersionUI", "Browse", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("VersionUI", "Save", 0, QApplication::UnicodeUTF8));
        historyButton->setText(QApplication::translate("VersionUI", "Retrieve Version", 0, QApplication::UnicodeUTF8));
        refButton->setText(QApplication::translate("VersionUI", "Set Reference", 0, QApplication::UnicodeUTF8));
        commentButton->setText(QApplication::translate("VersionUI", "Comments", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VersionUI: public Ui_VersionUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERSIONUI_H
