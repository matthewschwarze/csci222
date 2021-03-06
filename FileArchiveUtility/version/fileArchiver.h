/* 
 * File:   fileArchiver.h
 * Author: matthew
 *
 * Created on 16 September 2015, 6:38 PM
 */

#ifndef FILEARCHIVER_H
#define	FILEARCHIVER_H
#include "mongo/client/dbclient.h"
#include "mongo/bson/bson.h"
#include "mongo/client/dbclientcursor.h"
#include "mongo/client/gridfs.h"
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include "FileRec.h"
#include "VersionRec.h"
#include "FileHash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>

class fileArchiver {
private:
    mongo::DBClientConnection conn;
    void createZipFile(const std::string &,std::string&);
    void unZipFile(const std::string &,std::string&);
public:
    fileArchiver();
    //fileArchiver(const fileArchiver& orig);
    bool differs(std::string);
    bool exists(std::string);
    void insertNew(std::string, std::string);
    void update(std::string, std::string);
    void retriveVersion(int, std::string, std::string);
    int getCurrentVersionNumber(std::string);
    std::string getHashOfLastSaved(std::string);
    std::string getComment(std::string, int);
    //vector<versionInfo> getVersioninfo(std::string);
    FileRec* getDetailsOfLastSaved(std::string);
    std::vector<VersionRec> getVersioninfo(std::string);
    void setReference(std::string, int, std::string);
    void setVersionBlocks(FileRec, VersionRec &);
    void removeVersion(int, std::string);
    ~fileArchiver();


};

#endif	/* FILEARCHIVER_H */

