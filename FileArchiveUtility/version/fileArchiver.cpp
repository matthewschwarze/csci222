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
/*    auto_ptr<DBClientCursor> cursor =
            c.query("tutorial.persons", MONGO_QUERY("age" << age));
    while (cursor->more()) {
        BSONObj p = cursor->next();
        cout << p.getStringField("name") << endl;
    } */
}

bool fileArchiver::exists(string filename) {

}

fileArchiver::~fileArchiver() {
}

