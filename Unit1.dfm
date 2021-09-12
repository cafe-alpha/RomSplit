object Form1: TForm1
  Left = 250
  Top = 174
  BorderStyle = bsDialog
  Caption = '<Title defined in FormCreate>'
  ClientHeight = 265
  ClientWidth = 513
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '‚l‚r ‚oƒSƒVƒbƒN'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 12
  object Label1: TLabel
    Left = 112
    Top = 8
    Width = 257
    Height = 12
    Caption = '--- Sega Saturn ROM files split/merge utility ---'
  end
  object Label2: TLabel
    Left = 16
    Top = 24
    Width = 73
    Height = 12
    Caption = 'How it works :'
  end
  object Label3: TLabel
    Left = 16
    Top = 40
    Width = 162
    Height = 12
    Caption = '  1. Drag'#39'n Drop files to convert'
  end
  object Label4: TLabel
    Left = 16
    Top = 56
    Width = 125
    Height = 12
    Caption = '  2. Push Convert button'
  end
  object lblInFile1: TLabel
    Left = 12
    Top = 108
    Width = 54
    Height = 12
    Caption = 'Input File :'
  end
  object lblInFile2: TLabel
    Left = 12
    Top = 126
    Width = 70
    Height = 12
    Caption = 'Input File #2 :'
    Visible = False
  end
  object Label5: TLabel
    Left = 264
    Top = 24
    Width = 62
    Height = 12
    Caption = 'Limitations :'
  end
  object Label6: TLabel
    Left = 264
    Top = 40
    Width = 208
    Height = 12
    Caption = '  1. Supports only Saturn boot ROM files'
  end
  object Label7: TLabel
    Left = 264
    Top = 56
    Width = 159
    Height = 12
    Caption = '  2. Total size limited to 256KB'
  end
  object Label8: TLabel
    Left = 16
    Top = 72
    Width = 455
    Height = 12
    Caption = 
      'As header is used to reconstruct the ROM, input order of files t' +
      'o merge is not important.'
  end
  object lblOutFile1: TLabel
    Left = 12
    Top = 220
    Width = 63
    Height = 12
    Caption = 'Output File :'
    Visible = False
  end
  object lblOutFile2: TLabel
    Left = 12
    Top = 238
    Width = 79
    Height = 12
    Caption = 'Output File #2 :'
    Visible = False
  end
  object edtFile1: TEdit
    Left = 88
    Top = 104
    Width = 412
    Height = 20
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 0
  end
  object btnConvert: TButton
    Left = 200
    Top = 152
    Width = 97
    Height = 49
    Caption = 'Convert'
    TabOrder = 1
    Visible = False
    OnClick = btnConvertClick
  end
  object edtFile2: TEdit
    Left = 88
    Top = 122
    Width = 412
    Height = 20
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 2
    Visible = False
  end
  object edtOutFile1: TEdit
    Left = 104
    Top = 216
    Width = 396
    Height = 20
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 3
    Visible = False
  end
  object edtOutFile2: TEdit
    Left = 104
    Top = 234
    Width = 396
    Height = 20
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 4
    Visible = False
  end
end
