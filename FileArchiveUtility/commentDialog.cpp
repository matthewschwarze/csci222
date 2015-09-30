/*
 * File:   commentDialog.cpp
 * Author: lee
 *
 * Created on 23 September 2015, 9:40 PM
 */

#include "commentDialog.h"

commentDialog::commentDialog(fileArchiver* &db, std::string &filename) {
    widget.setupUi(this);
    
    std::cout << filename << std::endl;
    
    //below here, the class should get the comment stored in fileArchiver, convert it into a QTextDocument, and display it
    
    QString comm = db->getComment(filename, 0).c_str();
    QTextDocument* commText = new QTextDocument(comm);
    
    widget.commentField->setDocument(commText);
    
    connect(widget.okButton, SIGNAL(clicked()), this, SLOT(close()));
}

commentDialog::~commentDialog() {
}
