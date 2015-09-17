/*
 * File:   newtestclass.cpp
 * Author: tomch
 *
 * Created on 17/09/2015, 7:23:24 PM
 */

#include "filerectestclass.h"
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testConstruct() {
    FileRec testRec;
    
    string strFilename("test");
    testRec.setFilename(strFilename);
    CPPUNIT_ASSERT(strFilename == testRec.getFilename());
    
    string strBlobname("tester");
    testRec.setBlobName(strBlobname);
    CPPUNIT_ASSERT(strBlobname == testRec.getBlobName());
    
    timespec timeChange = { 100, 0 };
    testRec.setModTime(timeChange);
    CPPUNIT_ASSERT(timeChange.tv_sec == testRec.getModTime().tv_sec);
    
    int iBlockCount = 6;
    testRec.setBlockCount(iBlockCount);
    CPPUNIT_ASSERT(iBlockCount == testRec.getBlockCount());
    
    int iVersionNum = 1;
    testRec.setVersionNum(iVersionNum);
    CPPUNIT_ASSERT(iVersionNum == testRec.getVersionNum());
    
    HashType hashFile("1234");
    testRec.setHashOriginal(hashFile);
    CPPUNIT_ASSERT(hashFile == testRec.getHashOriginal());
    
    HashType hashRecent("4321");
    testRec.setHashLatest(hashRecent);
    CPPUNIT_ASSERT(hashRecent == testRec.getHashLatest());
    
    int iRefVersion = 1;
    testRec.setReferenceVersion(iRefVersion);
    CPPUNIT_ASSERT(iRefVersion == testRec.getReferenceVersion());
    
    HashType hashBlockH("2341");
    testRec.appendBlock(hashBlockH);
    CPPUNIT_ASSERT(hashBlockH == (*(testRec.getBlocksBegin())));
    
    int iVersionID = 40;
    testRec.appendVersionID(iVersionID);
    CPPUNIT_ASSERT(iVersionID == (*(testRec.getVersionIDsBegin())));
    
    string strComment("I like this");
    testRec.appendComment(strComment);
    CPPUNIT_ASSERT(strComment == (*(testRec.getCommentsBegin())));
}

void newtestclass::testReadFile() {
    
    FileRec testRec;
    string testFile("test.txt");
    struct stat filest;
    
    /* Get the stats from the file*/
    stat(testFile.c_str(), &filest);
    
    /* Read in file into record*/
    testRec.createData(testFile);
    
    CPPUNIT_ASSERT(testRec.getFilename() == testFile);
    CPPUNIT_ASSERT(testRec.getModTime().tv_sec == filest.st_mtime);
    /* Want to test the hashing at some point*/
}


