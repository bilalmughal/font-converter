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
*       Filename:  c-helper.c
*
*    Description:  Helper Functions
*
*        Version:  1.0
*        Created:  2015-01-14
*
*         Author:  Mirza Bilal, bilal@mirzabilal.com
*
* =====================================================================================
*/

#include <stdio.h>
#include "c-helper.h"

int is_directory_exist(const char* dir_path)
{
    struct stat info;

    if( stat( dir_path, &info ) != 0 )
        printf( "cannot access %s\n", dir_path );
    else if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows
    {
        printf( "%s is a directory\n", dir_path );
        return 0;
    }
    else
        printf( "%s is no directory\n", dir_path );
    return -1;
}

