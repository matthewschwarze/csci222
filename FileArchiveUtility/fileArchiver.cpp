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
    in.open("dbproperties.txt");
    if (!in.good()) {
        cout << "could not locate dbproperties.txt!" << endl;
    }
    in >> dbhost;
    conn.connect(dbhost);
}

/**********************************************************
 *checks to see if two files of same name have equal hash
 * true when they do differ
 ***********************************************************/

bool fileArchiver::differs(string filename) {

    boost::filesystem::path p(filename); //get filename from path
    string file(p.filename().c_str());
    std::string tempname = tempnam("/tmp", "ARKIV");
    createZipFile(filename, tempname);

    string hash = hash_md5(tempname);
    unlink(tempname.c_str());
    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << file << "curhash" << hash)); //change to query filerec
    if (cursor->more()) {
        return false;
    } else {
        return true;
    }
}

/**********************************************************
 *checks to see if a record exists of the same name
 * true when record already exists
 ***********************************************************/
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

/**********************************************************
 *creates a zip file of given localfile to tempname
 * 
 ***********************************************************/
void fileArchiver::createZipFile(const string& localfile, string& tempname) {
    std::string command = "/bin/gzip -c ";
    //std::string command = "/bin/cp ";

    command.append(localfile);
    command.append(" > ");
    command.append(" " + tempname);

    system(command.c_str());
}

/**********************************************************
 *unzips file of given localfile to tempname
 * 
 ***********************************************************/
void fileArchiver::unZipFile(const string& localfile, string& tempname) {
    std::string command = "/bin/gunzip -c ";
    //std::string command = "/bin/cp ";

    command.append(localfile);
    command.append(" > ");
    command.append(" " + tempname);

    system(command.c_str());
}

/**********************************************************
 *inserts a new record into the database
 * 
 ***********************************************************/
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
    long long v = result.getField("uploadDate").Date().millis; //get time in milliseconds
    timespec modtime;
    modtime.tv_nsec = v;
    modtime.tv_sec = v / 1000;
    record.setModTime(modtime);

    record.setHashOriginal(result.getStringField("md5")); //getting hash from db
    record.setHashLatest(result.getStringField("md5"));

    //getting the hash of individual blocks
    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.fs.chunks", MONGO_QUERY("files_id" << mongo::OID(id)));
    while (cursor->more()) {
        BSONObj p = cursor->next();
        BSONElement binData = p.getField("data");
        int leng;
        string data = binData.binData(leng);
        string hash = hash_md5_data(data);
        record.appendBlock(hash); //store hash
    }
    unlink(tempname.c_str()); // remove tmp file
    record.writeToDB(conn); //write record to db
}

/**********************************************************
 *gets details of last record to be put into db for that filename
 * 
 ***********************************************************/
FileRec* fileArchiver::getDetailsOfLastSaved(string filename) {
    FileRec* record = new FileRec;
    record->readFromDB(conn, filename);
    return record;
}

/**********************************************************
 *updates an existing record
 * 
 ***********************************************************/
void fileArchiver::update(string filename, string commentp) {
    FileRec* Origrecord = getDetailsOfLastSaved(filename); //get current record for the file

    VersionRec newV; //used to store the current fileRec 

    newV.setFilehash(Origrecord->getHashLatest());
    newV.settmpname(Origrecord->getBlobName());
    newV.setModifyTime(Origrecord->getModTime());
    newV.setLength(Origrecord->getBlockCount());
    newV.setVersionNumber(Origrecord->getReferenceVersion());
    setVersionBlocks(*(Origrecord), newV); // get block hashes and bin data, store in the version
    newV.writeToDB(conn); //write new versionRec to db

    //set up fileRec to contain data from newly inserted file
    Origrecord->setVersionNum(Origrecord->getVersionNum() + 1);
    Origrecord->setReferenceVersion(Origrecord->getReferenceVersion() + 1);

    Origrecord->clearBlockHashes();
    Origrecord->appendVersion(newV.getVersionID());

    mongo::GridFS gfs(conn, "fileRecords"); //get a gridfs connection to the database, fileRecords is the name "table"
    gfs.setChunkSize(1024 * 4); //4kb chunck sizes

    std::string tempname = tempnam("/tmp", "ARKIV");
    createZipFile(filename, tempname);

    mongo::BSONObj result = gfs.storeFile(tempname);
    //store the file name in the filerec object as well as other data

    boost::filesystem::path p(filename); //get filename from path
    string path(p.filename().c_str());
    Origrecord->setFilename(path); //don't need to do this as filename hasn't changed 

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

    Origrecord->setBlockCount(result.getIntField("length"));

    long long v = result.getField("uploadDate").Date().millis;
    timespec modtime;
    modtime.tv_nsec = v;
    modtime.tv_sec = v / 1000;
    Origrecord->setModTime(modtime);

    Origrecord->setHashLatest(result.getStringField("md5")); //don't update the original hash

    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.fs.chunks", MONGO_QUERY("files_id" << mongo::OID(id)));
    while (cursor->more()) {
        BSONObj p = cursor->next();
        BSONElement binData = p.getField("data");
        int leng;
        string data = binData.binData(leng);
        string hash = hash_md5_data(data);
        Origrecord->appendBlock(hash);
    }
    unlink(tempname.c_str());

    Origrecord->writeToDB(conn); //write updated fileRec to db
    delete Origrecord;

}

