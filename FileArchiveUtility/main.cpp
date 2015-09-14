/* 
 * File:   main.cpp
 * Author: Matthew
 *
 * Created on 9 September 2015, 8:37 PM
 */

#include <iostream>
#include "mongo/client/dbclient.h"

using namespace std;

/*
 * 
 */
void run() {
  mongo::DBClientConnection c;
  c.connect("121.211.198.171:27017");
}

int main() {
    mongo::client::initialize();
    try {
        run();
        std::cout << "connected ok" << std::endl;
    } catch( const mongo::DBException &e ) {
        std::cout << "caught " << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

