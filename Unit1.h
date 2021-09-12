//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <stdio.h>

#include <Classes.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <Controls.hpp>
#include <Menus.hpp>

//---------------------------------------------------------------------------



class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *edtFile1;
        TLabel *lblInFile1;
        TButton *btnConvert;
        TEdit *edtFile2;
        TLabel *lblInFile2;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *lblOutFile1;
        TEdit *edtOutFile1;
        TLabel *lblOutFile2;
        TEdit *edtOutFile2;
        void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btnConvertClick(TObject *Sender);
private:	// User declarations
    void __fastcall WmDropFiles(TWMDropFiles DropMsg);

public:		// User declarations
    __fastcall TForm1(TComponent* Owner);

    LONG m_lInFileCnt;
    bool m_bMergeMode;

BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles, WmDropFiles)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
