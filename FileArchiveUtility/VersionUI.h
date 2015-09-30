/* 
 * File:   VersionUI.h
 * Author: lec725
 *
 * Created on 14 September 2015, 2:30 PM
 */

#ifndef _VERSIONUI_H
#define	_VERSIONUI_H

#include "ui_VersionUI.h"
#include "retrieveVersion.h"
#include "setReference.h"
#include "commentDialog.h"
#include "getCommentForm.h"
#include "fileArchiver.h"
#include "VersionRec.h"
#include "mongo/client/dbclient.h"
#include "mongo/bson/bson.h"
#include <cstring>
#include <string>
#include "archiveTableView.h"

using namespace std;
using mongo::BSONElement;
using mongo::BSONObj;
using mongo::BSONObjBuilder;
using mongo::BSONObjIterator;

class VersionUI : public QDialog {
    Q_OBJECT
public:
    VersionUI();
    virtual ~VersionUI();
public slots:
    void openFile();
    void createTable(vector<VersionRec>* vers);
    void saveFile();
private:
    Ui::VersionUI widget;
    commentDialog* commentBox;
    retrieveVersion* versionBox;
    setReference* referenceBox;
    getCommentForm* commentGet;
    fileArchiver* db;
    string fileName;
    const char* comment;
};

#endif	/* _VERSIONUI_H */
