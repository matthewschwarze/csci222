#include <fstream>
#include <stdexcept>
#include <exception>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "FileHash.h"

#include "FileRec.h"
using namespace std;
using mongo::BSONElement;
using mongo::BSONObj;
using mongo::BSONObjBuilder;
using mongo::BSONObjIterator;

FileRec::FileRec() :
length(0),
versionCount(0),
refNum(0) {
    modifytime.tv_sec = 0;
    modifytime.tv_nsec = 0;
}

string FileRec::getFilename() const {
    return filename;
}

string FileRec::getBlobName() const {
    return tempname;
}

timespec FileRec::getModTime() const {
    return modifytime;
}

int FileRec::getBlockCount() const {
    return length;
}

int FileRec::getVersionNum() const {
    return versionCount;
}

HashType FileRec::getHashOriginal() const {
    return origHash;
}

HashType FileRec::getHashLatest() const {
    return recentHash;
}

int FileRec::getReferenceVersion() const {
    return refNum;
}

vector<HashType>::iterator FileRec::getBlocksBegin() {
    return blockhashes.begin();
}

vector<HashType>::iterator FileRec::getBlocksEnd() {
    return blockhashes.end();
}

vector<std::string>::iterator FileRec::getVersionBegin() {
    return versions.begin();
}

vector<std::string>::iterator FileRec::getVersionEnd() {
    return versions.end();
}

vector<comment>::iterator FileRec::getCommentsBegin() {
    return comments.begin();
}

vector<comment>::iterator FileRec::getCommentsEnd() {
    return comments.end();
}

void FileRec::setFilename(const string& s) {
    filename = s;
}

void FileRec::setBlobName(const string& x) {
    tempname = x;
}

void FileRec::setModTime(timespec x) {
    modifytime = x;
}

void FileRec::setBlockCount(int x) {
    length = x;
}

void FileRec::setVersionNum(int x) {
    versionCount = x;
}

void FileRec::setHashOriginal(HashType x) {
    origHash = x;
}

void FileRec::setHashLatest(HashType x) {
    recentHash = x;
}

void FileRec::setReferenceVersion(int x) {
    refNum = x;
}

void FileRec::appendBlock(HashType hash) {
    blockhashes.push_back(hash);
}

void FileRec::appendVersion(std::string v) {
    versions.push_back(v);
}

void FileRec::appendComment(comment c) {
    comments.push_back(c);
}

void FileRec::clearBlockHashes() {
    blockhashes.clear();
}

void FileRec::clearVersions() {
    versions.clear();
}

void FileRec::clearComments() {
    comments.clear();
}

/**********************************************************
 *reads from db and converts bson to FileRec object
 * 
***********************************************************/
void FileRec::readFromDB(mongo::DBClientConnection& conn, string filename) {

    boost::filesystem::path p(filename); //get filename from path
    string file(p.filename().c_str());
    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << file));

    if (cursor->more()) {

        BSONObj record = cursor->next();
        //get data from db and store in the FileRec
        this->filename = record.getStringField("filename");
        this->tempname = record.getStringField("Tempname");
        this->recentHash = record.getStringField("curhash");
        this->origHash = record.getStringField("ovhash");
        this->length = record.getIntField("length");
        this->versionCount = record.getIntField("nversions");
        this->modifytime.tv_nsec = record.getField("Mtnsec").numberLong();
        this->modifytime.tv_sec = record.getField("mtsec").numberLong();
        this->refNum = record.getIntField("currentversion");

        vector<BSONElement> hashes(record.getField("FileBlkHashes").Array());
        for (vector<BSONElement>::iterator it = hashes.begin(); it != hashes.end(); ++it) {
            appendBlock((*it).String());
        }

        //comments is an array of objects so it takes a bit of nesting to convert
        vector<BSONElement> array = record["comments"].Array(); //convert to array
        for (vector<BSONElement>::iterator ar = array.begin(); ar != array.end(); ++ar) {
            BSONObj commentdata = ar->Obj(); //store object at array[x] into BSONObj
            BSONElement version = commentdata.getField("version"); //convert
            BSONElement commentdb = commentdata.getField("comment");

            comment data;
            data.comment = commentdb.String();
            data.version = version.Int();
            appendComment(data);
        }


        if (record.hasElement("versionrec")) { //again an array of objects
            vector<BSONElement> array = record["versionrec"].Array();
            for (vector<BSONElement>::iterator it = array.begin(); it != array.end(); ++it) {

                BSONObj versionRecord = it->Obj();
                BSONElement id = versionRecord.getField("id");
                appendVersion(id.String());
            }
        } 
    }
}

/**********************************************************
 *convert FileRec to bson, then write to db
 * 
***********************************************************/
void FileRec::writeToDB(mongo::DBClientConnection &conn) {
    BSONObjBuilder record; //build BSONObj
    record.append("filename", this->filename);
    record.append("Tempname", this->tempname);
    record.append("curhash", this->recentHash);
    record.append("ovhash", this->origHash);
    record.append("length", this->length);
    record.append("nversions", this->versionCount);
    /* love you */ long long time = this->modifytime.tv_nsec;
    record.append("Mtnsec", time);
    time = this->modifytime.tv_sec;
    record.append("mtsec", time);
    record.append("currentversion", this->refNum);

    mongo::BSONArrayBuilder bArr; //arrays to store multiple objects inside main object
    mongo::BSONArrayBuilder Comments;
    for (vector<string>::iterator it = blockhashes.begin(); it != blockhashes.end(); ++it) {
        bArr.append(*it);
    }

    for (vector<comment>::iterator it = comments.begin(); it != comments.end(); ++it) {
        BSONObjBuilder comment;
        comment.append("version", it->version); //
        comment.append("comment", it->comment);
        Comments.append(comment.obj());
    }

    if (!versions.empty()) { //if there are id's in the versions collection
        mongo::BSONArrayBuilder Version; //store the id's in an BSONarray
        for (vector<string>::iterator it = versions.begin(); it != versions.end(); ++it) {
            BSONObjBuilder version;
            version.append("id", (*it));
            Version.append(version.obj());
        }
        record.append("versionrec", Version.arr());
    }
    record.append("FileBlkHashes", bArr.arr()); //adding arrays to main record
    record.append("comments", Comments.arr());

    BSONObj result = record.obj();
    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << filename));
    if (cursor->more()) {//already file rec in db so update
        conn.update("fileRecords.Filerec", MONGO_QUERY("filename" << filename), result);
    } else {
        conn.insert("fileRecords.Filerec", result); //must be new record 
    }
    string e = conn.getLastError();
    if (!e.empty()) {
        cout << "something failed failed: " << e << std::endl;
        sleep(1);
        exit(1);
    }
    else{
        cout << "record " << this->refNum << " successfully written to database" << endl;
    }
}

bool FileRec::operator==(const FileRec& other) {
    return (filename == other.filename) && (recentHash == other.recentHash);
}

bool FileRec::operator!=(const FileRec& other) {
    return (filename != other.filename) || (recentHash != other.recentHash);
}
