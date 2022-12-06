object FormLog: TFormLog
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1046#1091#1088#1085#1072#1083' '#1088#1072#1091#1085#1076#1086#1074
  ClientHeight = 384
  ClientWidth = 323
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Comic Sans MS'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 15
  object LogSG: TStringGrid
    Left = 0
    Top = 0
    Width = 318
    Height = 384
    ColCount = 2
    DefaultColWidth = 148
    FixedCols = 0
    RowCount = 2
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goFixedRowDefAlign]
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
  end
end
