#include <fstream>
#include <stdexcept>
#include <exception>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "FileRec.h"
using namespace std;

FileRec::FileRec():
	length(0),
	versionCount(0),
	origHash(0),
	recentHash(0),
	refNum(0)
{
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

vector<int>::iterator FileRec::getBlocksBegin() {
	return blockhashes.begin();
}

vector<int>::iterator FileRec::getBlocksEnd() {
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

void FileRec::appendBlocks(int hash) {
	blockhashes.push_back(hash);
}

void FileRec::appendVersionIDs(int v) {
	versions.push_back(v);
}

void FileRec::appendComments(string c) {
	comments.push_back(c);
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
	//setHashLatest();
	
	
}

bool FileRec::operator==(const FileRec& other) {
	return (filename == other.filename) && (recentHash == other.recentHash);
}

bool FileRec::operator!=(const FileRec& other) {
	return (filename != other.filename) || (recentHash != other.recentHash);
}
