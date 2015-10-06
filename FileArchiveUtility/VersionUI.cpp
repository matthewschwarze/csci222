/*
 * File:   VersionUI.cpp
 * Author: lec725
 *
 * Created on 14 September 2015, 2:30 PM
 */

#include "VersionUI.h"
#include "getCommentForm.h"
#include "saveFunc.h"

VersionUI::VersionUI() {
    widget.setupUi(this);
    
    versionBox = new retrieveVersion();
    referenceBox = new setReference();
    commentGet = new getCommentForm();
    saveBox = new saveFunc();
    
    try {
        db = new fileArchiver();
        std::cout << "connected ok" << std::endl;
        std::string tmp = "commentDialog.cpp";
        
        vers=new vector<VersionRec>;
        (*vers)=db->getVersioninfo(tmp);
        
        fileName="commentDialog.cpp";
        
        
        //make the table to display
        //createTable(); //this is a function that is uncommented when testing relating to referencing and versions
        
        //when the buttons are pressed, open their respective UIs and functions
        connect(widget.browseButton, SIGNAL(clicked()), this, SLOT(openFile()));    //open up the native browser to select a file
        commentBox = new commentDialog(db, fileName, versNo);
        connect(widget.commentButton, SIGNAL(clicked()), this, SLOT(showComment())); //open commentDialog.ui's UI
        connect(widget.historyButton, SIGNAL(clicked()), this, SLOT(getVers())); //open retrieveVersion.ui's UI
        connect(widget.refButton, SIGNAL(clicked()), this, SLOT(setRef()));   //open setReference.ui's UI
        connect(widget.saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));   //open the save function and the UI for it
        connect(widget.tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(itemSelection(const QModelIndex &)));

    } catch (const mongo::DBException &e) {
        std::cout << "caught " << e.what() << std::endl;
    }

}

void VersionUI::openFile(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList filenames;
    if (dialog.exec())
        filenames = dialog.selectedFiles();
    
    //go ahead and get the comment
    commentGet->exec();
    string comment = commentGet->get();
    
    //change the filename to a const char* for transferral to a string
    const char* fileN = filenames[0].toStdString().c_str();
    string fname(fileN);
    fileName=fname;
    
    //send the file and the comment to fileArchiver
    if(db->exists(fileName)){
        if(db->differs(fileName)){
            db->update(fileName, comment); //there are differences so create a new version
        }
        else{//add in a message or something saying the file is the same
        }
    }
    else{
        db->insertNew(fileName, comment); //no other files by this name
    }
    
    widget.fileLine->setText(filenames[0]);
    
    (*vers)=db->getVersioninfo(fileName);
    createTable();
}

void VersionUI::createTable(){
    
    //Create a table, populate it with data using addTheData and setModel functions, and then resize the table and display it
    
    archiveTableView* myTable = new archiveTableView(0);
    myTable->addTheData(vers);
    widget.tableView->setModel(myTable);
    widget.tableView->resizeRowsToContents();
    widget.tableView->resizeColumnsToContents();
    widget.tableView->show();
}

void VersionUI::saveFile(){
    
    //checks to see if the version and the file is the same
    //if they are the same, don't save
    //if they aren't, save and store it as a version
    
    if (db->differs(fileName)==true){
        const char* message = "Save successful.";
        saveBox->setMessage(message);
        db->update(fileName, ""); //there are differences so create a new version
    } else {
        const char* message = "The files are the same. No need to save.";
        saveBox->setMessage(message);
    }
    saveBox->exec();
    
    (*vers)=db->getVersioninfo(fileName);
    createTable();

}

void VersionUI::itemSelection(const QModelIndex& index){
    //just a function that gets the row of whatever is highlighted
    VersionRec p=vers->at(index.row());
    versNo = p.getVersionNumber();
}

void VersionUI::showComment(){
    
    //below here, the class should get the comment stored in fileArchiver, convert it into a QTextDocument, and display it
    
    QString comm = db->getComment(fileName, versNo).c_str();
    
    commentBox->setComment(comm);
    
    commentBox->exec();
}

void VersionUI::setRef(){
    //executes the reference and see if the user actually wanted to set it. If so, then delete old records.
    referenceBox->exec();
    if (referenceBox->isOk()==true){
        commentGet->exec();
        string tempComm = commentGet->get();
        db->setReference(fileName, versNo, tempComm);
        (*vers)=db->getVersioninfo(fileName);
        createTable();
    }
}

void VersionUI::getVers(){
    //call the function in retrieveVersion that copies the file into the named file
    versionBox->setValues(db, versNo, fileName);
    versionBox->exec();
}

VersionUI::~VersionUI() {
}
