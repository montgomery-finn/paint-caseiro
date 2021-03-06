//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "uPonto.h"
#include "uPoligono.h"
#include "uDisplay.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Ponto aux(0,0);
Janela mundo(-250, -250, 250, 250);
Janela vp(0,0,500,500);
Janela clipping(-100,-100,100,100);
Poligono pol;
DisplayFile display;
int contaId = 0;
bool incluirPoligono = false;
bool selecionarPontoCentral = false;

double xVp2W (int xvp, Janela mundo, Janela vp){
    return ((xvp-vp.xmin)/(vp.xmax - vp.xmin)) * (mundo.xmax - mundo.xmin) + mundo.xmin;
}

double yVp2W (int yvp, Janela mundo, Janela vp){
	return (1 - ((yvp-vp.ymin)/(vp.ymax - vp.ymin))) * (mundo.ymax - mundo.ymin) + mundo.ymin;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

	//forma??o do eixo vertical
	aux.x = 0;
	aux.y = mundo.ymax;
	pol.pontos.push_back(aux);
	pol.pontos.push_back(Ponto(0, mundo.ymin));
	pol.id = contaId++;
	pol.tipo = 'E';  //Eixo
	display.poligonos.push_back(pol);
	pol.pontos.clear();

	//forma??o do eixo horizontal
	pol.pontos.push_back(Ponto(mundo.xmin, 0));
	pol.pontos.push_back(Ponto(mundo.xmax, 0));
	pol.id = contaId++;
	pol.tipo = 'E';
	display.poligonos.push_back(pol);
	pol.pontos.clear();

	pol.pontos.push_back(Ponto(clipping.xmin, clipping.ymin));
	pol.pontos.push_back(Ponto(clipping.xmin, clipping.ymax));
	pol.pontos.push_back(Ponto(clipping.xmax, clipping.ymax));
	pol.pontos.push_back(Ponto(clipping.xmax, clipping.ymin));
	pol.pontos.push_back(Ponto(clipping.xmin, clipping.ymin));
	pol.id = contaId++;
	pol.tipo = 'J';
	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.mostra(lbPoligonos);

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
	incluirPoligono = true;
	selecionarPontoCentral = false;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	lbVp->Caption = IntToStr(X) + ", " + IntToStr(Y);

	double xw = xVp2W(X, mundo, vp);
	double yw = yVp2W(Y, mundo, vp);

	lbMundo->Caption = FloatToStr(xw) + ", " + FloatToStr(yw);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbLeft){
		if(incluirPoligono){
			aux.x = xVp2W(X, mundo, vp);
			aux.y = yVp2W(Y, mundo, vp);
			pol.pontos.push_back(aux);
		}
		else if(selecionarPontoCentral){
			edPontoCentralX->Text = xVp2W(X, mundo, vp);
			edPontoCentralY->Text = yVp2W(Y, mundo, vp);
            selecionarPontoCentral = false;
		}
	}
	else{
		if(Button == mbRight){
			incluirPoligono = false;

			if(pol.pontos.size() > 0){
				pol.id = contaId++;

				pol.tipo = 'D'; //Desenho

				display.poligonos.push_back(pol);
				pol.pontos.clear();

				display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
				display.mostra(lbPoligonos);
			}
		}
	}


}
//---------------------------------------------------------------------------

void __fastcall TForm1::lbPoligonosClick(TObject *Sender)
{
	display.mostraPontos(lbPoligonos->ItemIndex, lbPontos);
}
//---------------------------------------------------------------------------

void TForm1::AtualizaMundo()
{
	display.poligonos[0].pontos[0].y = mundo.ymax;
	display.poligonos[0].pontos[1].y = mundo.ymin;

	display.poligonos[1].pontos[0].x = mundo.xmax;
	display.poligonos[1].pontos[1].x = mundo.xmin;

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}


void __fastcall TForm1::Button2Click(TObject *Sender)
{
	mundo.xmin = StrToFloat(edXmin->Text);
	mundo.xmax = StrToFloat(edXmax->Text);
	mundo.ymin = StrToFloat(edYmin->Text);
	mundo.ymax = StrToFloat(edYmax->Text);

	AtualizaMundo();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnTransladarClick(TObject *Sender)
{
	double dx, dy, dz;

	dx = StrToFloat(edDx->Text);
	dy = StrToFloat(edDy->Text);
	dz = StrToFloat(edDz->Text);

	int tipoTransformacao = getTipoTransformacao();

	display.poligonos[lbPoligonos->ItemIndex].translada(dx, dy, dz, tipoTransformacao);

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);

	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}
