/* 
 * File:   retrieveVersion.h
 * Author: lee
 *
 * Created on 23 September 2015, 9:32 PM
 */

#ifndef _RETRIEVEVERSION_H
#define	_RETRIEVEVERSION_H

#include "ui_retrieveVersion.h"
#include <iostream>
#include <fstream>
#include <QFileDialog>
#include "fileArchiver.h"
#include "VersionRec.h"

class retrieveVersion : public QDialog {
    Q_OBJECT
public:
    retrieveVersion();
    virtual ~retrieveVersion();
    void setValues(fileArchiver* curr, int versionNo, std::string fname);
public slots:
    void openFile(); 
    void pressOK();
private:
    Ui::retrieveVersion widget;
    const char* strName;
    std::string filename;
    std::string dirPath;
    fileArchiver* db;
    int versNo;
};

#endif	/* _RETRIEVEVERSION_H */
