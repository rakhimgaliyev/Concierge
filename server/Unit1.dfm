object Form1: TForm1
  Left = 0
  Top = 0
  ActiveControl = Memo1
  Caption = 'Form1'
  ClientHeight = 418
  ClientWidth = 409
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 8
    Top = 9
    Width = 393
    Height = 401
    Lines.Strings = (
      'Memo1')
    TabOrder = 0
  end
  object ServerSocket1: TServerSocket
    Active = False
    Port = 0
    ServerType = stNonBlocking
    OnClientConnect = ClientConnectEvent
    OnClientDisconnect = ServerSocket1ClientDisconnect
    OnClientRead = ClientSentMessage
    Left = 192
    Top = 192
  end
  object TrayIcon1: TTrayIcon
    OnClick = TrayIcon1Click
    Left = 216
    Top = 264
  end
end
