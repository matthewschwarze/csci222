/*
 * File:   saveFunc.cpp
 * Author: lee
 *
 * Created on 1 October 2015, 1:07 PM
 */

#include "saveFunc.h"

saveFunc::saveFunc() {
    widget.setupUi(this);
    
    connect(widget.okButton, SIGNAL(clicked()), this, SLOT(close()));
}

void saveFunc::setMessage(const char* mess){
    //set the message of what the save should show the user i.e. did it save or not
    message=mess;
    QString displayText(message);
    widget.messageLabel->setWordWrap(true);
    widget.messageLabel->setText(displayText);
}

saveFunc::~saveFunc() {
}
