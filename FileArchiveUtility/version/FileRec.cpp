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

vector<int>::iterator FileRec::getVersionIDsBegin() {
    return versions.begin();
}

vector<int>::iterator FileRec::getVersionIDsEnd() {
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

void FileRec::appendVersionID(int v) {
    versions.push_back(v);
}

void FileRec::appendComment(string c) {
    comments.push_back(c);
}

void FileRec::writeToDB(mongo::DBClientConnection &conn) {
    BSONObjBuilder record;
    record.append("filename", this->filename);
    record.append("Tempname", this->tempname);
    record.append("curhash", this->recentHash);
    record.append("ovhash", this->origHash);
    record.append("length", this->length); //maybe change to file length
    record.append("nversions", this->versionCount);
    // record.append("Mtnsec", this->modifytime.tv_nsec);
    // record.append("mtsec", this->modifytime.tv_sec);
    record.append("currentversion", this->refNum);
    mongo::BSONArray arr;
    mongo::BSONArrayBuilder bArr;
    for (vector<string>::iterator it = blockhashes.begin(); it != blockhashes.end(); ++it){
        //record.append("$push" << BSON("FileBlkHashes" << *it));
        arr = BSON_ARRAY(*it);
        bArr.append(arr);
    }

    record.append("FileBlkHashes", bArr.arr());
    BSONObj result = record.obj();
    conn.insert("test.Filerec", result);
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
