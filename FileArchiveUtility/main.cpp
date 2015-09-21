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
        std::string tmp = "version/fileArchiver.cpp";  
        std::string comment = "first version of fileArchiver.cpp";
        if(db.exists(tmp)){
            std::cout << "already exists" << std::endl;
            //call differs
            if(db.differs(tmp)){
               // db.update(tmp, comment);
                cout << "they are different" << endl;
                db.update(tmp, comment);
            }
            else{
                std::cout << "they are not different" << endl;
            }
        }else{
            db.insertNew(tmp, comment);
        }
        
    } catch (const mongo::DBException &e) {
        std::cout << "caught " << e.what() << std::endl;
    }
    
    
    return EXIT_SUCCESS;
}