//---------------------------------------------------------------------------

float TForm1::GetPassoNavegacao(){
	float passo = StrToFloat(edPassoNavegacao->Text);

	if(passo <= 0){
		throw UnicodeString("Passo precisa ser maior que 0");
	}

	return StrToFloat(edPassoNavegacao->Text);
}


void __fastcall TForm1::btnCimaClick(TObject *Sender)
{
	try{
        float passo = GetPassoNavegacao();

		mundo.ymin = mundo.ymin + passo;
		mundo.ymax = mundo.ymax + passo;

		edYmin->Text = mundo.ymin;
		edYmax ->Text = mundo.ymax;

		AtualizaMundo();
	}
	catch(UnicodeString s){
		ShowMessage(s);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnBaixoClick(TObject *Sender)
{
	try{
		float passo = GetPassoNavegacao();

		mundo.ymin = mundo.ymin - passo;
		mundo.ymax = mundo.ymax - passo;

		edYmin->Text = mundo.ymin;
		edYmax ->Text = mundo.ymax;

		AtualizaMundo();
	}
	catch(UnicodeString s){
		ShowMessage(s);
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnEsquerdaClick(TObject *Sender)
{
	try{
		float passo = GetPassoNavegacao();

		mundo.xmin = mundo.xmin - passo;
		mundo.xmax = mundo.xmax - passo;

		edXmin->Text = mundo.xmin;
		edXmax ->Text = mundo.xmax;

		AtualizaMundo();
	}
	catch(UnicodeString s){
		ShowMessage(s);
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnDireitaClick(TObject *Sender)
{
	try{
		float passo = GetPassoNavegacao();

		mundo.xmin = mundo.xmin + passo;
		mundo.xmax = mundo.xmax + passo;

		edXmin->Text = mundo.xmin;
		edXmax ->Text = mundo.xmax;

		AtualizaMundo();
	}
	catch(UnicodeString s){
		ShowMessage(s);
	}
}
//---------------------------------------------------------------------------

float TForm1::GetFatorZoom(){
	float fator = StrToFloat(edFatorZoom->Text);

	if(fator <= 1){
		throw UnicodeString("Passo precisa ser maior que 1");
	}

	return fator;
}

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	try{
	   float fator = GetFatorZoom();

		mundo.xmin = mundo.xmin / fator;
		mundo.xmax = mundo.xmax / fator;
		mundo.ymin = mundo.ymin / fator;
		mundo.ymax = mundo.ymax / fator;

		edXmin->Text = mundo.xmin;
		edXmax ->Text = mundo.xmax;
		edYmin->Text = mundo.ymin;
		edYmax ->Text = mundo.ymax;

		AtualizaMundo();
	}
	catch(UnicodeString s){
		ShowMessage(s);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	try{
		float fator = GetFatorZoom();

		mundo.xmin = mundo.xmin * fator;
		mundo.xmax = mundo.xmax * fator;
		mundo.ymin = mundo.ymin * fator;
		mundo.ymax = mundo.ymax * fator;

		edXmin->Text = mundo.xmin;
		edXmax ->Text = mundo.xmax;
		edYmin->Text = mundo.ymin;
		edYmax ->Text = mundo.ymax;

		AtualizaMundo();
	}
	catch(UnicodeString s){
		ShowMessage(s);
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::rgTipoRetaClick(TObject *Sender)
{
    display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button6Click(TObject *Sender)
{
	selecionarPontoCentral = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	double xc = StrToFloat(edPontoCentralX->Text);
	double yc = StrToFloat(edPontoCentralY->Text);
	double r =  StrToFloat(edRaio->Text);

	pol.gerarCircunferencia(xc, yc, r);

	pol.id = contaId++;

	pol.tipo = 'C'; //Circunferencia

	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(lbPoligonos);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnEscalonarClick(TObject *Sender)
{
	double sx = StrToFloat(edEscalonamentoSx->Text);
	double sy = StrToFloat(edEscalonamentoSy->Text);
	double sz = StrToFloat(edEscalonamentoSz->Text);

	if(sx > 0 && sy > 0 && sz > 0){
       int tipoTransformacao = getTipoTransformacao();

		display.poligonos[lbPoligonos->ItemIndex].escalonar(sx, sy, sz, tipoTransformacao);

		display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);

		display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
	}
	else{
        ShowMessage("Os fatores de escalonamento precisam ser maiores que 0");
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnRefletirClick(TObject *Sender)
{
	bool refletirX = cbRefletirX->Checked;
	bool refletirY = cbRefletirY->Checked;
	bool refletirZ = cbRefletirZ->Checked;

    int tipoTransformacao = getTipoTransformacao();

	display.poligonos[lbPoligonos->ItemIndex].refletir(refletirX, refletirY,
		refletirZ, tipoTransformacao);

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);

	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}
//---------------------------------------------------------------------------


int TForm1::getTipoTransformacao(){
   return rdTipoTransformacao->ItemIndex;
}

void __fastcall TForm1::btnRotacionarClick(TObject *Sender)
{
	double angulo = (StrToFloat(edAnguloRotacao->Text) / 180) * 3.14159265358979323846;

	int tipoTransformacao = getTipoTransformacao();

    int eixo = rgEixoRotacao->ItemIndex;

	display.poligonos[lbPoligonos->ItemIndex].rotacionar(angulo, eixo, tipoTransformacao);

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);

	display.poligonos[lbPoligonos->ItemIndex].mostraPontos(lbPontos);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnClippingClick(TObject *Sender)
{
	display.clipping(clipping, &contaId);

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(lbPoligonos);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnCalteljauClick(TObject *Sender)
{
	pol = display.poligonos[lbPoligonos->ItemIndex].calteljau(5);
	pol.id = contaId++;

	pol.tipo = 'P'; //Param?trica, curva kkkkk

	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(lbPoligonos);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnHermiteClick(TObject *Sender)
{
	pol = display.poligonos[lbPoligonos->ItemIndex].hermite(0.01);
	pol.id = contaId++;

	pol.tipo = 'P'; //Param?trica, curva kkkkk

	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(lbPoligonos);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnBezierClick(TObject *Sender)
{
	pol = display.poligonos[lbPoligonos->ItemIndex].bezier(0.01);
	pol.id = contaId++;

	pol.tipo = 'P'; //Param?trica, curva kkkkk

	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(lbPoligonos);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnBSplineClick(TObject *Sender)
{
	pol = display.poligonos[lbPoligonos->ItemIndex].bSpline(0.01);
	pol.id = contaId++;

	pol.tipo = 'P'; //Param?trica, curva kkkkk

	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(lbPoligonos);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::btnForwardDifferenceClick(TObject *Sender)
{
	pol = display.poligonos[lbPoligonos->ItemIndex].forwardDifference(0.01);
	pol.id = contaId++;

	pol.tipo = 'P'; //Param?trica, curva kkkkk

	display.poligonos.push_back(pol);
	pol.pontos.clear();

	display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	display.mostra(lbPoligonos);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if(OpenTextFileDialog->Execute()){

		UnicodeString dialogFileName = OpenTextFileDialog->FileName;
		AnsiString fileName = dialogFileName;

		FILE *arquivo = fopen(fileName.c_str(), "r");

		char stringChar[255];
		UnicodeString stringPonto;
		char caracter = ' ';
		UnicodeString x,y,z;
		int cursor;
		Ponto aux = Ponto(0,0,0);

		while(!feof(arquivo)){
			fgets(stringChar,255,arquivo);

			stringPonto = UnicodeString(stringChar);

			cursor = 1;

			x = "";
			y = "";
			z = "";


			caracter = ' ';

			while(caracter != ','){
				x += caracter;

				cursor++;
				caracter = stringPonto[cursor];
			}

			aux.x = StrToFloat(x);

			cursor++;
			caracter = stringPonto[cursor];

			while(caracter != ','){
				y += caracter;

				cursor++;
				caracter = stringPonto[cursor];
			}

			aux.y = StrToFloat(y);

			cursor++;
			caracter = stringPonto[cursor];

			while(caracter != ')'){
				z += caracter;

				cursor++;
				caracter = stringPonto[cursor];
			}

			aux.z = StrToFloat(z);

			pol.pontos.push_back(aux);
		}


		pol.id = contaId++;

		pol.tipo = '3'; //3D

		display.poligonos.push_back(pol);
		pol.pontos.clear();

		display.desenha(Image1->Canvas, mundo, vp, rgTipoReta->ItemIndex);
		display.mostra(lbPoligonos);

	}
}
//---------------------------------------------------------------------------



