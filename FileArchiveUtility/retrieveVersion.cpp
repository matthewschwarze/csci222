/*
 * File:   retrieveVersion.cpp
 * Author: lee
 *
 * Created on 23 September 2015, 9:32 PM
 */

#include "retrieveVersion.h"

retrieveVersion::retrieveVersion() {
    widget.setupUi(this);
    
    //pressOK gets the filename stored in the private member from openFile
    //these are just calls for what happens on their button clicks
    connect(widget.browseButton, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(widget.buttonBox, SIGNAL(accepted()), this, SLOT(pressOK()));
    connect(widget.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void retrieveVersion::openFile(){
    //get the filename
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList filenames;
    if (dialog.exec())
        filenames = dialog.selectedFiles();
    //show the filename back to the user
    widget.fileRow->setText(filenames[0].toStdString().c_str());
    //set the filename to "filename"
    std::string tempStr(filenames[0].toStdString().c_str());
    dirPath=tempStr;    
}

void retrieveVersion::pressOK(){
    QString name = widget.nameRow->text();
    strName = name.toStdString().c_str();
    std::string wholePath = dirPath + "/" + strName;
    
    //Copy the file on OK
    db->retriveVersion(versNo, filename, wholePath);
    
    accept();
}

void retrieveVersion::setValues(fileArchiver* curr, int versionNo, std::string fname){
    db=curr;
    versNo=versionNo;
    filename = fname;
}

retrieveVersion::~retrieveVersion() {
}
