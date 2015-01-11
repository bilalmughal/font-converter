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
		void testAddition( void )
		{
			//TS_ASSERT( 1 + 1 > 1 );
			//TS_ASSERT_EQUALS( 1 + 1, 2 );
		  int res = convert_font("test.ttf", "woff", "result");
			//TS_ASSERT( 1 + 1 > 1 );
			TS_ASSERT_EQUALS( res, 0 );
		}
		void convertfont_ttftowoff_equalszero( void )
		{
		  int res = convert_font("test.ttf", "woff", "result");
			//TS_ASSERT( 1 + 1 > 1 );
			TS_ASSERT_EQUALS( res, 0 );
		}
};
#endif
