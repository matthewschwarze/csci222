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
            cout << "already exists" << std::endl;
            //call differs
            if (db.differs(tmp)) {
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
        cout << "getting version 0" << endl;
        db.retriveVersion(0, tmp, comment);
        //for (int i = 0; i < 4; i++)
           // db.removeVersion(i, tmp);
        vector<VersionRec> vers= db.getVersioninfo(tmp);
        cout << "versions info" << endl;
        for(vector<VersionRec>::iterator it = vers.begin(); it != vers.end(); ++it)
            cout << (*it).getVersionNumber() << " " << (*it).getLength() << " " << (*it).getModifyTime().tv_sec << endl;
        
        int curr = db.getCurrentVersionNumber(tmp);
        cout << "current version " <<curr << endl;
        
         string comm = db.getComment(tmp, curr);
        cout << "comment of version " << curr << " " <<comm << endl;
   
        string hash = db.getHashOfLastSaved(tmp);
        cout << "current hash " <<hash << endl;

    } catch (const mongo::DBException &e) {
        std::cout << "caught " << e.what() << std::endl;
    }


    return EXIT_SUCCESS;
}

