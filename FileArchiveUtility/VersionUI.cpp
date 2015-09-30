/*
 * File:   VersionUI.cpp
 * Author: lec725
 *
 * Created on 14 September 2015, 2:30 PM
 */

#include "VersionUI.h"
#include "getCommentForm.h"

VersionUI::VersionUI() {
    widget.setupUi(this);
    
    versionBox = new retrieveVersion();
    referenceBox = new setReference();
    commentGet = new getCommentForm();
    
    try {
        db = new fileArchiver();
        std::cout << "connected ok" << std::endl;
        std::string tmp = "commentDialog.cpp";
        
        vector<VersionRec>* vers= new vector<VersionRec>;
        (*vers) = db->getVersioninfo(tmp);
        
        
        //make the table to display
        createTable(vers);
        
        //when the buttons are pressed, open their respective UIs and functions
        connect(widget.browseButton, SIGNAL(clicked()), this, SLOT(openFile()));    //open up the native browser to select a file
        commentBox = new commentDialog(db, fileName);
        connect(widget.commentButton, SIGNAL(clicked()), commentBox, SLOT(exec())); //open commentDialog.ui's UI
        connect(widget.historyButton, SIGNAL(clicked()), versionBox, SLOT(exec())); //open retrieveVersion.ui's UI
        connect(widget.refButton, SIGNAL(clicked()), referenceBox, SLOT(exec()));   //open setReference.ui's UI

    } catch (const mongo::DBException &e) {
        std::cout << "caught " << e.what() << std::endl;
    }
    
    
  
    
    //what happens when save is pressed
    //connect(widget.saveButton, SIGNAL(clicked()), this, SLOT(exec()));
    
    //the main database stuff

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
    //const char* comm = commentGet->get();
    string comment = commentGet->get();
    std::cout << comment << std::endl;
    
    //change the filename to a const char* for transferral to a string
    const char* fileN = filenames[0].toStdString().c_str();
    string fname(fileN);
    fileName=fname;
    
    //send the file and the comment to fileArchiver
    std::cout << "Filename: " << fileName << "\tComment: " << comment << std::endl;
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
    
    widget.fileLine->setText(fileN);
}

void VersionUI::createTable(vector<VersionRec>* vers){
    
    //I think the way I am doing it is wrong: it needs to show after a file is selected
    
    archiveTableView myTable(0);
    myTable.addTheData(vers);
    widget.tableView->setModel(&myTable);
    widget.tableView->resizeRowsToContents();
    widget.tableView->show();
    
    for(vector<VersionRec>::iterator it = (*vers).begin(); it != (*vers).end(); ++it)
        cout << (*it).getVersionNumber() << " " << (*it).getLength() << " " << (*it).getModifyTime().tv_sec << endl;
}

void VersionUI::saveFile(){
    VersionRec VR;
    //get the most recent version of the file and save it in the VR might be the best way
    //then we'll have to compare the versions... I assume we'll have to compare the sizes, though that's really not accurate
    //but maybe we could compare hashes, that may be the way, especially if the same content creates the same hash
    //if they are the same, don't save
    //if they aren't, save and store it as a version
}

VersionUI::~VersionUI() {
}
