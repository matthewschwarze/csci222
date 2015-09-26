/* 
 * File:   main.cpp
 * Author: Matthew
 *
 * Created on 9 September 2015, 8:37 PM
 */

#include <iostream>
#include "version/fileArchiver.h"
#include "version/VersionRec.h"
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
        std::string comment = "zipped test ";
        if (db.exists(tmp)) {
            //std::cout << "already exists" << std::endl;
            //call differs
            if (db.differs(tmp)) {
                // db.update(tmp, comment);
                cout << "they are different" << endl;
                 db.update(tmp, comment);
            } else {
                std::cout << "they are not different" << endl;
            }
        } else {
            db.insertNew(tmp, comment);
        }
        tmp = "fileArchiver.cpp";
        comment = "~/";
        //db.retriveVersion(3, tmp, comment);
        //for (int i = 0; i < 4; i++)
           // db.removeVersion(i, tmp);
        vector<VersionRec> vers= db.getVersioninfo(tmp);
        for(vector<VersionRec>::iterator it = vers.begin(); it != vers.end(); ++it)
            cout << (*it).getVersionNumber() << " " << (*it).getLength() << " " << (*it).getModifyTime().tv_sec << endl;

    } catch (const mongo::DBException &e) {
        std::cout << "caught " << e.what() << std::endl;
    }


    return EXIT_SUCCESS;
}

