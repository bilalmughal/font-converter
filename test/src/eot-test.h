//  Copyright © 2012, Mirza Bilal (bilal@mirzabilal.com) All rights reserved.
//  Redistribution and use in source and binary forms, with or without modification, are permitted provided that 
//  the following conditions are met:
//   1.  Redistributions of source code must retain the above copyright notice, this list of conditions and the
//       following disclaimer.
//   2.  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and 
//      the following disclaimer in the documentation and/or other materials provided with the distribution.
//   3.  Neither the name of Mirza Bilal nor the names of its contributors may be used to endorse or promote 
//       products derived from this software without specific prior written permission.
//  THIS SOFTWARE IS PROVIDED BY MIRZA BILAL "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
//  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
//  SHALL MIRZA BILAL BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
//  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
//  POSSIBILITY OF SUCH DAMAGE.

// =====================================================================================
// 
//       Filename:  eot-test.h
//
//    Description:  EOT font unit tests
//
//        Version:  1.0
//        Created:  2015-01-09
//
//         Author:  Mirza Bilal, bilal@mirzabilal.com
//
// =====================================================================================

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
    TTF2Eot ttf2Eot;
public:
    void setUp()
    {
    }

    void test_convert_noSrcFile(void)
    {
        int res = ttf2Eot.Convert();
        TS_ASSERT_EQUALS(res, 0);
    }
    
    void test_convert_validTTF()
    {
        ttf2Eot.SrcFile("test/data/yoo.ttf");
        int res = ttf2Eot.Convert();
        TS_ASSERT_EQUALS(res, 0);
    }
};

#endif  //__EOT_TEST_H__

