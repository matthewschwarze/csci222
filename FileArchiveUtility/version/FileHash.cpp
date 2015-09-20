
#include "FileHash.h"
#include <Qt/qfile.h>
#include <Qt/qbytearray.h>
#include <Qt/qcryptographichash.h>
#include <Qt/qstring.h>
#include <string>
#include <iostream>
using namespace std;

string hash_md5(string filename) {
    /* Connect to file */
    QString qFilename(filename.c_str());
    QFile fInput(qFilename);
    if(fInput.open(QIODevice::ReadOnly))
  {
    /* Construct QByteArray for file data */
    QByteArray fileData = fInput.readAll();
    
    /* Get a QByteArry of the Hash */
    QByteArray qHash = QCryptographicHash::hash(fileData, QCryptographicHash::Md5);
    string retHash = QString(qHash.toHex()).toStdString();
    /* Convert QByteArray to string again*/
    fInput.close();
    return retHash;
    }
    else{
        cout << "ahhh" << endl; //do something like exit
        string a = "ahh";
        return a;
    }
}

string hash_md5_data(string data) {
    
    /* Construct QByteArray for data */
    QByteArray fileData (data.c_str(), data.length());
    
    /* Get a QByteArry of the Hash */
    QByteArray qHash = QCryptographicHash::hash(fileData, QCryptographicHash::Md5);
   
    string retHash = QString(qHash.toHex()).toStdString();
    /* Convert QByteArray to string again*/
    return retHash;
}