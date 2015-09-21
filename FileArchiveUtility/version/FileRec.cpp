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

vector<VersionRec>::iterator FileRec::getVersionBegin() {
    return versions.begin();
}

vector<VersionRec>::iterator FileRec::getVersionEnd() {
    return versions.end();
}

vector<string>::iterator FileRec::getCommentsBegin() {
    return comments.begin();
}

vector<string>::iterator FileRec::getCommentsEnd() {
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

void FileRec::appendVersion(VersionRec v) {
    versions.push_back(v);
}

void FileRec::appendComment(string c) {
    comments.push_back(c);
}

void FileRec::readFromDB(DBClientConnection& conn, string filename){

}

void FileRec::writeToDB(mongo::DBClientConnection &conn) {
    BSONObjBuilder record;
    record.append("filename", this->filename);
    record.append("Tempname", this->tempname);
    record.append("curhash", this->recentHash);
    record.append("ovhash", this->origHash);
    record.append("length", this->length);
    record.append("nversions", this->versionCount);
    record.append("Mtnsec", 0);
    record.append("mtsec", 0);
    record.append("currentversion", this->refNum);

    mongo::BSONArrayBuilder bArr;
    mongo::BSONArrayBuilder Comments;
    for (vector<string>::iterator it = blockhashes.begin(); it != blockhashes.end(); ++it) {
        //record.append("$push" << BSON("FileBlkHashes" << *it));
        bArr.append(*it);
    }

    for (vector<string>::iterator it = comments.begin(); it != comments.end(); ++it) {
        //record.append("$push" << BSON("FileBlkHashes" << *it));
        BSONObjBuilder comment;
        comment.append("version", 0); //think about converting from string to struct
        comment.append("comment", *it);
        Comments.append(comment.obj());
    }

    if (!versions.empty()) {
        mongo::BSONArrayBuilder Version;
        for (vector<VersionRec>::iterator it = versions.begin(); it != versions.end(); ++it) {
            //record.append("$push" << BSON("FileBlkHashes" << *it));
            BSONObjBuilder version;
            //get the transformed to BSONobj version record
            Version.append(version.obj());

        }
        record.append("versionRec", Version.arr());
    }

    record.append("FileBlkHashes", bArr.arr());

    record.append("comments", Comments.arr());
    BSONObj result = record.obj();
    conn.insert("fileRecords.Filerec", result);
}

void FileRec::createData(string filename) {
    ifstream testFile(filename.c_str());

    if (testFile.bad()) {
        string err;
        err += "Could not open file \'";
        err += filename;
        err += "\'.";
        throw runtime_error(err);
    }

    // Get metadata on file
    struct stat filedata;
    int result = stat(filename.c_str(), &filedata);
    if (result == -1) {
        string err;
        err += "Could not open file \'";
        err += filename;
        err += "\'.";
        throw runtime_error(err);
    }

    // Set up this record to match the data collected
    setFilename(filename);
    timespec modtime;
    modtime.tv_sec = filedata.st_mtime;
    setModTime(modtime);

    string strHash = hash_md5(filename);
    setHashLatest(strHash);


}

bool FileRec::operator==(const FileRec& other) {
    return (filename == other.filename) && (recentHash == other.recentHash);
}

bool FileRec::operator!=(const FileRec& other) {
    return (filename != other.filename) || (recentHash != other.recentHash);
}