/**********************************************************
 *removes a given version from the db
 * 
 ***********************************************************/
void fileArchiver::removeVersion(int version, string filename) {
    if (!exists(filename)) { //record dosen't exist
        cout << "no Record: " << filename << " found!" << endl;
        return;
    }
    FileRec* Origrecord = getDetailsOfLastSaved(filename); //get latest version

    vector<string> VersionsToKeep; //vector to store version id to keep
    vector<comment> commentsToKeep; // vestor to store comments to keep

    if (Origrecord->getReferenceVersion() == version) {//version to delete is current file rec record
        string id;
        for (vector<comment>::iterator it = Origrecord->getCommentsBegin(); it != Origrecord->getCommentsEnd(); ++it) {
            if ((*it).version != version)//keep comments 
                commentsToKeep.push_back((*it));
        }
        for (vector<string>::iterator it = Origrecord->getVersionBegin(); it != Origrecord->getVersionEnd(); ++it) {
            id = (*it); //get the id of the next most recent version, stored in chronological order
        }
        for (vector<string>::iterator it = Origrecord->getVersionBegin(); it != Origrecord->getVersionEnd(); ++it) {
            if (id != (*it)) {
                VersionsToKeep.push_back((*it)); //removing the version to become the new fileRec from versions collection
            }
        }

        if (id != "") { //if there is a valid version
            VersionRec newCurrFile;
            newCurrFile.readFromDB(conn, id); //read it into memory

            auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.fs.chunks", MONGO_QUERY("files_id" << mongo::OID(Origrecord->getBlobName())));
            string filter = "fileRecords.fs.chunks";
            while (cursor->more()) { //remove original record data
                BSONObj p = cursor->next();
                conn.mongo::DBClientBase::remove(filter, MONGO_QUERY("files_id" << mongo::OID(Origrecord->getBlobName())));
            }
            //remove the file record, won't need if i implement only storing updates
            filter = "fileRecords.fs.files";
            conn.mongo::DBClientBase::remove(filter, MONGO_QUERY("_id" << mongo::OID(Origrecord->getBlobName())));

            //update fileRec
            Origrecord->setVersionNum(Origrecord->getVersionNum() - 1);
            Origrecord->setBlobName(newCurrFile.gettmpname());
            Origrecord->setBlockCount(newCurrFile.getLength());
            Origrecord->setHashLatest(newCurrFile.getFileHash());
            Origrecord->setHashOriginal(newCurrFile.getFileHash());
            Origrecord->setModTime(newCurrFile.getModifyTime());
            Origrecord->setReferenceVersion(newCurrFile.getVersionNumber());

            Origrecord->clearBlockHashes();
            for (vector<VersionDiffBlock>::iterator it = newCurrFile.getChangesBegin(); it != newCurrFile.getChangesEnd(); ++it)
                Origrecord->appendBlock((*it).blockHash);

            Origrecord->clearVersions(); //remove current collection
            for (vector<string>::iterator it = VersionsToKeep.begin(); it != VersionsToKeep.end(); ++it)
                Origrecord->appendVersion((*it)); //add version ids to keep

            Origrecord->clearComments(); //remove current collection
            for (vector<comment>::iterator it = commentsToKeep.begin(); it != commentsToKeep.end(); ++it)
                Origrecord->appendComment((*it)); //add comments to keep

            //remove the version that is now the fileRec from the FileVersion collection
            filter = "fileRecords.FileVersion";
            conn.mongo::DBClientBase::remove(filter, MONGO_QUERY("_id" << mongo::OID(id)));

            Origrecord->writeToDB(conn); //write to the db
            cout << "Record " << id << " successfully removed from database" << endl;

        } else {//no versions left delete whole record
            auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.fs.chunks", MONGO_QUERY("files_id" << mongo::OID(Origrecord->getBlobName())));
            string filter = "fileRecords.fs.chunks";
            while (cursor->more()) { //remove orginal record data
                BSONObj p = cursor->next();
                conn.mongo::DBClientBase::remove(filter, MONGO_QUERY("files_id" << mongo::OID(Origrecord->getBlobName())));
            }
            //remove the file record, won't need if i implement only storing updates
            filter = "fileRecords.fs.files";
            conn.mongo::DBClientBase::remove(filter, MONGO_QUERY("_id" << mongo::OID(Origrecord->getBlobName())));
            //delete the Version rec
            filter = "fileRecords.Filerec";
            conn.mongo::DBClientBase::remove(filter, MONGO_QUERY("filename" << Origrecord->getFilename()));
            cout << "Entire record successfully removed from database" << endl;

        }
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
                cout << "Record ID" << (*it) << " successfully removed from database" << endl;

            } else {//add record id to version to keep
                VersionsToKeep.push_back((*it));
            }
        }
        Origrecord->clearVersions(); //remove current collection
        for (vector<string>::iterator it = VersionsToKeep.begin(); it != VersionsToKeep.end(); ++it)
            Origrecord->appendVersion((*it)); //add version ids to keep

        Origrecord->clearComments(); //remove current collection
        for (vector<comment>::iterator it = commentsToKeep.begin(); it != commentsToKeep.end(); ++it)
            Origrecord->appendComment((*it)); //add comments to keep

        Origrecord->writeToDB(conn); //write to the db
    }
}

