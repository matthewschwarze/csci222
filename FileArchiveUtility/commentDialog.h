/* 
 * File:   commentDialog.h
 * Author: lee
 *
 * Created on 23 September 2015, 9:40 PM
 */

#ifndef _COMMENTDIALOG_H
#define	_COMMENTDIALOG_H

#include "ui_commentDialog.h"
#include "fileArchiver.h"
#include <string>

class commentDialog : public QDialog {
    Q_OBJECT
public:
    commentDialog(fileArchiver*&, std::string&, int);
    virtual ~commentDialog();
    void setComment(QString &qS);
private:
    Ui::commentDialog widget;
    QString comment;
};

#endif	/* _COMMENTDIALOG_H */
