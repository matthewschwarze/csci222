#include "VersionRec.h"
using namespace std;
using mongo::BSONElement;
using mongo::BSONObj;
using mongo::BSONObjBuilder;
using mongo::BSONObjIterator;

VersionRec::VersionRec() {

    versionid = "";
    versionnumber = 0;
    length = 0;
    filehash = " ";
    modifytime.tv_sec = 0;
    modifytime.tv_nsec = 0;

}

std::string VersionRec::getVersionID() const {
    return versionid;
}

string VersionRec::gettmpname() const {
    return tmpname;
}

int VersionRec::getVersionNumber() const {
    return versionnumber;
}

int VersionRec::getLength() const {
    return length;
}

timespec VersionRec::getModifyTime() const {
    return modifytime;
}

HashType VersionRec::getFileHash() const {
    return filehash;
}

vector<VersionDiffBlock>::iterator VersionRec::getChangesBegin() {
    return changes.begin();
}

vector<VersionDiffBlock>::iterator VersionRec::getChangesEnd() {
    return changes.end();
}

void VersionRec::settmpname(string t) {
    tmpname = t;
}

void VersionRec::setVersionID(std::string v) {
    versionid = v;
}

void VersionRec::setVersionNumber(int n) {
    versionnumber = n;
}

void VersionRec::setLength(int l) {
    length = l;
}

void VersionRec::setModifyTime(timespec t) {
    modifytime = t;
}

void VersionRec::setFilehash(HashType h) {
    filehash = h;
}

void VersionRec::changesAppend(VersionDiffBlock b) {
    changes.push_back(b);
}

void VersionRec::readFromDB(mongo::DBClientConnection& conn, string versionID) {

    auto_ptr<mongo::DBClientCursor> cursor =
            conn.query("fileRecords.FileVersion", MONGO_QUERY("_id" << mongo::OID(versionID)));

    if (cursor->more()) {

        BSONObj record = cursor->next();
        this->versionid = versionID;
        this->tmpname = record.getStringField("Tempname");
        this->filehash = record.getStringField("filehash");
        this->length = record.getIntField("length");
        this->modifytime.tv_nsec = record.getField("Mtnsec").numberLong();
        this->modifytime.tv_sec = record.getField("mtsec").numberLong();
        this->versionnumber = record.getIntField("Version");

        vector<BSONElement> hashes(record.getField("Blktable").Array());
        for (vector<BSONElement>::iterator it = hashes.begin(); it != hashes.end(); ++it) {

            BSONObj blockdata = it->Obj();
            BSONElement blocknum = blockdata.getField("Blknum");
            BSONElement blockhash = blockdata.getField("hash");

            VersionDiffBlock tmp;
            tmp.blockNo = blocknum.Int();
            tmp.blockHash = blockhash.String();
            changesAppend(tmp);
        }
    }
    else{
        cout << "could not find version " << versionID << endl;
    }
}

void VersionRec::writeToDB(mongo::DBClientConnection& conn) {

    BSONObjBuilder record;

    if (this->versionid.empty()) {
        record.genOID();
    } else {
        mongo::OID theoid(this->versionid);
        record.append("_id", theoid);
    }

    record.append("Tempname", this->tmpname);
    record.append("filehash", this->filehash);
    record.append("length", this->length);
    record.append("Version", this->versionnumber);
    /* love you */ long long time = this->modifytime.tv_nsec;
    record.append("Mtnsec", time);
    time = this->modifytime.tv_sec;
    record.append("mtsec", time);

    mongo::BSONArrayBuilder Version;
    for (vector<VersionDiffBlock>::iterator it = changes.begin(); it != changes.end(); ++it) {
        BSONObjBuilder version;
        version.append("Blknum", (*it).blockNo);
        version.append("hash", (*it).blockHash);
        Version.append(version.obj());
    }
    record.append("Blktable", Version.arr());

    BSONObj result = record.obj();
    if (this->versionid.empty()) {
        mongo::BSONElement thing;
        result.getObjectID(thing);
        mongo::OID anoid = thing.OID();
        this->versionid = anoid.toString();
    }

    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.FileVersion", MONGO_QUERY("_id" << mongo::OID(this->versionid)));
    if (cursor->more()) {
        conn.update("fileRecords.FileVersion", MONGO_QUERY("_id" << mongo::OID(this->versionid)), result);
    } else {
        conn.insert("fileRecords.FileVersion", result);
    }

    string e = conn.getLastError();
    if (!e.empty()) {
        cout << "something failed failed: " << e << std::endl;
        sleep(1);
        exit(1);
    }
    else{
        cout << "Version " << this->versionnumber << " successfully written to database" << endl;
    }
}