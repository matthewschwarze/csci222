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

void fileArchiver::createZipFile(const string& localfile, string& tempname) {
    //std::string command = "/bin/gzip -c ";    
    std::string command = "/bin/cp ";


    command.append(localfile);
    //command.append(" > ");
    command.append(" " + tempname);

    system(command.c_str());
}

void fileArchiver::unZipFile(const string& localfile, string& tempname) {
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
        record.appendBlock(hash);
    }

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

    VersionRec newV;
    stringstream convert; // stream used for the conversion


    newV.setFilehash(Origrecord->getHashLatest());
    newV.settmpname(Origrecord->getBlobName());
    newV.setModifyTime(Origrecord->getModTime());
    newV.setLength(Origrecord->getBlockCount());
    newV.setVersionNumber(Origrecord->getReferenceVersion());
    setVersionBlocks(*(Origrecord), newV); // get block hashes and bin data, store in the version
    newV.writeToDB(conn);

    Origrecord->setVersionNum(Origrecord->getVersionNum() + 1);
    Origrecord->setReferenceVersion(Origrecord->getReferenceVersion() + 1);
//woo
    Origrecord->clearBlockHashes();
    Origrecord->appendVersion(newV.getVersionID());

    //write newV to database

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

    Origrecord->writeToDB(conn);
    delete Origrecord;

}

void fileArchiver::removeVersion(int version, string filename) {
    if (!exists(filename)) {
        return;
    }
    FileRec* Origrecord = getDetailsOfLastSaved(filename); //get latest version

    vector<string> VersionsToKeep; //vector to store version id to keep
    vector<comment> commentsToKeep; // vestor to store comments to keep

    if (Origrecord->getReferenceVersion() == version) {//version to delete is current file rec record
        cout << "delete the latest version" << endl;
        
        
        
    } else {//is a stored version
        //find comment belonging to that version
        for (vector<comment>::iterator it = Origrecord->getCommentsBegin(); it != Origrecord->getCommentsEnd(); ++it) {
            if ((*it).version != version)//keep comments 
                commentsToKeep.push_back((*it));
        }

        for (vector<string>::iterator it = Origrecord->getVersionBegin(); it != Origrecord->getVersionEnd(); ++it) {
            //look for the record that matches
            auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.FileVersion", MONGO_QUERY("_id" << mongo::OID((*it)) << "Version" << version));

            if (cursor->more()) { //found version rec
                VersionRec tmp;
                tmp.readFromDB(conn, (*it)); //read it into memory
                cout << "found version to delete " << (*it) << endl;
                //query all of the file chunks and remove, replace with deleting the array of bin data if i get there 
                auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.fs.chunks", MONGO_QUERY("files_id" << mongo::OID(tmp.gettmpname())));

                string filter = "fileRecords.fs.chunks";
                while (cursor->more()) {
                    BSONObj p = cursor->next();
                    conn.mongo::DBClientBase::remove(filter, MONGO_QUERY("files_id" << mongo::OID(tmp.gettmpname())));
                }
                //remove the file record, won't need if i implement only storing updates
                filter = "fileRecords.fs.files";
                conn.mongo::DBClientBase::remove(filter, MONGO_QUERY("_id" << mongo::OID(tmp.gettmpname())));
                //delete the Version rec
                filter = "fileRecords.FileVersion";
                conn.mongo::DBClientBase::remove(filter, MONGO_QUERY("_id" << mongo::OID((*it))));
                Origrecord->setVersionNum(Origrecord->getVersionNum() - 1);
            } else {//add record id to version to keep
                VersionsToKeep.push_back((*it));
            }
        }
        Origrecord->clearVersions(); //remove current collection
        for (vector<string>::iterator it = VersionsToKeep.begin(); it != VersionsToKeep.end(); ++it)
            Origrecord->appendVersion((*it)); //add version ids to keep
        //boogy man do da
        Origrecord->clearComments(); //remove current collection
        for (vector<comment>::iterator it = commentsToKeep.begin(); it != commentsToKeep.end(); ++it)
            Origrecord->appendComment((*it)); //add comments to keep

        Origrecord->writeToDB(conn); //write to the db
    }
}

