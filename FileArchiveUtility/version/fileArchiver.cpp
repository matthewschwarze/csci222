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
      /* auto_ptr<mongo::DBClientCursor> cursor =
                conn.query("tutorial.persons", MONGO_QUERY("id" << filename));
        while (cursor->more()) {
            BSONObj p = cursor->next();
            cout << p.getStringField("name") << endl;
        } */
}

bool fileArchiver::exists(string filename) {

}
/*
void fileArchiver::insertNew(string, string);
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

