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
*       Filename:  ff-bridge.c
*
*    Description:  Fontforge bridge Source file
*
*        Version:  1.0
*        Created:  2015-01-12
*
*         Author:  Mirza Bilal, bilal@mirzabilal.com
*
* =====================================================================================
*/
#include <fontforge/fontforge.h>
#include "ff-bridge.h"

void* LoadFont(const char* src_file)
{
    SplineFont* font = NULL;
    doinitFontForgeMain();
    font = LoadSplineFont(src_file,1);
    return font;
}

int convert_font(const char* src_file, const char* output_format, const char* output_file)
{
    SplineFont* font = NULL;
    char out_file[255];
    printf("\nSource File: %s\n", src_file);
    printf("Output Format: %s\n", output_format);
    printf("Output File: %s\n", output_file);

    sprintf(out_file, "%s.%s", output_file, output_format);
    printf ("Output file path: %s\n",out_file);

    font = (SplineFont*)LoadFont(src_file);

    if(font != NULL)
    {
        int ret = GenerateScript(font, out_file, NULL, 0, -1, NULL, NULL, font->map, NULL, 1);
        if(ret)
            return 0;
    }
    return -1;
}

