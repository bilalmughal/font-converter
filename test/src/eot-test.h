/*
 * =====================================================================================
 *
 *       Filename:  ff_test.h
 *
 *    Description:  Fontforge client unit tests
 *
 *        Version:  1.0
 *        Created:  01/09/2015 12:28:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mirza Bilal, bilal@mirzabilal.com 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __EOT_TEST_H__
#define __EOT_TEST_H__

#include <cxxtest/TestSuite.h>


#ifdef __cplusplus
extern "C" {
#endif
#include "ff-bridge.h"
#ifdef __cplusplus
}
#endif

class MyTestSuite2 : public CxxTest::TestSuite
{
public:
    void testAddition(void)
    {
        TS_ASSERT(1 + 1 > 1);
        TS_ASSERT_EQUALS(1 + 1, 2);
    }
};

#endif  //__EOT_TEST_H__