void fileArchiver::retriveVersion(int version, string filename, string retrived) {
    if (!exists(filename)) {
        return;
    }

    FileRec* Origrecord = getDetailsOfLastSaved(filename);

    bool found = false;
    string fileRef;
    if (Origrecord->getReferenceVersion() == version) {
        fileRef = Origrecord->getBlobName();
        found = true;
    } else {
        for (vector<string>::iterator it = Origrecord->getVersionBegin(); it != Origrecord->getVersionEnd(); ++it) {
            VersionRec tmp;
            tmp.readFromDB(conn, (*it));
            if (tmp.getVersionNumber() == version) {
                found = true;
                fileRef = tmp.gettmpname();
                break;
            }
        } //get the id's iterate untill version match 
    }
    if (!found) { //work out a way to send a did not find version
        cout << "not found" << endl;
        delete Origrecord;
        return;
    }
    std::string tempname = tempnam("/tmp", "ARKIV");
    fstream tmpfile;
    tmpfile.open(tempname.c_str(), ios::out | ios::binary);
    if (tmpfile.good()) {
        auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.fs.chunks", MONGO_QUERY("files_id" << mongo::OID(fileRef)));
        while (cursor->more()) {
            BSONObj p = cursor->next();
            BSONElement binData = p.getField("data");
            int leng;
            string data = binData.binData(leng);
            tmpfile.write((char*) data.c_str(), leng);
        }

        tmpfile.close();
        retrived += Origrecord->getFilename();
        unZipFile(tempname, retrived);

        unlink(tempname.c_str());
        delete Origrecord;

    } else {
        delete Origrecord;
        return;
    }

}

int fileArchiver::getCurrentVersionNumber(string filename) {
    boost::filesystem::path p(filename); //get filename from path
    string file(p.filename().c_str());

    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << file));

    if (cursor->more()) {
        BSONObj record = cursor->next();
        return record.getIntField("currentversion");
    } else {
        return -1;
    }
}

string fileArchiver::getHashOfLastSaved(string filename) {
    boost::filesystem::path p(filename); //get filename from path
    string file(p.filename().c_str());

    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << file));

    if (cursor->more()) {
        BSONObj record = cursor->next();
        return record.getStringField("curhash");
    } else {
        return file;
    }
}

vector<VersionRec> fileArchiver::getVersioninfo(string filename) {
    boost::filesystem::path p(filename); //get filename from path
    string file(p.filename().c_str());

    vector<VersionRec> versions;

    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << file));

    if (cursor->more()) {
        VersionRec VR;
        BSONObj record = cursor->next();
        if (record.hasElement("versionrec")) {
            vector<BSONElement> array = record["versionrec"].Array();
            for (vector<BSONElement>::iterator it = array.begin(); it != array.end(); ++it) {

                //do a sub query for the record

                BSONObj versionRecord = it->Obj();
                BSONElement version = versionRecord.getField("id");
                string id = version.String();
                auto_ptr<mongo::DBClientCursor> subcursor = conn.query("fileRecords.Fileversion", MONGO_QUERY("_id" << mongo::OID(id)));

                BSONObj subversion = subcursor->next();
                BSONElement versionnum = subversion.getField("version");
                BSONElement length = subversion.getField("Length");
                BSONElement timem = subversion.getField("Mtsec");
                BSONElement timemn = subversion.getField("mtnsec");
                timespec time;
                time.tv_nsec = timemn.Int();
                time.tv_sec = timem.Int();

                VR.setLength(length.Int());
                VR.setModifyTime(time);
                VR.setVersionNumber(versionnum.Int());

                versions.push_back(VR);
                //VR = NULL;
            }
        } else {
            cout << "no other versions" << endl;
        }
        //set up current version
        BSONElement timem = record.getField("Mtsec");
        BSONElement timemn = record.getField("mtnsec");
        timespec time;
        time.tv_nsec = timemn.Int();
        time.tv_sec = timem.Int();

        VR.setLength(record.getIntField("length"));
        VR.setVersionNumber(record.getIntField("currentversion"));
        VR.setModifyTime(time);
        versions.push_back(VR);
    } else {
        return versions;
    }
}

void fileArchiver::setVersionBlocks(FileRec record, VersionRec &version) {
    int i = 0;
    for (vector<string>::iterator it = record.getBlocksBegin(); it != record.getBlocksEnd(); ++it) {
        VersionDiffBlock tmp;
        tmp.blockNo = i;
        tmp.blockHash = (*it);
        version.changesAppend(tmp);
        i++;
    }
}

/*
bool fileArchiver::getComment(string, int);

void fileArchiver::setReference(string, int, string);
 */

fileArchiver::~fileArchiver() {
    //close connection
}

