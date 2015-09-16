/* 
 * File:   dbtest.h
 * Author: matthew
 *
 * Created on 16 September 2015, 12:18 PM
 */

#ifndef DBTEST_H
#define	DBTEST_H

#include "mongo/client/dbclient.h"
#include "mongo/bson/bson.h"

class dbtest {

private:
    mongo::DBClientConnection conn;
    
    
public:
    dbtest();
    dbtest(const dbtest& orig);
    bool doSelect();
    bool doInsert();
    bool doUpdate();
    
    virtual ~dbtest();

};

#endif	/* DBTEST_H */

