/* 
 * File:   main.cpp
 * Author: Matthew
 *
 * Created on 9 September 2015, 8:37 PM
 */

#include <iostream>
#include "mongo/client/dbclient.h"
#include "mongo/bson/bson.h"

using namespace std;
using mongo::BSONElement;
using mongo::BSONObj;
using mongo::BSONObjBuilder;
using mongo::BSONObjIterator;

/*
 * 
 */
void run(mongo::DBClientConnection &c) {
    c.connect("121.211.198.171:27017");
}

void createRecord(mongo::DBClientConnection &c) {

    BSONObjBuilder b;
    b.append("name", "Joe");
    b.append("age", 33);
    BSONObj p = b.obj();
    c.insert("test.persons", p);
    cout << "record created" << endl;

    cout << "ignore this unless error occurred  " << c.getLastErrorDetailed().toString() << endl;

    
}

int main() {
    mongo::client::initialize();
    mongo::DBClientConnection c;
    try {
        run(c);
        std::cout << "connected ok" << std::endl;
        createRecord(c);
    } catch (const mongo::DBException &e) {
        std::cout << "caught " << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

