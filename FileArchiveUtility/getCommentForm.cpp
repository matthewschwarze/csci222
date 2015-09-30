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
    QTextDocument* comm = widget.commentEdit->document();
    const char* tempComm = (*comm).toPlainText().toStdString().c_str();
    std::cout << tempComm << std::endl;
    std::string tempStr(tempComm);
    comment=tempStr;
    std::cout << comment << std::endl;
    accept();
}

std::string getCommentForm::get(){
    std::string str(comment);
    return str;
}

getCommentForm::~getCommentForm() {
}
