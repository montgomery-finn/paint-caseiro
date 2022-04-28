object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 808
  ClientWidth = 913
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PrintScale = poNone
  PixelsPerInch = 96
  TextHeight = 13
  object lbMundo: TLabel
    Left = 467
    Top = 524
    Width = 40
    Height = 13
    Caption = 'lbMundo'
  end
  object lbVp: TLabel
    Left = 24
    Top = 528
    Width = 20
    Height = 13
    Caption = 'lbVp'
  end
  object GroupBox2: TGroupBox
    Left = 535
    Top = 17
    Width = 363
    Height = 344
    Caption = 'Poligonos'
    TabOrder = 1
    object Label1: TLabel
      Left = 3
      Top = 19
      Width = 45
      Height = 13
      Caption = 'Poligonos'
    end
    object Label2: TLabel
      Left = 87
      Top = 19
      Width = 33
      Height = 13
      Caption = 'Pontos'
    end
    object Button1: TButton
      Left = 3
      Top = 179
      Width = 122
      Height = 25
      Caption = 'Incluir poligono'
      TabOrder = 0
      OnClick = Button1Click
    end
    object lbPoligonos: TListBox
      Left = 6
      Top = 38
      Width = 75
      Height = 135
      ItemHeight = 13
      TabOrder = 1
      OnClick = lbPoligonosClick
    end
    object lbPontos: TListBox
      Left = 87
      Top = 38
      Width = 273
      Height = 135
      ItemHeight = 13
      TabOrder = 2
    end
    object GroupBox7: TGroupBox
      Left = 135
      Top = 179
      Width = 225
      Height = 162
      Caption = 'Circunfer'#234'ncia'
      TabOrder = 3
      object Label11: TLabel
        Left = 3
        Top = 43
        Width = 68
        Height = 13
        Caption = 'Ponto central:'
      end
      object Label12: TLabel
        Left = 90
        Top = 16
        Width = 6
        Height = 13
        Caption = 'X'
      end
      object Label14: TLabel
        Left = 46
        Top = 93
        Width = 25
        Height = 13
        Caption = 'Raio:'
      end
      object Label13: TLabel
        Left = 142
        Top = 16
        Width = 6
        Height = 13
        Caption = 'Y'
      end
      object edPontoCentralX: TEdit
        Left = 77
        Top = 35
        Width = 59
        Height = 21
        TabOrder = 0
        Text = '0'
      end
      object edPontoCentralY: TEdit
        Left = 142
        Top = 35
        Width = 59
        Height = 21
        TabOrder = 1
        Text = '0'
      end
      object Button6: TButton
        Left = 77
        Top = 62
        Width = 124
        Height = 25
        Caption = 'Selecionar ponto central'
        TabOrder = 2
        OnClick = Button6Click
      end
      object edRaio: TEdit
        Left = 80
        Top = 93
        Width = 121
        Height = 21
        TabOrder = 3
        Text = '30'
      end
      object Button7: TButton
        Left = 80
        Top = 120
        Width = 121
        Height = 25
        Caption = 'Inserir circunfer'#234'ncia'
        TabOrder = 4
        OnClick = Button7Click
      end
    end
    object rgTipoReta: TRadioGroup
      Left = 3
      Top = 241
      Width = 126
      Height = 100
      Caption = 'Tipo reta'
      ItemIndex = 0
      Items.Strings = (
        'LineTo'
        'DDA'
        'Bresenham')
      TabOrder = 4
      OnClick = rgTipoRetaClick
    end
    object Button3: TButton
      Left = 3
      Top = 210
      Width = 122
      Height = 25
      Caption = 'Importar Poligono 3D'
      TabOrder = 5
      OnClick = Button3Click
    end
  end
  object Panel1: TPanel
    Left = 16
    Top = 16
    Width = 502
    Height = 502
    TabOrder = 0
    object Image1: TImage
      Left = 1
      Top = 1
      Width = 500
      Height = 500
      Align = alClient
      OnMouseDown = Image1MouseDown
      OnMouseMove = Image1MouseMove
      ExplicitLeft = 8
      ExplicitTop = 15
    end
  end
  object GroupBox5: TGroupBox
    Left = 17
    Top = 565
    Width = 512
    Height = 236
    Caption = 'Mundo'
    TabOrder = 2
    object GroupBox4: TGroupBox
      Left = 294
      Top = 153
      Width = 185
      Height = 70
      Caption = 'Zoom'
      TabOrder = 0
      object Label5: TLabel
        Left = 47
        Top = 7
        Width = 26
        Height = 13
        Caption = 'Fator'
      end
      object Button4: TButton
        Left = 3
        Top = 26
        Width = 38
        Height = 25
        Caption = '+'
        TabOrder = 0
        OnClick = Button4Click
      end
      object edFatorZoom: TEdit
        Left = 47
        Top = 26
        Width = 50
        Height = 21
        TabOrder = 1
        Text = '2'
      end
      object Button5: TButton
        Left = 103
        Top = 26
        Width = 38
        Height = 25
        Caption = '-'
        TabOrder = 2
        OnClick = Button5Click
      end
    end
    object GroupBox1: TGroupBox
      Left = 3
      Top = 13
      Width = 257
      Height = 212
      Caption = 'Altera'#231#227'o manual'
      TabOrder = 1
      object Label3: TLabel
        Left = 20
        Top = 25
        Width = 22
        Height = 13
        Caption = 'XMin'
      end
      object Label4: TLabel
        Left = 135
        Top = 25
        Width = 26
        Height = 13
        Caption = 'XMax'
      end
      object Label6: TLabel
        Left = 135
        Top = 71
        Width = 26
        Height = 13
        Caption = 'YMax'
      end
      object Label7: TLabel
        Left = 20
        Top = 71
        Width = 22
        Height = 13
        Caption = 'YMin'
      end
      object Button2: TButton
        Left = 19
        Top = 117
        Width = 213
        Height = 25
        Caption = 'Alterar mundo'
        TabOrder = 0
        OnClick = Button2Click
      end
      object edXmin: TEdit
        Left = 20
        Top = 44
        Width = 109
        Height = 21
        TabOrder = 1
        Text = '-250'
      end
      object edXmax: TEdit
        Left = 135
        Top = 44
        Width = 98
        Height = 21
        TabOrder = 2
        Text = '250'
      end
      object edYmin: TEdit
        Left = 20
        Top = 90
        Width = 109
        Height = 21
        TabOrder = 3
        Text = '-250'
      end
      object edYmax: TEdit
        Left = 135
        Top = 90
        Width = 96
        Height = 21
        TabOrder = 4
        Text = '250'
      end
    end
    object GroupBox3: TGroupBox
      Left = 266
      Top = 17
      Width = 246
      Height = 130
      Caption = 'Navega'#231#227'o'
      TabOrder = 2
      object Label8: TLabel
        Left = 81
        Top = 44
        Width = 28
        Height = 13
        Caption = 'Passo'
      end
      object btnCima: TButton
        Left = 80
        Top = 16
        Width = 75
        Height = 25
        Caption = 'Cima'
        TabOrder = 0
        OnClick = btnCimaClick
      end
      object btnEsquerda: TButton
        Left = 0
        Top = 47
        Width = 75
        Height = 25
        Caption = 'Esquerda'
        TabOrder = 1
        OnClick = btnEsquerdaClick
      end
      object btnDireita: TButton
        Left = 153
        Top = 47
        Width = 75
        Height = 25
        Caption = 'Direita'
        TabOrder = 2
        OnClick = btnDireitaClick
      end
      object btnBaixo: TButton
        Left = 80
        Top = 90
        Width = 75
        Height = 25
        Caption = 'Baixo'
        TabOrder = 3
        OnClick = btnBaixoClick
      end
      object edPassoNavegacao: TEdit
        Left = 81
        Top = 63
        Width = 50
        Height = 21
        TabOrder = 4
        Text = '100'
      end
    end
  end
  object GroupBox10: TGroupBox
    Left = 535
    Top = 364
    Width = 370
    Height = 381
    Caption = 'Transforma'#231#245'es'
    TabOrder = 3
    object rdTipoTransformacao: TRadioGroup
      Left = 3
      Top = 24
      Width = 177
      Height = 65
      Caption = 'Tipo tranforma'#231#227'o'
      ItemIndex = 0
      Items.Strings = (
        'Simples'
        'Homogenea')
      TabOrder = 0
    end
    object GroupBox6: TGroupBox
      Left = 3
      Top = 95
      Width = 177
      Height = 138
      Caption = 'Transla'#231#227'o'
      TabOrder = 1
      object Label9: TLabel
        Left = 13
        Top = 24
        Width = 13
        Height = 13
        Caption = 'DX'
      end
      object Label10: TLabel
        Left = 13
        Top = 48
        Width = 13
        Height = 13
        Caption = 'DY'
      end
      object Label19: TLabel
        Left = 13
        Top = 75
        Width = 13
        Height = 13
        Caption = 'DZ'
      end
      object edDx: TEdit
        Left = 32
        Top = 21
        Width = 115
        Height = 21
        TabOrder = 0
        Text = '100'
      end
      object edDy: TEdit
        Left = 32
        Top = 48
        Width = 115
        Height = 21
        TabOrder = 1
        Text = '0'
      end
      object btnTransladar: TButton
        Left = 32
        Top = 102
        Width = 115
        Height = 25
        Caption = 'Transladar'
        TabOrder = 2
        OnClick = btnTransladarClick
      end
      object edDz: TEdit
        Left = 32
        Top = 75
        Width = 113
        Height = 21
        TabOrder = 3
        Text = '0'
      end
    end
    object GroupBox8: TGroupBox
      Left = 186
      Top = 24
      Width = 177
      Height = 137
      Caption = 'Escalonamento'
      TabOrder = 2
      object Label15: TLabel
        Left = 11
        Top = 24
        Width = 12
        Height = 13
        Caption = 'SX'
      end
      object Label16: TLabel
        Left = 11
        Top = 51
        Width = 12
        Height = 13
        Caption = 'SY'
      end
      object Label18: TLabel
        Left = 11
        Top = 78
        Width = 12
        Height = 13
        Caption = 'SZ'
      end
      object edEscalonamentoSx: TEdit
        Left = 29
        Top = 24
        Width = 115
        Height = 21
        TabOrder = 0
        Text = '2'
      end
      object btnEscalonar: TButton
        Left = 32
        Top = 105
        Width = 115
        Height = 25
        Caption = 'Escalonar'
        TabOrder = 1
        OnClick = btnEscalonarClick
      end
      object edEscalonamentoSy: TEdit
        Left = 29
        Top = 51
        Width = 115
        Height = 21
        TabOrder = 2
        Text = '2'
      end
      object edEscalonamentoSz: TEdit
        Left = 29
        Top = 78
        Width = 113
        Height = 21
        TabOrder = 3
        Text = '2'
      end
    end
    object Rotação: TGroupBox
      Left = 3
      Top = 239
      Width = 177
      Height = 139
      Caption = 'Rota'#231#227'o'
      TabOrder = 3
      object Label17: TLabel
        Left = 3
        Top = 24
        Width = 33
        Height = 13
        Caption = 'Angulo'
      end
      object edAnguloRotacao: TEdit
        Left = 42
        Top = 24
        Width = 132
        Height = 21
        TabOrder = 0
        Text = '30'
      end
      object btnRotacionar: TButton
        Left = 3
        Top = 97
        Width = 171
        Height = 25
        Caption = 'Rotacionar'
        TabOrder = 1
        OnClick = btnRotacionarClick
      end
      object rgEixoRotacao: TRadioGroup
        Left = 11
        Top = 51
        Width = 163
        Height = 40
        Caption = 'Eixo'
        Columns = 3
        ItemIndex = 2
        Items.Strings = (
          'X'
          'Y'
          'Z')
        TabOrder = 2
      end
    end
    object GroupBox9: TGroupBox
      Left = 186
      Top = 160
      Width = 95
      Height = 79
      Caption = 'Reflex'#227'o'
      TabOrder = 4
      object cbRefletirX: TCheckBox
        Left = 3
        Top = 24
        Width = 25
        Height = 17
        Caption = 'X'
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
      object cbRefletirY: TCheckBox
        Left = 34
        Top = 24
        Width = 25
        Height = 17
        Caption = 'Y'
        Checked = True
        State = cbChecked
        TabOrder = 1
      end
      object btnRefletir: TButton
        Left = 3
        Top = 47
        Width = 89
        Height = 25
        Caption = 'Refletir'
        TabOrder = 2
        OnClick = btnRefletirClick
      end
      object cbRefletirZ: TCheckBox
        Left = 65
        Top = 24
        Width = 25
        Height = 17
        Caption = 'Z'
        ParentShowHint = False
        ShowHint = False
        TabOrder = 3
      end
    end
  end
  object GroupBox11: TGroupBox
    Left = 822
    Top = 531
    Width = 73
    Height = 66
    Caption = 'Clipping'
    TabOrder = 4
    object btnClipping: TButton
      Left = 3
      Top = 24
      Width = 67
      Height = 25
      Caption = 'Cortar'
      TabOrder = 0
      OnClick = btnClippingClick
    end
  end
  object GroupBox12: TGroupBox
    Left = 535
    Top = 751
    Width = 370
    Height = 49
    Caption = 'Curvas'
    TabOrder = 5
    object btnCalteljau: TButton
      Left = 3
      Top = 16
      Width = 60
      Height = 25
      Caption = 'Calteljau'
      TabOrder = 0
      OnClick = btnCalteljauClick
    end
    object btnBezier: TButton
      Left = 135
      Top = 16
      Width = 60
      Height = 25
      Caption = 'B'#233'zier'
      TabOrder = 1
      OnClick = btnBezierClick
    end
    object btnHermite: TButton
      Left = 69
      Top = 16
      Width = 60
      Height = 25
      Caption = 'Hermite'
      TabOrder = 2
      OnClick = btnHermiteClick
    end
    object btnBSpline: TButton
      Left = 201
      Top = 16
      Width = 60
      Height = 25
      Caption = 'B-Spline'
      TabOrder = 3
      OnClick = btnBSplineClick
    end
    object btnForwardDifference: TButton
      Left = 265
      Top = 16
      Width = 102
      Height = 25
      Caption = 'Forward Difference'
      TabOrder = 4
      OnClick = btnForwardDifferenceClick
    end
  end
  object OpenTextFileDialog: TOpenTextFileDialog
    Left = 65535
    Top = 780
  end
end
