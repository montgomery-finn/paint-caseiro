//---------------------------------------------------------------------------

#pragma hdrstop

#include "uPonto3d.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Ponto::Ponto(double x, double y): Ponto2D(x,y){
    this->z = 0;
}

Ponto::Ponto(double x, double y, double z) : Ponto2D(x, y){
	this->z = z;
}

UnicodeString Ponto::toString(){
	return "( " + FloatToStr(x) + ", " + FloatToStr(y) + ", " + FloatToStr(z) + ") ";
}

//transformacoes
void Ponto::translada(double dx, double dy, double dz){
    Ponto::translada(dx, dy);
	z += dz;
}

void Ponto::escalonar(double sx, double sy, double sz){
	Ponto2D::escalonar(sx, sy);
	z = z * sz;
}

void Ponto::refletir(bool x, bool y, bool z){
	Ponto2D::refletir(x,y);

	if(z){
		this->z = -this->z;
	}
}

void Ponto::translada(double dx, double dy){
	Ponto2D::translada(dx, dy);
}

void Ponto::escalonar(double sx, double sy){
	Ponto2D::escalonar(sx, sy);
}

void Ponto::refletir(bool x, bool y){
    Ponto2D::refletir(x,y);
}

void Ponto::rotacionar(double angulo, int eixo){
	if(eixo == 2){ //z
		Ponto2D::rotacionar(angulo);
		return;
	}

	double cosAngulo = cos(angulo);
	double sinAngulo = sin(angulo);
	double aux;

	if(eixo == 1){ //y
		aux = x;

		x = x*cosAngulo + z*sinAngulo;
		z = -aux*sinAngulo + z*cosAngulo;
        return;
	}

	//x
	aux = y;

	y = y*cosAngulo - z*sinAngulo;
    z = aux*sinAngulo + z*cosAngulo;

}
