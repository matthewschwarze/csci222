/*
 * File:   newtestclass.h
 * Author: tomch
 *
 * Created on 17/09/2015, 7:23:23 PM
 */

#ifndef NEWTESTCLASS_H
#define	NEWTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>
#include "../version/FileRec.h"

class newtestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass);

    CPPUNIT_TEST(testConstruct);
    CPPUNIT_TEST(testReadFile);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass();
    virtual ~newtestclass();
    void setUp();
    void tearDown();

private:
    void testConstruct();
    void testReadFile();
};

#endif	/* NEWTESTCLASS_H */

