#include "VersionRec.h"
using namespace std;

VersionRec::VersionRec() {

    versionid = 0;
    versionnumber = 0;
    length = 0;
    filehash = " ";
    modifytime.tv_sec = 0;
    modifytime.tv_nsec = 0;

}

int VersionRec::getVersionID() const {
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

void VersionRec::setVersionID(int v) {
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