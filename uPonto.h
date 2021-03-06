//---------------------------------------------------------------------------

#ifndef uPontoH
#define uPontoH
#include "uJanela.h"

#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
class Ponto2D {
	public:
		double x;
		double y;

        Ponto2D();
		Ponto2D(double, double);

		//conversoes
		int xW2Vp(double xwmax, double xwmin, double vpmax, double vpmin);
		int xW2Vp(Janela, Janela);
		int yW2Vp(Janela, Janela);
		UnicodeString toString();

		//transformacoes
		void translada(double dx, double dy);
		void escalonar(double sx, double sy);
		void refletir(bool x, bool y);
		void rotacionar(double angulo);

		//clipping
		int cohen(Janela janelaClipping);
		bool clippingPontos(Janela janelaClipping);

};


#endif
