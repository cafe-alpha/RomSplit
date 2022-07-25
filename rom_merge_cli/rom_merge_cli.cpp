/* 
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                     Version 2, December 2004
 * 
 *  Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 * 
 *  Everyone is permitted to copy and distribute verbatim or modified
 *  copies of this license document, and changing it is allowed as long
 *  as the name is changed.
 * 
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 * 
 *   0. You just DO WHAT THE FUCK YOU WANT TO. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

////////////////////////////////////////////////////////////////////////
// MAIN
////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    if(argc <= 3)
    {
        printf("Usage %s <even_file> <odd_file> <output_file>.\r\n", argv[0]);
        return 0;
    }

    char* in1_file = argv[1];
    char* in2_file = argv[2];
    char* out_file = argv[3];


    FILE* fp1;
    FILE* fp2;
    FILE* fpo;

    fp1 = fopen(in1_file, "rb");
    if(!fp1)
    {
        printf("Error : input file \"%s\" open failure.\r\n", in1_file);
        return 0;
    }

    fp2 = fopen(in2_file, "rb");
    if(!fp2)
    {
        fclose(fp1); fp1 = NULL;
        printf("Error : input file \"%s\" open failure.\r\n", in2_file);
        return 0;
    }

    fpo = fopen(out_file, "wb");
    if(!fpo)
    {
        fclose(fp1); fp1 = NULL;
        fclose(fp2); fp2 = NULL;
        printf("Error : output file \"%s\" open failure.\r\n", out_file);
        return 0;
    }

    long size1, size2;

    fseek(fp1, 0, SEEK_END);
    size1 = ftell(fp1);
    fseek(fp1, 0, SEEK_SET);

    fseek(fp2, 0, SEEK_END);
    size2 = ftell(fp2);
    fseek(fp2, 0, SEEK_SET);

    long size = size1;
    if(size2 < size)
    {
        size = size2;
    }
    size = size*2;

    unsigned char* buff1;
    unsigned char* buff2;
    unsigned char* buff;

    buff1 = (unsigned char*)malloc(size/2);
    buff2 = (unsigned char*)malloc(size/2);
    buff  = (unsigned char*)malloc(size);

    if((!buff1) || (!buff2) || (!buff))
    {
        fclose(fp1); fp1 = NULL;
        fclose(fp2); fp2 = NULL;
        fclose(fpo); fpo = NULL;
        if(buff1)
        {
            free(buff1);
        }
        if(buff2)
        {
            free(buff2);
        }
        if(buff)
        {
            free(buff);
        }

        printf("Error : memory allocation failure.\r\n");
        return 0;
    }

    fread(buff1, size/2, 1, fp1);
    fread(buff2, size/2, 1, fp2);

    fclose(fp1); fp1 = NULL;
    fclose(fp2); fp2 = NULL;

    for(long i=0; i<(size/2); i++)
    {
        buff[(2*i) + 0] = buff1[i];
        buff[(2*i) + 1] = buff2[i];
    }


    fwrite(buff, size, 1, fpo);
    fclose(fpo); fpo = NULL;

    printf("Wrote %ld bytes to file \"%s\".\r\n", size, out_file);

    return 0;
}

