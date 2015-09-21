/* 
 * File:   fileArchiver.cpp
 * Author: matthew
 * 
 * Created on 16 September 2015, 6:38 PM
 */


#include "fileArchiver.h"
#include <exception>
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

    boost::filesystem::path p(filename); //get filename from path
    string file(p.filename().c_str());
    string hash = hash_md5(filename);

    auto_ptr<mongo::DBClientCursor> cursor =
            conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << file << "curhash" << hash)); //change to query filerec
    if (cursor->more()) {
        return false;
    } else {
        return true;
    }
}

bool fileArchiver::exists(string filename) {
    //check for the existance of a filerec with same name
    boost::filesystem::path p(filename); //get filename from path
    string file(p.filename().c_str());
    auto_ptr<mongo::DBClientCursor> cursor =
            conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << file));

    if (cursor->more()) {
        return true;
    } else {
        return false;
    }

}

void fileArchiver::createZipFile(const std::string& localfile, std::string& tempname) {
    //std::string command = "/bin/gzip -c ";    
    std::string command = "/bin/cp ";


    command.append(localfile);
    //command.append(" > ");
    command.append(" " + tempname);

    system(command.c_str());
}

void fileArchiver::insertNew(string filename, string commentp) {

    mongo::GridFS gfs(conn, "fileRecords"); //get a gridfs connection to the database, fileRecords is the name "table"
    gfs.setChunkSize(1024 * 4); //4kb chunck sizes

    std::string tempname = tempnam("/tmp", "ARKIV");
    createZipFile(filename, tempname);

    mongo::BSONObj result = gfs.storeFile(tempname);
    //store the file name in the filerec object as well as other data
    FileRec record;

    boost::filesystem::path p(filename); //get filename from path
    string path(p.filename().c_str());
    record.setFilename(path);

    comment data;
    data.comment = commentp;
    data.version = 0; //first record
    record.appendComment(data);

    string test = result.getField("_id"); //get id from db
    string id;
    boost::tokenizer<> tok(test); //need to break up id as it is in the form "id: objectid('grgrfrbgryrgr')"
    for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
        id = *beg; //last iteration should be the actual id
    }
    record.setBlobName(id); //set id

    //int numBlocks = result.getIntField("length") / result.getIntField("chunkSize") + (result.getIntField("length") % result.getIntField("chunkSize") != 0);
    record.setBlockCount(result.getIntField("length"));
    record.setReferenceVersion(0); //first version as it is insert new
    record.setVersionNum(1);
    //long long v;
    //result.getField("uploadDate").numberLong();
    timespec modtime;
    modtime.tv_sec = 0;
    record.setModTime(modtime);

    record.setHashOriginal(result.getStringField("md5"));
    record.setHashLatest(result.getStringField("md5"));

    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.fs.chunks", MONGO_QUERY("files_id" << mongo::OID(id)));
    while (cursor->more()) {
        BSONObj p = cursor->next();
        BSONElement binData = p.getField("data");
        int leng;
        string data = binData.binData(leng);
        string hash = hash_md5_data(data);
        cout << hash << endl;
        record.appendBlock(hash);
    }

    cout << "file name " << record.getFilename() << endl;
    cout << "version number " << record.getReferenceVersion() << endl;
    cout << "blob id " << record.getBlobName() << endl;
    cout << "length of file " << record.getBlockCount() << endl;
    cout << "date (incorrect) " << record.getModTime().tv_sec << endl;
    cout << "hash of file " << record.getHashOriginal() << endl;
    cout << "hash of blocks " << endl;
    for (vector<string>::iterator it = record.getBlocksBegin(); it != record.getBlocksEnd(); ++it)
        cout << *it << endl;

    cout << "comments " << endl;
    for (vector<comment>::iterator it = record.getCommentsBegin(); it != record.getCommentsEnd(); ++it)
        cout << it->version << " " << it->comment << endl;


    unlink(tempname.c_str());

    record.writeToDB(conn);


}

FileRec* fileArchiver::getDetailsOfLastSaved(string filename) {
    FileRec* record = new FileRec;
    record->readFromDB(conn, filename);
    return record;
}

