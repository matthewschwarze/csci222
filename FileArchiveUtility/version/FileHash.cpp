
#include "FileHash.h"
#include <Qt/qfile.h>
#include <Qt/qbytearray.h>
#include <Qt/qcryptographichash.h>
#include <Qt/qstring.h>
#include <string>
using namespace std;

string hash_md5(string filename) {
    /* Connect to file */
    QString qFilename(filename.c_str());
    QFile fInput(qFilename);
    
    /* Construct QByteArray for file data */
    QByteArray fileData = fInput.readAll();
    
    /* Get a QByteArry of the Hash */
    QByteArray qHash = QCryptographicHash::hash(fileData, QCryptographicHash::Md5);
    
    /* Convert QByteArray to string again*/
    string retHash(qHash);
    return retHash;
}

string hash_md5_data(string data) {
    /* Connect to file */
    QString qFilename(filename.c_str());
    QFile fInput(qFilename);
    
    /* Construct QByteArray for file data */
    QByteArray fileData = fInput.readAll();
    
    /* Get a QByteArry of the Hash */
    QByteArray qHash = QCryptographicHash::hash(fileData, QCryptographicHash::Md5);
    
    /* Convert QByteArray to string again*/
    string retHash(qHash);
    return retHash;
}