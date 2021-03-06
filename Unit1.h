//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "uJanela.h"
#include <Vcl.Tabs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include "uPonto3d.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TImage *Image1;
	TLabel *lbMundo;
	TLabel *lbVp;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox5;
	TGroupBox *GroupBox4;
	TLabel *Label5;
	TButton *Button4;
	TEdit *edFatorZoom;
	TButton *Button5;
	TGroupBox *GroupBox1;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label6;
	TLabel *Label7;
	TButton *Button2;
	TEdit *edXmin;
	TEdit *edXmax;
	TEdit *edYmin;
	TEdit *edYmax;
	TGroupBox *GroupBox3;
	TLabel *Label8;
	TButton *btnCima;
	TButton *btnEsquerda;
	TButton *btnDireita;
	TButton *btnBaixo;
	TEdit *edPassoNavegacao;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button1;
	TListBox *lbPoligonos;
	TListBox *lbPontos;
	TGroupBox *GroupBox10;
	TRadioGroup *rdTipoTransformacao;
	TGroupBox *GroupBox6;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *edDx;
	TEdit *edDy;
	TButton *btnTransladar;
	TGroupBox *GroupBox8;
	TLabel *Label15;
	TLabel *Label16;
	TEdit *edEscalonamentoSx;
	TButton *btnEscalonar;
	TEdit *edEscalonamentoSy;
	TGroupBox *Rota??o;
	TLabel *Label17;
	TEdit *edAnguloRotacao;
	TButton *btnRotacionar;
	TGroupBox *GroupBox9;
	TCheckBox *cbRefletirX;
	TCheckBox *cbRefletirY;
	TButton *btnRefletir;
	TGroupBox *GroupBox11;
	TButton *btnClipping;
	TGroupBox *GroupBox7;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label14;
	TLabel *Label13;
	TEdit *edPontoCentralX;
	TEdit *edPontoCentralY;
	TButton *Button6;
	TEdit *edRaio;
	TButton *Button7;
	TRadioGroup *rgTipoReta;
	TGroupBox *GroupBox12;
	TButton *btnCalteljau;
	TButton *btnBezier;
	TButton *btnHermite;
	TButton *btnBSpline;
	TButton *btnForwardDifference;
	TOpenTextFileDialog *OpenTextFileDialog;
	TButton *Button3;
	TEdit *edDz;
	TCheckBox *cbRefletirZ;
	TEdit *edEscalonamentoSz;
	TLabel *Label18;
	TLabel *Label19;
	TRadioGroup *rgEixoRotacao;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall lbPoligonosClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall btnTransladarClick(TObject *Sender);
	void __fastcall btnCimaClick(TObject *Sender);
	void __fastcall btnBaixoClick(TObject *Sender);
	void __fastcall btnEsquerdaClick(TObject *Sender);
	void __fastcall btnDireitaClick(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall rgTipoRetaClick(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall btnEscalonarClick(TObject *Sender);
	void __fastcall btnRefletirClick(TObject *Sender);
	void __fastcall btnRotacionarClick(TObject *Sender);
	void __fastcall btnClippingClick(TObject *Sender);
	void __fastcall btnCalteljauClick(TObject *Sender);
	void __fastcall btnHermiteClick(TObject *Sender);
	void __fastcall btnBezierClick(TObject *Sender);
	void __fastcall btnBSplineClick(TObject *Sender);
	void __fastcall btnForwardDifferenceClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);

private:	// User declarations
	void AtualizaMundo();
	float GetPassoNavegacao();
	float GetFatorZoom();
	int getTipoTransformacao();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
