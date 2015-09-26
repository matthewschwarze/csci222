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

void FileRec::readFromDB(mongo::DBClientConnection& conn, string filename) {

    boost::filesystem::path p(filename); //get filename from path
    string file(p.filename().c_str());
    auto_ptr<mongo::DBClientCursor> cursor =
            conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << file));

    if (cursor->more()) {

        BSONObj record = cursor->next();

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


        vector<BSONElement> array = record["comments"].Array();
        for (vector<BSONElement>::iterator ar = array.begin(); ar != array.end(); ++ar) {
            BSONObj commentdata = ar->Obj();
            BSONElement version = commentdata.getField("version");
            BSONElement commentdb = commentdata.getField("comment");

            comment data;
            data.comment = commentdb.String();
            data.version = version.Int();
            appendComment(data);
        }


        if (record.hasElement("versionrec")) {
            vector<BSONElement> array = record["versionrec"].Array();
            for (vector<BSONElement>::iterator it = array.begin(); it != array.end(); ++it) {

                BSONObj versionRecord = it->Obj();
                BSONElement id = versionRecord.getField("id");
                appendVersion(id.String());
            }
        } else {
            cout << "no other versions" << endl;
        }
    }
}

void FileRec::writeToDB(mongo::DBClientConnection &conn) {
    BSONObjBuilder record;
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

    mongo::BSONArrayBuilder bArr;
    mongo::BSONArrayBuilder Comments;
    for (vector<string>::iterator it = blockhashes.begin(); it != blockhashes.end(); ++it) {
        bArr.append(*it);
    }

    for (vector<comment>::iterator it = comments.begin(); it != comments.end(); ++it) {
        BSONObjBuilder comment;
        comment.append("version", it->version); //think about converting from string to struct
        comment.append("comment", it->comment);
        Comments.append(comment.obj());
    }

    if (!versions.empty()) {
        mongo::BSONArrayBuilder Version;
        for (vector<string>::iterator it = versions.begin(); it != versions.end(); ++it) {
            BSONObjBuilder version;
            version.append("id", (*it));
            Version.append(version.obj());
        }
        record.append("versionrec", Version.arr());
    }
    record.append("FileBlkHashes", bArr.arr());
    record.append("comments", Comments.arr());

    BSONObj result = record.obj();
    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << filename));
    if (cursor->more()) {
        conn.update("fileRecords.Filerec", MONGO_QUERY("filename" << filename), result);
    } else {
        conn.insert("fileRecords.Filerec", result);
    }
    string e = conn.getLastError();
    if (!e.empty()) {
        cout << "something failed failed: " << e << std::endl;
        sleep(1);
        exit(1);
    }
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
