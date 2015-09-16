/* 
 * File:   main.cpp
 * Author: Matthew
 *
 * Created on 9 September 2015, 8:37 PM
 */

#include <iostream>
#include "version/dbtest.h"
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
        dbtest db;
        std::cout << "connected ok" << std::endl;
    } catch (const mongo::DBException &e) {
        std::cout << "caught " << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

