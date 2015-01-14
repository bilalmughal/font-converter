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
#include <string.h>
#include <stdio.h>
#include "ff-bridge.h"

void* LoadFont(const char* src_file)
{
    SplineFont* font = NULL;
    doinitFontForgeMain();
    font = LoadSplineFont(src_file,1);
    return font;
}

char** get_font_names(const char* src_file)
{
    char* src_file_copy = strdup(src_file);
    char** font_names = GetFontNames(src_file_copy);
    free(src_file_copy);
    return font_names;
}

int get_ttc_font_count(const char* src_file)
{
    FILE* ttc_file = fopen(src_file, "rb");
    int fonts_tag, i;
    int count=0;

    if ( ttc_file == NULL ) 
    {
        fprintf( stderr, "Unable to open %s\n", src_file );
        return count;
    }

    fonts_tag = getlong(ttc_file);
    if ( fonts_tag != CHR('t','t','c','f') ) 
    {
        fprintf( stderr, "%s is not a valid TTC file.\n", src_file );
        fclose(ttc_file);
        return count;
    }

    fonts_tag = getlong(ttc_file);
    if ( fonts_tag != 0x10000 && fonts_tag != 0x20000 )
        fprintf( stderr, "Unexpected ttc version number: %08x\n", fonts_tag );
    count = getlong(ttc_file);
    count = (count < 1) ? 1 : count;
    
    fclose(ttc_file);
    return count;
}

int convert_font(const char* src_file, const char* output_format, const char* output_file, const char* out_dir)
{
    SplineFont* font = NULL;
    font = (SplineFont*)LoadFont(src_file);
    char out_file[255];
    char output_dir[255];
    sprintf(output_dir, "%s", (out_dir == NULL || strlen(out_dir) > 0) ? out_dir : ".");
    
    if (output_file == NULL || strlen(output_file) == 0)
    {
        if (strlen(font->fontname) > 0)
            sprintf(out_file, "%s/%s.%s", output_dir, font->fontname, output_format);
        else
            sprintf(out_file, "%s/font-%x.%s", output_dir, rand() % 1000, output_format);
    }
    else
    {
        sprintf(out_file, "%s/%s.%s", out_dir, output_file, output_format);
    }
    
    printf("\nSource File: %s\n", src_file);
    printf("Output Format: %s\n", output_format);
    printf("Output File: %s\n", output_file);

    printf ("Output file path: %s\n",out_file);

    if(font != NULL)
    {
        int ret = GenerateScript(font, out_file, NULL, 0, -1, NULL, NULL, font->map, NULL, 1);
        if(ret)
            return 0;
    }
    return -1;
}

