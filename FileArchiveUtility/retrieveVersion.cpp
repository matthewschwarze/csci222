/*
 * File:   retrieveVersion.cpp
 * Author: lee
 *
 * Created on 23 September 2015, 9:32 PM
 */

#include "retrieveVersion.h"

retrieveVersion::retrieveVersion() {
    widget.setupUi(this);
    
    //pressOK needs to get the filename stored in the private member from openFile
    connect(widget.browseButton, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(widget.buttonBox, SIGNAL(accepted()), this, SLOT(pressOK()));
    connect(widget.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    
    //Get the file name from retrieveVersion nameRow
}

void retrieveVersion::openFile(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList filenames;
    if (dialog.exec())
        filenames = dialog.selectedFiles();
    widget.fileRow->setText(filenames[0].toStdString().c_str());
}

void retrieveVersion::pressOK(){
    QString name = widget.nameRow->text();
    strName = name.toStdString().c_str();
    std::cout << strName << std::endl;
    accept();
}

retrieveVersion::~retrieveVersion() {
}
