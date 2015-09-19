/* 
 * File:   fileArchiver.cpp
 * Author: matthew
 * 
 * Created on 16 September 2015, 6:38 PM
 */


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

    //create a filerec object, populate with data

    //retrieve filerec's that match its filename (pk))
    auto_ptr<mongo::DBClientCursor> cursor =
            conn.query("fileRecords.fs.files", MONGO_QUERY("filename" << filename)); //change to query filerec
    if (cursor->more()) {
        BSONObj p = cursor->next();
        //cout <<"hash of file " <<p.getStringField("md5") << endl;
        //compare with hash just got from db
        //if the same return false as they do not differ
    }
}

bool fileArchiver::exists(string filename) {
    //check for the existance of a filerec with same name
    /*
    auto_ptr<mongo::DBClientCursor> cursor =
            conn.query("fileRecords.fs.files", MONGO_QUERY("filename" << filename));
    if (cursor->more()) {
        cout << " no insert" << endl;
        return true;
    } else {
        return false;
    }
     */
}

void fileArchiver::createZipFile(const std::string& localfile, std::string& tempname) {
    //std::string command = "/bin/gzip -c ";    
    std::string command = "/bin/cp ";


    command.append(localfile);
    //command.append(" > ");
    command.append(" " + tempname);

    system(command.c_str());
}

void fileArchiver::insertNew(string filename, string comment) {

    mongo::GridFS gfs(conn, "fileRecords"); //get a gridfs connection to the database, fileRecords is the name "table"
    gfs.setChunkSize(1024 * 4); //4kb chunck sizes

    std::string tempname = tempnam("/tmp", "ARKIV");
    createZipFile(filename, tempname);

    mongo::BSONObj result = gfs.storeFile(tempname);
    //store the file name in the filerec object as well as other data
    FileRec record;

    boost::filesystem::path p(filename);
    string path(p.filename().c_str());
    record.setFilename(path);
    record.appendComment(comment);
    record.setBlobName(result.getField("_id").toString());
    
    cout << "file name " << record.getFilename() << endl; 
    
    cout << "blob id " << record.getBlobName() << endl; 

    unlink(tempname.c_str());


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

