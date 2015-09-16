#ifndef _VERSIONREC_H_
#define _VERSIONREC_H_

#include <vector>
#include <time.h>
#include "hash.h"

typedef int HashType;

struct VersionDiffBlock {
	int blockNo;
	HashType blockHash;
	int blockLen;
	char blockArr[BLOCK_SIZE];
};

class VersionRec {
	private:
		int versionid;
		int versionnumber;
		int length;
		timespec modifytime;
		HashType filehash;
		std::vector<VersionDiffBlock> changes;
		
	public:
	
		//---- Constructors / Destructors ----//
		VersionRec();
		
		//---- Accessor Functions ----//
		int getVersionID() const;
		
		int getVersionNumber() const;
		
		int getLength() const;
		
		timespec getModifyTime() const;
		
		HashType getFileHash() const;
		
		std::vector<VersionDiffBlock>::iterator getChangesBegin();
		
		std::vector<VersionDiffBlock>::iterator getChangesEnd();
		
		//---- Mutator Functions ----//
		void setVersionID(int v);
		
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