void fileArchiver::update(string filename, string commentp) {
    FileRec* Origrecord = getDetailsOfLastSaved(filename);

    //create a version record and store the current record in it
    //load in new file, increment version count
    //delete current hashes
    VersionRec newV;

    newV.setFilehash(Origrecord->getHashLatest());
    newV.settmpname(Origrecord->getBlobName());
    newV.setModifyTime(Origrecord->getModTime());
    newV.setLength(Origrecord->getBlockCount());
    newV.setVersionNumber(Origrecord->getReferenceVersion());
    Origrecord->setVersionNum(Origrecord->getVersionNum() + 1);
    Origrecord->setReferenceVersion(Origrecord->getVersionNum() - 1);
    
    //set up blkhashes into the version class
    
    Origrecord->clearBlockHashes();
    
    
    mongo::GridFS gfs(conn, "fileRecords"); //get a gridfs connection to the database, fileRecords is the name "table"
    gfs.setChunkSize(1024 * 4); //4kb chunck sizes

    std::string tempname = tempnam("/tmp", "ARKIV");
    createZipFile(filename, tempname);

    mongo::BSONObj result = gfs.storeFile(tempname);
    //store the file name in the filerec object as well as other data

    boost::filesystem::path p(filename); //get filename from path
    string path(p.filename().c_str());
    Origrecord->setFilename(path);

    comment data;
    data.comment = commentp;
    data.version = Origrecord->getReferenceVersion(); 
    Origrecord->appendComment(data);

    string test = result.getField("_id"); //get id from db
    string id;
    boost::tokenizer<> tok(test); //need to break up id as it is in the form "id: objectid('grgrfrbgryrgr')"
    for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
        id = *beg; //last iteration should be the actual id
    }
    Origrecord->setBlobName(id); //set id

    //int numBlocks = result.getIntField("length") / result.getIntField("chunkSize") + (result.getIntField("length") % result.getIntField("chunkSize") != 0);
    Origrecord->setBlockCount(result.getIntField("length"));
    //long long v;
    //result.getField("uploadDate").numberLong();
    timespec modtime;
    modtime.tv_sec = 0;
    Origrecord->setModTime(modtime);

    Origrecord->setHashLatest(result.getStringField("md5"));

    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.fs.chunks", MONGO_QUERY("files_id" << mongo::OID(id)));
    while (cursor->more()) {
        BSONObj p = cursor->next();
        BSONElement binData = p.getField("data");
        int leng;
        string data = binData.binData(leng);
        string hash = hash_md5_data(data);
        Origrecord->appendBlock(hash);
    }

    cout << "file name " << Origrecord->getFilename() << endl;
    cout << "version number " << Origrecord->getReferenceVersion() << endl;
    cout << "blob id " << Origrecord->getBlobName() << endl;
    cout << "length of file " << Origrecord->getBlockCount() << endl;
    cout << "date (incorrect) " << Origrecord->getModTime().tv_sec << endl;
    cout << "hash of file " << Origrecord->getHashOriginal() << " " << Origrecord->getHashLatest() << endl;
    cout << "hash of blocks " << endl;
    for (vector<string>::iterator it = Origrecord->getBlocksBegin(); it != Origrecord->getBlocksEnd(); ++it)
        cout << *it << endl;

    cout << "comments " << endl;
    for (vector<comment>::iterator it = Origrecord->getCommentsBegin(); it != Origrecord->getCommentsEnd(); ++it)
        cout << it->version << " " << it->comment << endl;


    unlink(tempname.c_str());

   // Origrecord->writeToDB(conn);
     
}

/*
void fileArchiver::retriveVersion(int, string, string);
float fileArchiver::getCurrentVersionNumber(string);
string fileArchiver::getHashOfLastSaved(string);
bool fileArchiver::getComment(string, int);
//vector<versionInfo> fileArchiver::getVersioninfo(std::string);
void fileArchiver::setReference(string, int, string);
 */

fileArchiver::~fileArchiver() {
}

