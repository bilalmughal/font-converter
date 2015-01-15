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
    {
        fprintf( stderr, "Unexpected ttc version number: %08x\n", fonts_tag );
        return count;
    }

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

int get_dfont_font_count(const char* src_file)
{
    FILE* f = fopen(src_file, "rb");
    SplineFont* sf = NULL;
    int flags = 0;
    long offset = 0;

    unsigned char buffer[16], buffer2[16];
    long rdata_pos, map_pos, type_list, name_list, rpos;
    int32 rdata_len;
    uint32 nfnt_pos, font_pos, fond_pos;
    unsigned long tag;
    int i, cnt, subcnt;
    int nfnt_subcnt=0, font_subcnt=0, fond_subcnt=0;

    fseek(f,offset,SEEK_SET);
    if ( fread(buffer,1,16,f)!=16 )
    {
        fclose(f);
        return 0;
    }
    rdata_pos = offset + ((buffer[0]<<24)|(buffer[1]<<16)|(buffer[2]<<8)|buffer[3]);
    map_pos = offset + ((buffer[4]<<24)|(buffer[5]<<16)|(buffer[6]<<8)|buffer[7]);
    rdata_len = ((buffer[8]<<24)|(buffer[9]<<16)|(buffer[10]<<8)|buffer[11]);
    /* map_len = ((buffer[12]<<24)|(buffer[13]<<16)|(buffer[14]<<8)|buffer[15]); */
    if ( rdata_pos+rdata_len!=map_pos || rdata_len==0 )
    {
        fclose(f);
        return 0;
    }
    fseek(f,map_pos,SEEK_SET);
    buffer2[15] = buffer[15]+1; /* make it be different */
    if ( fread(buffer2,1,16,f)!=16 )
    {
        fclose(f);
        return 0;
    }

    /* Apple's data fork resources appear to have a bunch of zeroes here instead */
    /*  of a copy of the first 16 bytes */
    for ( i=0; i<16; ++i )
    {
        if ( buffer2[i]!=0 )
            break;
    }
    if ( i != 16 ) 
    {
        for ( i=0; i<16; ++i )
        {
            if ( buffer[i]!=buffer2[i] )
            {
                fclose(f);
                return 0;
            }
        }
    }
    
    getlong(f);     /* skip the handle to the next resource map */
    getushort(f);   /* skip the file resource number */
    getushort(f);   /* skip the attributes */
    type_list = map_pos + getushort(f);
    name_list = map_pos + getushort(f);

    fseek(f,type_list,SEEK_SET);
    cnt = getushort(f)+1;
    for ( i=0; i<cnt; ++i ) {
        tag = getlong(f);
        /* printf( "%c%c%c%c\n", tag>>24, (tag>>16)&0xff, (tag>>8)&0xff, tag&0xff );*/
        subcnt = getushort(f)+1;
        rpos = type_list+getushort(f);
        sf = NULL;
        if ( tag==CHR('P','O','S','T') && !(flags&(ttf_onlystrikes|ttf_onlykerns)))     /* No FOND */
        {
            //return subcnt;
            //sf = SearchPostScriptResources(f,rpos,subcnt,rdata_pos,flags);
        }
        else if ( tag==CHR('s','f','n','t') && !(flags&ttf_onlykerns))
        {
            //ttf font count
            fclose(f);
            return subcnt;
            //sf = SearchTtfResources(f,rpos,subcnt,rdata_pos,name_list,filename,flags,openflags);
        }
        else if ( tag==CHR('N','F','N','T') ) 
        {
            //NFNT Font for bdf font count
            nfnt_pos = rpos;
            nfnt_subcnt = subcnt;
        } 
        else if ( tag==CHR('F','O','N','T') ) 
        {
            font_pos = rpos;
            font_subcnt = subcnt;
        } 
        else if ( tag==CHR('F','O','N','D') ) 
        {
            fond_pos = rpos;
            fond_subcnt = subcnt;
        }
    }
    fclose(f);
    return -1;
}

