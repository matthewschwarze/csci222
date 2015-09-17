/* 
 * File:   fileArchiver.cpp
 * Author: matthew
 * 
 * Created on 16 September 2015, 6:38 PM
 */
#include <iostream>
#include <fstream>
#include <string>

#include "fileArchiver.h"
using namespace std;
using mongo::BSONElement;
using mongo::BSONObj;
using mongo::BSONObjBuilder;
using mongo::BSONObjIterator;

fileArchiver::fileArchiver() {
    mongo::client::initialize();
    string dbhost;
    ifstream in;
    in.open("version/dbproperties.txt");
    if (!in.good()) {
        cout << "could not locate dbproperties.txt!" << endl;
    }
    in >> dbhost;
    conn.connect(dbhost);
}

bool fileArchiver::differs(string filename) {
    auto_ptr<mongo::DBClientCursor> cursor =
            conn.query("fs.files", MONGO_QUERY("filename" << filename));
    while (cursor->more()) {
        BSONObj p = cursor->next();
        cout << p.getStringField("filename") << endl;
    }
}

bool fileArchiver::exists(string filename) {
    auto_ptr<mongo::DBClientCursor> cursor =
            conn.query("fs.files", MONGO_QUERY("filename" << filename));
    if (cursor->more()) {
        return true;
    } else {
        return false;
    }
}


void fileArchiver::insertNew(string filename, string comment){
    mongo::GridFS gfs(conn, "fileRecords");//get a gridfs connection to the database, fileRecords is the name "table"
    gfs. = 1024 * 256;

    mongo::BSONObj result = gfs.storeFile(filename);
}
 /*
void fileArchiver::update(string, string);
void fileArchiver::retriveVersion(int, string, string);
float fileArchiver::getCurrentVersionNumber(string);
string fileArchiver::getHashOfLastSaved(string);
bool fileArchiver::getComment(string, int);
//vector<versionInfo> fileArchiver::getVersioninfo(std::string);
void fileArchiver::setReference(string, int, string);
 */

fileArchiver::~fileArchiver() {
}

