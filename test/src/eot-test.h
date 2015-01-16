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
#include "ttf2eot.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "ff-bridge.h"
#ifdef __cplusplus
}
#endif

class Ttf2EotTestSuite : public CxxTest::TestSuite
{
public:
    void test_convert_validttf(void)
    {
        TTF2Eot ttf2Eot;
        int res = ttf2Eot.Convert();

        TS_ASSERT_EQUALS(res, 0);
    }
};

#endif  //__EOT_TEST_H__
