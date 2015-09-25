#ifndef _VERSIONREC_H_
#define _VERSIONREC_H_

#include <vector>
#include <string>
#include <time.h>
#include <mongo/client/dbclient.h>

typedef std::string HashType;
const int BLOCK_SIZE = 4096;

struct VersionDiffBlock {
    int blockNo;
    HashType blockHash;
    int blockLen;
    char blockArr[BLOCK_SIZE];
};

class VersionRec {
private:
    std::string versionid;
    int versionnumber;
    int length;
    std::string tmpname;
    timespec modifytime;
    HashType filehash;
    std::vector<VersionDiffBlock> changes;

public:

    //---- Constructors / Destructors ----//
    VersionRec();

    //---- Accessor Functions ----//
    std::string gettmpname() const;

    std::string getVersionID() const;

    int getVersionNumber() const;

    int getLength() const;

    timespec getModifyTime() const;

    HashType getFileHash() const;

    std::vector<VersionDiffBlock>::iterator getChangesBegin();

    std::vector<VersionDiffBlock>::iterator getChangesEnd();

    //---- Mutator Functions ----//
    void settmpname(std::string t);

    void setVersionID(std::string v);

    void setVersionNumber(int n);

    void setLength(int l);

    void setModifyTime(timespec t);

    void setFilehash(HashType h);

    void changesAppend(VersionDiffBlock b);

    //---- Read / Writing Functions ----//
    void readFromDB(mongo::DBClientConnection conn, int vid);

    void writeToDB(mongo::DBClientConnection conn);

    //---- Overloaded Operators ----//
    bool operator==(const VersionRec& other);

    bool operator!=(const VersionRec& other);

};

#endif
