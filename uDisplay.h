//---------------------------------------------------------------------------

#ifndef uDisplayH
#define uDisplayH

#include "uPoligono.h"
#include "uJanela.h"
#include <vector>

#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>

//---------------------------------------------------------------------------

class DisplayFile {
	public:
		std::vector <Poligono> poligonos;

		void desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta);
		void mostra(TListBox *listbox);
		void mostraPontos(int qualPoligono, TListBox *listbox);

		void clipping(Janela janelaClipping, int *contaId);
};

#endif