/**********************************************************
 *retrive a version from the db  to user specified path
 * 
 ***********************************************************/
void fileArchiver::retriveVersion(int version, string filename, string retrived) {
    if (!exists(filename)) {
        cout << "no Record: " << filename << " found!" << endl;
        return;
    }

    FileRec* Origrecord = getDetailsOfLastSaved(filename);

    bool found = false;
    string fileRef;
    if (Origrecord->getReferenceVersion() == version) { //current fileRec is the version they are after
        fileRef = Origrecord->getBlobName();
        found = true;
    } else {//check in the version records
        for (vector<string>::iterator it = Origrecord->getVersionBegin(); it != Origrecord->getVersionEnd(); ++it) {
            VersionRec tmp;
            tmp.readFromDB(conn, (*it));
            if (tmp.getVersionNumber() == version) {
                found = true;
                fileRef = tmp.gettmpname();
                break;
            }
        } //get the id's iterate until version match 
    }
    if (!found) { //work out a way to send a did not find version
        cout << "version not found" << endl;
        delete Origrecord;
        return;
    }
    std::string tempname = tempnam("/tmp", "ARKIV"); // create tmp file to load data into
    tempname += ".gz";
    BSONObjBuilder record;
    record.append("_id", mongo::OID(fileRef));
    mongo::GridFS gfs(conn, "fileRecords");
    BSONObj test = record.obj();

    mongo::GridFile afile = gfs.findFile(test);
    unsigned long long length = afile.write(tempname); //write to tmp file
    //retrived += Origrecord->getFilename(); //adds file name to given path
    unZipFile(tempname, retrived); //unzips and places file in given directory

    unlink(tempname.c_str());
    delete Origrecord;
}

/**********************************************************
 *returns information about the different versions
 * length, version and modifytime (seconds) are set and 
 * returned in the VersionRec objects
 ***********************************************************/
vector<VersionRec> fileArchiver::getVersioninfo(string filename) {
    FileRec * Origrecord = getDetailsOfLastSaved(filename);
    vector<VersionRec> versions; //to store the version info
    for (vector<string>::iterator it = Origrecord->getVersionBegin(); it != Origrecord->getVersionEnd(); ++it) {
        //get all the versions from the db using id's stored in the versions collection
        VersionRec VR;
        auto_ptr<mongo::DBClientCursor> subcursor = conn.query("fileRecords.FileVersion", MONGO_QUERY("_id" << mongo::OID((*it))));

        BSONObj subversion = subcursor->next();
        BSONElement versionnum = subversion.getField("Version");
        BSONElement length = subversion.getField("length");
        timespec time;
        time.tv_nsec = subversion.getField("Mtnsec").numberLong();
        time.tv_sec = subversion.getField("mtsec").numberLong();

        VR.setLength(length.Int());
        VR.setModifyTime(time);
        VR.setVersionNumber(versionnum.Int());
        versions.push_back(VR);
    }
    //put current version into a version rec as well
    VersionRec VR;
    VR.setLength(Origrecord->getBlockCount());
    VR.setVersionNumber(Origrecord->getReferenceVersion());
    VR.setModifyTime(Origrecord->getModTime());
    versions.push_back(VR);
    return versions;
}

