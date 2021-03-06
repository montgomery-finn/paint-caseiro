//---------------------------------------------------------------------------

#pragma hdrstop

#include "uDisplay.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void DisplayFile::desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta){
	canvas->Pen->Color = clBlack;
	canvas->Pen->Width = 3;

	canvas->Brush->Color = clWhite;
	canvas->FillRect(Rect(0,0,500,500));

	for(int i = 0; i < poligonos.size(); i++){
		poligonos[i].desenha(canvas, mundo, vp, tipoReta);
	}
}

void DisplayFile::mostra(TListBox *listbox){
	listbox->Clear();

	for(int i = 0; i < poligonos.size(); i++){
		listbox->Items->Add(poligonos[i].toString());
	}
}

void DisplayFile::mostraPontos(int qualPoligono, TListBox *listbox){
	poligonos[qualPoligono].mostraPontos(listbox);
														
}

void DisplayFile::clipping(Janela janelaClipping, int *contaId){
	int numeroPoligonos = poligonos.size();

	Poligono pol;

	for(int i = 0; i < numeroPoligonos; i++){
		char tipo = poligonos[i].tipo;

		if(tipo != 'E' && tipo != 'J'){
			if(tipo == 'C'){
				pol = poligonos[i].clippingPontos(janelaClipping);
			}
			else{
				pol = poligonos[i].cohen(janelaClipping);
			}

			if(pol.pontos.size() > 0){
				pol.id = *contaId;

				*contaId = *contaId + 1;

				pol.tipo = tipo;

				poligonos.push_back(pol);
			}

			pol.pontos.clear();
		}
	}
}
