/* 
 * File:   getCommentForm.h
 * Author: lee
 *
 * Created on 29 September 2015, 4:40 PM
 */

#ifndef _GETCOMMENTFORM_H
#define	_GETCOMMENTFORM_H

#include "ui_getCommentForm.h"
#include <iostream>
#include <string>
#include "fileArchiver.h"

class getCommentForm : public QDialog {
    Q_OBJECT
public:
    getCommentForm();
    virtual ~getCommentForm();
public slots:
    void pressOK();
    std::string get();
private:
    Ui::getCommentForm widget;
    std::string comment;
};

#endif	/* _GETCOMMENTFORM_H */
