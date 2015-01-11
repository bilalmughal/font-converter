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
#ifndef __FF_TEST_H__
#define __FF_TEST_H__

#include <cxxtest/TestSuite.h>


#ifdef __cplusplus
extern "C" {
#endif
#include "ff-bridge.h"
#ifdef __cplusplus
}
#endif

class FFTestSuite : public CxxTest::TestSuite
{
    public:

        void test_LoadFont( void )
        {
            void* res = LoadFont("test/data/yoo.ttf");
            TS_ASSERT(res);
        }

        void test_fontConvert_ttf2woff( void )
        {
            int res = convert_font("test/data/yoo.ttf", "woff", "bin/result");
            TS_ASSERT_EQUALS( res, 0 );
        }

        void test_fontConvert_woff2ttf( void )
        {
            int res = convert_font("test/data/yoo.woff", "ttf", "bin/result");
            TS_ASSERT_EQUALS( res, 0 );
        }
};

#endif  //__FF_TEST_H__
