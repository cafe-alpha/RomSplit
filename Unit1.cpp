//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <string.h>
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


//http://gnuwin32.sourceforge.net/version.c.txt
BOOL GetAppVersion( char *LibName, WORD *MajorVersion, WORD *MinorVersion, WORD *BuildNumber, WORD *RevisionNumber )
{
    DWORD dwHandle, dwLen;
    UINT BufLen;
    LPTSTR lpData;
    VS_FIXEDFILEINFO *pFileInfo;

    dwLen = GetFileVersionInfoSize( LibName, &dwHandle );

    if (!dwLen)
    {
        return FALSE;
    }

    lpData = (LPTSTR) malloc (dwLen);
    if (!lpData)
    {
        return FALSE;
    }

    if( !GetFileVersionInfo( LibName, dwHandle, dwLen, lpData ) )
    {
        free (lpData);
        return FALSE;
    }

    if( VerQueryValue( lpData, "\\", (LPVOID *) &pFileInfo, (PUINT)&BufLen ) )
    {
        *MajorVersion = HIWORD(pFileInfo->dwFileVersionMS);
        *MinorVersion = LOWORD(pFileInfo->dwFileVersionMS);
        *BuildNumber = HIWORD(pFileInfo->dwFileVersionLS);
        *RevisionNumber = LOWORD(pFileInfo->dwFileVersionLS);
        free (lpData);
        return TRUE;
    }

    free (lpData);
    return FALSE;
}


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
    , m_bMergeMode(false)
    , m_lInFileCnt(0)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    WORD ver[4];
    GetAppVersion(Application->ExeName.c_str(), ver+0, ver+1, ver+2, ver+3);
    AnsiString str;
    str.printf("RomSplit ver.%d.%d.%d [Build " __DATE__ ", " __TIME__ "]", ver[0], ver[1], ver[2]);
    Form1->Caption = str;

    /* Enable file drag and drop. */
    DragAcceptFiles(this->Handle, true);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    /* Nothing special here. */
}


