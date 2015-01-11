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
//       Filename:  font-converter.cpp
//
//    Description:  font-conversion utility
//
//        Version:  1.0
//        Created:  2015-01-09
//
//         Author:  Mirza Bilal, bilal@mirzabilal.com
//
// =====================================================================================

#include <iostream>
#include <fstream>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

using namespace std;
int main()
{
    cout<<"Hello CMake and CXXTest"<<endl;
    std::vector<char> v;
    if (FILE *file = fopen("main.cpp", "r")) {
        char buf[1024];
        while (size_t len = fread(buf, 1, sizeof(buf), file))
            v.insert(v.end(), buf, buf + len);
        fclose(file);
        std::cout << v.size()<< endl;
        for (std::vector<char>::const_iterator i = v.begin(); i != v.end(); ++i) {
            std::cout << *i << endl;
        }

    }

    return 0;
}

