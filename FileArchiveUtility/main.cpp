/* 
 * File:   main.cpp
 * Author: Matthew
 *
 * Created on 9 September 2015, 8:37 PM
 */

#include <iostream>
#include "version/fileArchiver.h"
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



int main() {
    
    try {
        fileArchiver db;
        std::cout << "connected ok" << std::endl;
        std::string tmp = "filename";
        db.exists(tmp);
    } catch (const mongo::DBException &e) {
        std::cout << "caught " << e.what() << std::endl;
    }
    
    
    return EXIT_SUCCESS;
}