//---------------------------------------------------------------------------
void __fastcall TForm1::WmDropFiles(TWMDropFiles DropMsg)
{
    /* Retrieve the count of dragged files. */
    LONG lCount = DragQueryFile((HDROP)DropMsg.Drop, -1, NULL, 0);

    if(lCount >= 1)
    {
        for(LONG lId=0; lId<lCount; lId++)
        {
            /* Retrieve name of dragged file. */
            char pcFileName[MAX_PATH+1] = {'\0'};
            DragQueryFile((HDROP)DropMsg.Drop, lId, pcFileName, MAX_PATH);

            AnsiString strFullPath = AnsiString(pcFileName);

            if(m_lInFileCnt == 0)
            {
                edtFile1->Text = strFullPath;

                /* Check if file need to be splitted or merged. */
                FILE* fp = fopen(strFullPath.c_str(), "rb");
                char pcRomHeader[16] = {'\0'};
                if(fp)
                {
                    fread(pcRomHeader, sizeof(pcRomHeader), 1, fp);
                    fclose(fp);
                }
                if(memcmp(pcRomHeader, "SEGA SEGASATURN ", sizeof(pcRomHeader)) == 0)
                {
                    m_bMergeMode = false;

                    /* In split mode one input file is enough, so
                     * enable the convert button now.
                     */
                    btnConvert->Caption = "SPLIT";
                    btnConvert->Visible = true;

                    /* Set output files name from input one. */
                    char strName[MAX_PATH] = {'\0'};
                    strcpy(strName, strFullPath.c_str());
                    LONG lNameLen = strlen(strName);
                    if(lNameLen > 4)
                    {
                        strName[lNameLen - 4] = '\0';
                        char* strExt = strName + lNameLen - 3;
                        char strOutFile[MAX_PATH] = {'\0'};

                        sprintf(strOutFile, "%s_H.%s", strName, strExt);
                        edtOutFile1->Text = strOutFile;
                        lblOutFile1->Caption = "Output File #1 :";
                        lblOutFile1->Visible = true;
                        edtOutFile1->Visible = true;

                        sprintf(strOutFile, "%s_L.%s", strName, strExt);
                        edtOutFile2->Text = strOutFile;
                        lblOutFile2->Visible = true;
                        edtOutFile2->Visible = true;
                    }
                }
                else
                {
                    m_bMergeMode = true;

                    /* In merge mode one more input file is needed, so
                     * display but not enable the convert button now.
                     */
                    btnConvert->Caption = "MERGE";
                    btnConvert->Visible = true;
                    btnConvert->Enabled = false;
                    lblInFile1->Caption = "Input File #1 :";

                    lblInFile2->Visible = true;
                    edtFile2  ->Visible = true;
                }

                m_lInFileCnt++;
            }

            else if((m_lInFileCnt == 1) && (m_bMergeMode))
            {
                edtFile2->Text = strFullPath;
                btnConvert->Enabled = true;

                lblOutFile1->Visible = true;
                edtOutFile1->Visible = true;

                /* Set output file name from second input one. */
                char strName[MAX_PATH] = {'\0'};
                strcpy(strName, strFullPath.c_str());
                LONG lNameLen = strlen(strName);
                if(lNameLen > 4)
                {
                    strName[lNameLen - 4] = '\0';
                    char* strExt = strName + lNameLen - 3;
                    char strOutFile[MAX_PATH] = {'\0'};

                    sprintf(strOutFile, "%s_MERGE.%s", strName, strExt);
                    edtOutFile1->Text = strOutFile;
                    lblOutFile1->Visible = true;
                    edtOutFile1->Visible = true;
                }
            }
        }
    }

    DragFinish((HDROP)DropMsg.Drop);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnConvertClick(TObject *Sender)
{
#define ROM_SIZE (256*1024)
    UCHAR* pucInBuff = (UCHAR*)malloc(ROM_SIZE*sizeof(UCHAR));
    if(!pucInBuff)
    {
        return;
    }

    UCHAR* pucOutBuff = (UCHAR*)malloc(ROM_SIZE*sizeof(UCHAR));
    if(!pucOutBuff)
    {
        return;
    }

    memset(pucInBuff , 0xFF, ROM_SIZE*sizeof(UCHAR));
    memset(pucOutBuff, 0xFF, ROM_SIZE*sizeof(UCHAR));

    int i;
    FILE* fp;
    if(m_bMergeMode)
    {
        UCHAR* pucIn1Ptr = pucInBuff;
        fp = fopen(edtFile1->Text.c_str(), "rb");
        if(fp)
        {
            fread(pucIn1Ptr, (ROM_SIZE*sizeof(UCHAR))/2, 1, fp);
            fclose(fp);
        }

        UCHAR* pucIn2Ptr = pucInBuff + ((ROM_SIZE*sizeof(UCHAR))/ 2);
        fp = fopen(edtFile2->Text.c_str(), "rb");
        if(fp)
        {
            fread(pucIn2Ptr, (ROM_SIZE*sizeof(UCHAR))/2, 1, fp);
            fclose(fp);
        }

        /* Check which buffer contains the highest bytes. */
        bool bOrder = ((pucIn1Ptr[0] == 'S') && (pucIn1Ptr[1] == 'G') ? true : false);

        /* Merge the two buffers into a single one. */
        for(i=0; i<((ROM_SIZE*sizeof(UCHAR))/2); i++)
        {
            if(bOrder)
            {
                pucOutBuff[(2*i) + 0] = pucIn1Ptr[i];
                pucOutBuff[(2*i) + 1] = pucIn2Ptr[i];
            }
            else
            {
                pucOutBuff[(2*i) + 0] = pucIn2Ptr[i];
                pucOutBuff[(2*i) + 1] = pucIn1Ptr[i];
            }
        }

        /* Spit the output file. */
        fp = fopen(edtOutFile1->Text.c_str(), "wb");
        if(fp)
        {
            fwrite((void*)pucOutBuff, ROM_SIZE*sizeof(UCHAR), 1, fp);
            fclose(fp);
        }
    }
    else
    {
        fp = fopen(edtFile1->Text.c_str(), "rb");
        if(fp)
        {
            fread(pucInBuff, ROM_SIZE*sizeof(UCHAR), 1, fp);
            fclose(fp);
        }

        /* Split the input file contents. */
        UCHAR* pucOut1Ptr = pucOutBuff;
        UCHAR* pucOut2Ptr = pucOutBuff + ((ROM_SIZE*sizeof(UCHAR))/ 2);

        for(i=0; i<((ROM_SIZE*sizeof(UCHAR))/2); i++)
        {
            pucOut1Ptr[i] = pucInBuff[(2*i) + 0];
            pucOut2Ptr[i] = pucInBuff[(2*i) + 1];
        }

        /* Spit the output files. */
        fp = fopen(edtOutFile1->Text.c_str(), "wb");
        if(fp)
        {
            fwrite((void*)pucOut1Ptr, (ROM_SIZE*sizeof(UCHAR))/2, 1, fp);
            fclose(fp);
        }

        fp = fopen(edtOutFile2->Text.c_str(), "wb");
        if(fp)
        {
            fwrite((void*)pucOut2Ptr, (ROM_SIZE*sizeof(UCHAR))/2, 1, fp);
            fclose(fp);
        }
    }


    free(pucInBuff );
    free(pucOutBuff);
}
//---------------------------------------------------------------------------

