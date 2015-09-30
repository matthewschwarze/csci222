/*
 * File:   setReference.cpp
 * Author: lee
 *
 * Created on 23 September 2015, 9:37 PM
 */

#include "setReference.h"

setReference::setReference() {
    widget.setupUi(this);
    
    //the accept, on press, should set that version as the first in the table and delete the other version
    //this requires the fileArchiver to be sent in by reference
    //it also needs to call getCommentForm for the version set
    connect(widget.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(widget.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

setReference::~setReference() {
}
