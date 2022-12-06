object FormGameMode: TFormGameMode
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Domino. '#1042#1099#1073#1086#1088' '#1088#1072#1079#1085#1086#1074#1080#1076#1085#1086#1089#1090#1080' '#1080#1075#1088#1099
  ClientHeight = 261
  ClientWidth = 267
  Color = clActiveBorder
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PointsLabel: TLabel
    Left = 8
    Top = 120
    Width = 218
    Height = 33
    Alignment = taCenter
    Caption = ' '#1054#1095#1082#1080' '#1076#1083#1103' '#1087#1086#1073#1077#1076#1099':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
  end
  object SpinEdit: TSpinEdit
    Left = 8
    Top = 159
    Width = 241
    Height = 33
    EditorEnabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    Increment = 10
    MaxValue = 250
    MinValue = 50
    ParentFont = False
    TabOrder = 2
    Value = 100
  end
  object RadioGroup: TRadioGroup
    Left = 8
    Top = 8
    Width = 241
    Height = 105
    Caption = #1056#1072#1079#1085#1086#1074#1080#1076#1085#1086#1089#1090#1100' '#1080#1075#1088#1099':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      #1050#1083#1072#1089#1089#1080#1082#1072
      #1050#1086#1079#1105#1083)
    ParentFont = False
    TabOrder = 1
  end
  object PlayButton: TButton
    Left = 8
    Top = 202
    Width = 241
    Height = 51
    Caption = #1048#1075#1088#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = PlayButtonClick
  end
end
