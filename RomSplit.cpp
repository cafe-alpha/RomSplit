//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("RomSplit.res");
USEFORM("Unit1.cpp", Form1);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    HANDLE hMutex;
    try
    {
        /* Prevent from executing multiple instances of this program. */
        const char strMutex[] = "SaturnSaveRepack";
        hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, strMutex);
        if(!hMutex)
        {
            CreateMutex(NULL, true, strMutex);
        }
        else
        {
            CloseHandle(hMutex);
            return 0;
        }
        Application->Initialize();
        Application->Title = "RomSplit";
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    CloseHandle(hMutex);
    return 0;
}
//---------------------------------------------------------------------------
