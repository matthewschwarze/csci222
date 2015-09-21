#ifndef _FILEREC_H_
#define _FILEREC_H_

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "VersionRec.h"
#include "mongo/client/dbclient.h"
#include "mongo/bson/bson.h"
#include "mongo/client/dbclientcursor.h"
#include "mongo/client/gridfs.h"
#include <boost/filesystem.hpp>


typedef std::string HashType;

class FileRec {
	private:
		std::string filename;
		std::string tempname;
		timespec modifytime;
		int length;
		int versionCount;
		HashType origHash;
		HashType recentHash;
		int refNum;
		std::vector<HashType> blockhashes;
		std::vector<VersionRec> versions;
		std::vector<std::string> comments;
	
	public:
	
		//---- Constructors / Destructors ----//
		FileRec();
		
		//---- Accessor Functions ----//
		std::string getFilename() const;
		
		std::string getBlobName() const;
		
		timespec getModTime() const;
		
		int getBlockCount() const;
		
		int getVersionNum() const;
		
		HashType getHashOriginal() const;
		
		HashType getHashLatest() const;
		
		int getReferenceVersion() const;
		
		std::vector<HashType>::iterator getBlocksBegin();

		std::vector<HashType>::iterator getBlocksEnd();
		
		std::vector<VersionRec>::iterator getVersionBegin();
		
		std::vector<VersionRec>::iterator getVersionEnd();
		
		std::vector<std::string>::iterator getCommentsBegin();
		
		std::vector<std::string>::iterator getCommentsEnd();
		
		//---- Mutator Functions ----//
		void setFilename(const std::string& s);
		
		void setBlobName(const std::string& x);
		
		void setModTime(timespec x);
		
		void setBlockCount(int x);
		
		void setVersionNum(int x);
		
		void setHashOriginal(HashType x);
		
		void setHashLatest(HashType x);
		
		void setReferenceVersion(int x);
				
		void appendBlock(HashType hash);
				
		void appendVersion(VersionRec v);
				
		void appendComment(std::string c);
		
		//---- Reading / Writing Functions ----//
		
		void createData(std::string filename);
		
		void readFromDB(mongo::DBClientConnection&, std::string filename);
		
		void writeToDB(mongo::DBClientConnection&);
		
		//-- Overloaded Operators --//
		bool operator==(const FileRec& other);
		
		bool operator!=(const FileRec& other);
	
};

#endif
