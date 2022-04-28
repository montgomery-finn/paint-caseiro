//---------------------------------------------------------------------------

#ifndef uPonto3dH
#define uPonto3dH
#include "uPonto.h"
//---------------------------------------------------------------------------
class Ponto : public Ponto2D{
	public:
		double z;

		Ponto(double x, double y);
		Ponto(double x, double y, double z);

        UnicodeString toString();

    	//transformacoes
		void translada(double dx, double dy, double dz);
		void escalonar(double sx, double sy, double sz);
		void refletir(bool x, bool y, bool z);
		void rotacionar(double angulo, int eixo);

		void translada(double dx, double dy);
		void escalonar(double sx, double sy);
		void refletir(bool x, bool y);
};
#endif
