//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPonto.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

Ponto aux(0,0);
Janela mundo(-250, -250, 250, 250);
Janela vp(0,0,500,500);

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
