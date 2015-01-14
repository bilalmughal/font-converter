/* 
*  Copyright © 2012, Mirza Bilal (bilal@mirzabilal.com) All rights reserved.
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that 
*  the following conditions are met:
*   1.  Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*   2.  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and 
*      the following disclaimer in the documentation and/or other materials provided with the distribution.
*   3.  Neither the name of Mirza Bilal nor the names of its contributors may be used to endorse or promote 
*       products derived from this software without specific prior written permission.
*  THIS SOFTWARE IS PROVIDED BY MIRZA BILAL "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
*  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
*  SHALL MIRZA BILAL BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
*  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
*  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
*  POSSIBILITY OF SUCH DAMAGE.
*/

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
#include "utility/c-helper.h"
#ifdef __cplusplus
}
#endif

class FFTestSuite : public CxxTest::TestSuite
{
    public:

        void test_LoadFont( void )
        {
            TS_TRACE("Starting Test LoadFont");
            void* res = LoadFont("test/data/yoo.ttf");
            TS_ASSERT(res);
        }
        
        void test_isDirectoryExist_invalidpath( void )
        {
            TS_TRACE("Starting Test LoadFont");
            int res = is_directory_exist("this_path_is_invalid");
            TS_ASSERT_EQUALS(res, -1);
        }
        
        void test_isDirectoryExist_validpath( void )
        {
            TS_TRACE("Starting Test LoadFont");
            int res = is_directory_exist("./bin");
            TS_ASSERT_EQUALS(res, 0);
        }
        
        void test_fontConvert_emptyoutname( void )
        {
            TS_TRACE("Starting Test fontConvert_emptyoutname");
            int res = convert_font("test/data/yoo.ttf", "otf", "", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }

        void test_fontConvert_ttf2woff( void )
        {
            TS_TRACE("Starting Test ttf2woff");
            int res = convert_font("test/data/yoo.ttf", "woff", "yoo", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }
        
        void test_fontConvert_ttf2otf( void )
        {
            TS_TRACE("Starting Test ttf2otf");
            int res = convert_font("test/data/yoo.ttf", "otf", "yoo", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }

        void test_fontConvert_ttf2dfont( void )
        {
            TS_TRACE("Starting Test ttf2otf");
            int res = convert_font("test/data/yoo.ttf", "dfont", "yoo", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }

        void test_fontConvert_woff2ttf( void )
        {
            TS_TRACE("Starting Test woff2ttf");
            int res = convert_font("test/data/Oxygen.woff", "ttf", "oxygen", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }
        
        void test_fontConvert_woff2otf( void )
        {
            TS_TRACE("Starting Test woff2ttf");
            int res = convert_font("test/data/Oxygen.woff", "otf", "oxygen", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }
        
        void test_fontConvert_woff2dfont( void )
        {
            TS_TRACE("Starting Test woff2ttf");
            int res = convert_font("test/data/Oxygen.woff", "dfont", "oxygen", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }
        
        void test_fontConvert_otftottf( void )
        {
            TS_TRACE("Starting Test fontConvert_otftottf");
            int res = convert_font("test/data/Prociono-Regular.otf", "ttf" , "Prociono-Regular", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }
        
        void test_fontConvert_otftowoff( void )
        {
            TS_TRACE("Starting Test fontConvert_otftottf");
            int res = convert_font("test/data/Prociono-Regular.otf", "woff" , "Prociono-Regular", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }
        
        void test_fontConvert_otftodfont( void )
        {
            TS_TRACE("Starting Test fontConvert_otftottf");
            int res = convert_font("test/data/Prociono-Regular.otf", "dfont" , "Prociono-Regular", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }
        
        void test_fontConvert_dfont2ttf( void )
        {
            TS_TRACE("Starting Test dfont2ttf");
            int res = convert_font("test/data/Courier.dfont", "ttf", "Courier", "test/result");
            TS_ASSERT_EQUALS( res, 0 );
        }
            
        void test_getTTCFontCount_ttcwith3fonts( void )
        {
            TS_TRACE("Starting Test getFontNameCountFromTTC");
            int res = get_ttc_font_count("test/data/vegur.ttc");
            TS_ASSERT_EQUALS( res, 3 );
        }
        
        void test_getFontNames_ttcfontnames( void )
        {
            TS_TRACE("Starting Test getFontNames_ttcfontname");
            char** font_names = get_font_names("test/data/vegur.ttc");
            TS_ASSERT_SAME_DATA("Vegur",font_names[0], 6);
            for (int i = 0; i < 3; i++) 
                free(font_names[i]);
            free(font_names);
        }
        
        void test_getFontNames_ttcfontnames2( void )
        {
            TS_TRACE("Starting Test getFontNames_ttcfontname");
            char** font_names = get_font_names("test/data/vegur.ttc");
            TS_ASSERT_SAME_DATA("Vegur Bold",font_names[2], 11);
            for (int i = 0; i < 3; i++) 
                free(font_names[i]);
            free(font_names);
        }
};

#endif  //__FF_TEST_H__
