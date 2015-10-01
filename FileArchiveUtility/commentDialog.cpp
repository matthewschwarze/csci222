/*
 * File:   commentDialog.cpp
 * Author: lee
 *
 * Created on 23 September 2015, 9:40 PM
 */

#include "commentDialog.h"

commentDialog::commentDialog(fileArchiver* &db, std::string &filename, int versNo) {
    widget.setupUi(this);
    
    connect(widget.okButton, SIGNAL(clicked()), this, SLOT(close()));

}

void commentDialog::setComment(QString &qS){
    //display the comment
    QTextDocument* commText = new QTextDocument(qS);
    widget.commentField->setDocument(commText);
}

commentDialog::~commentDialog() {
}
