object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 300
  ClientWidth = 594
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 319
    Top = 107
    Width = 21
    Height = 13
    Caption = 'VID:'
  end
  object Label2: TLabel
    Left = 319
    Top = 134
    Width = 21
    Height = 13
    Caption = 'PID:'
  end
  object Label3: TLabel
    Left = 319
    Top = 161
    Width = 24
    Height = 13
    Caption = 'Slug:'
  end
  object Memo1: TMemo
    Left = 8
    Top = 8
    Width = 305
    Height = 281
    Lines.Strings = (
      'Memo1')
    TabOrder = 0
  end
  object Button1: TButton
    Left = 319
    Top = 8
    Width = 89
    Height = 25
    Caption = 'Connect'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 319
    Top = 39
    Width = 89
    Height = 25
    Caption = 'Connected devs'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 356
    Top = 104
    Width = 121
    Height = 21
    TabOrder = 3
  end
  object Edit2: TEdit
    Left = 356
    Top = 131
    Width = 121
    Height = 21
    TabOrder = 4
  end
  object Button3: TButton
    Left = 319
    Top = 70
    Width = 89
    Height = 25
    Caption = 'Registered devs'
    TabOrder = 5
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 497
    Top = 102
    Width = 89
    Height = 25
    Caption = 'Add to DB'
    TabOrder = 6
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 497
    Top = 133
    Width = 89
    Height = 25
    Caption = 'Delete from DB'
    TabOrder = 7
    OnClick = Button5Click
  end
  object Edit3: TEdit
    Left = 356
    Top = 158
    Width = 121
    Height = 21
    TabOrder = 8
  end
  object ClientSocket1: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = ClientSocket1Connect
    OnRead = ClientSocket1Read
    Left = 344
    Top = 232
  end
end
