/*
 * File:   setReference.cpp
 * Author: lee
 *
 * Created on 23 September 2015, 9:37 PM
 */

#include "setReference.h"

setReference::setReference() {
    widget.setupUi(this);
    okToDelete = false;
    
    //the accept, on press, should set that version as the first in the table and delete the other versions before it
    connect(widget.buttonBox, SIGNAL(accepted()), this, SLOT(okToDo()));
    connect(widget.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void setReference::okToDo(){
    okToDelete = true;
    accept();
}

bool setReference::isOk(){
    return okToDelete;
}

setReference::~setReference() {
}