/**********************************************************
 *used to set and store data in the VersionDiffBlock struct
 * in VersionRec
 ***********************************************************/
void fileArchiver::setVersionBlocks(FileRec record, VersionRec &version) {
    int i = 0; //copy blocks from fileRec into the VersionRec
    for (vector<string>::iterator it = record.getBlocksBegin(); it != record.getBlocksEnd(); ++it) {
        VersionDiffBlock tmp;
        tmp.blockNo = i;
        tmp.blockHash = (*it);
        version.changesAppend(tmp);
        i++;
    }
}

/**********************************************************
 *gets comment for a given record
 * 
 ***********************************************************/
string fileArchiver::getComment(string filename, int version) {
    FileRec * Origrecord = getDetailsOfLastSaved(filename);
    string Comment = "";

    for (vector<comment>::iterator it = Origrecord->getCommentsBegin(); it != Origrecord->getCommentsEnd(); ++it) {
        if ((*it).version == version)//keep comment
            Comment = (*it).comment;
    }
    return Comment;
}

/**********************************************************
 *returns current versions number
 * 
 ***********************************************************/
int fileArchiver::getCurrentVersionNumber(string filename) {
    int refnum = -1;
    FileRec * Origrecord = getDetailsOfLastSaved(filename);
    refnum = Origrecord->getReferenceVersion();
    return refnum;
}

/**********************************************************
 *gets hash of current fileRec
 * 
 ***********************************************************/
string fileArchiver::getHashOfLastSaved(string filename) {
    string hash = "";
    FileRec * Origrecord = getDetailsOfLastSaved(filename);
    hash = Origrecord->getHashLatest();
    return hash;
}

/**********************************************************
 *basically makes this the new original record, since whole files
 * are stored not the updates there is no need for such a function
 * but to emulate what it should do, it deletes all versions
 * before it and sets the orginial hash to its hash
 ***********************************************************/
void fileArchiver::setReference(string filename, int version, string comment) { //remove all versions insert new

    FileRec * Origrecord = getDetailsOfLastSaved(filename);


    vector<string> versions; //to store the version id
    string hash;
    for (vector<string>::iterator it = Origrecord->getVersionBegin(); it != Origrecord->getVersionEnd(); ++it) {
        //get all the versions from the db using id's stored in the versions collection
        VersionRec VR;
        auto_ptr<mongo::DBClientCursor> subcursor = conn.query("fileRecords.FileVersion", MONGO_QUERY("_id" << mongo::OID((*it))));

        BSONObj subversion = subcursor->next();
        BSONElement versionnum = subversion.getField("Version");
        if (versionnum.Int() < version) //version older than reference
        {
            removeVersion(versionnum.Int(), filename);
        } else {
            versions.push_back((*it));
            if (version == versionnum.Int()) {//set the original hash to the new reference version hash
                BSONElement versionnum = subversion.getField("hash");
                hash = versionnum.toString();
                cout << hash << endl;
            }
        }
    }
    delete Origrecord; //changes made in delete need to get update
    Origrecord = getDetailsOfLastSaved(filename);
    Origrecord->setHashOriginal(hash);
    Origrecord->clearVersions();
    for (vector<string>::iterator it = versions.begin(); it != versions.end(); ++it) {
        Origrecord->appendVersion((*it));
    }

    vector<struct comment> newComments;
    for (vector<struct comment>::iterator it = Origrecord->getCommentsBegin(); it != Origrecord->getCommentsEnd(); ++it) {
        if ((*it).version >= version) { //keeps comments of versions newer than new reference record

            if ((*it).version == version) {
                (*it).comment = comment;
            }
            newComments.push_back((*it));

        }
    }
    Origrecord->clearComments();

    for (vector<struct comment>::iterator it = newComments.begin(); it != newComments.end(); ++it) {
        Origrecord->appendComment((*it));
    }

    //write changes
    Origrecord->writeToDB(conn);
}

fileArchiver::~fileArchiver() {
    //nothing to do
}

