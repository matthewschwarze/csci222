/*
 * File:   getCommentForm.cpp
 * Author: lee
 *
 * Created on 29 September 2015, 4:40 PM
 */

#include "getCommentForm.h"
#include "commentDialog.h"

getCommentForm::getCommentForm() {
    widget.setupUi(this);
    
    connect(widget.buttonBox, SIGNAL(accepted()), this, SLOT(pressOK()));
    connect(widget.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void getCommentForm::pressOK(){
    //get the comment on accept, store it
    QTextDocument* comm = widget.commentEdit->document();
    const char* tempComm = (*comm).toPlainText().toStdString().c_str();
    std::string tempStr(tempComm);
    comment=tempStr;
    accept();
}

std::string getCommentForm::get(){
    //return the string stored last
    std::string str(comment);
    return str;
}

getCommentForm::~getCommentForm() {
}
