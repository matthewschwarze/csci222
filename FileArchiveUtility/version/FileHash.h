/* 
 * File:   FileHash.h
 * Author: tomch
 *
 * Created on 17 September 2015, 9:42 PM
 */

#ifndef FILEHASH_H
#define	FILEHASH_H

#include <string>

std::string hash_md5(std::string filename);
std::string hash_md5_data(std::string data);

#endif	/* FILEHASH_H */

