/* 
 * File:   dbtest.cpp
 * Author: matthew
 * 
 * Created on 16 September 2015, 12:18 PM
 */
#include <iostream>
#include <fstream>
#include <string>
#include "dbtest.h"

using namespace std;
using mongo::BSONElement;
using mongo::BSONObj;
using mongo::BSONObjBuilder;
using mongo::BSONObjIterator;

dbtest::dbtest() {
    //read connect from file
    mongo::client::initialize();
    string dbhost;
    ifstream in;
    in.open("versionD/dbproperties.txt");
    if (!in.good()) {
        cout << "could not locate dbproperties.txt!" << endl;
    }
    in >> dbhost;
    conn.connect(dbhost);
}

dbtest::dbtest(const dbtest& orig) {
    mongo::client::initialize();
   // this->conn = orig.conn;
}

dbtest::~dbtest() {
}

bool dbtest::doSelect(){ //select a record
}
bool dbtest::doInsert(){//insert a version record including the file, will need the version class to be implemented
}
bool dbtest::doUpdate(){//update a record
}

/*void createRecord(mongo::DBClientConnection &c) {

    BSONObjBuilder b;
    b.append("name", "Joe");
    b.append("age", 33);
    BSONObj p = b.obj();
    c.insert("test.persons", p);
    cout << "record created" << endl;

    cout << "ignore this unless error occurred  " << c.getLastErrorDetailed().toString() << endl;

    
}*/