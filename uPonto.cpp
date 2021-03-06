//---------------------------------------------------------------------------

#pragma hdrstop
#include "uPonto.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

//o Ponto:: serve pra dizer que o m?todo construtor pertence ? classe Ponto
Ponto2D::Ponto2D(double nx, double ny){
	x = nx;
    y = ny;
}

//conversoes
int Ponto2D::xW2Vp(double xwmax, double xwmin, double xvpmax, double xvpmin){
	return ((x - xwmin) / (xwmax - xwmin)) * (xvpmax-xvpmin);
}

int Ponto2D::xW2Vp(Janela mundo, Janela vp){
	return ((x - mundo.xmin) / (mundo.xmax - mundo.xmin)) * (vp.xmax-vp.xmin);
}

int Ponto2D::yW2Vp(Janela mundo, Janela vp){
	return (1 - ((y - mundo.ymin) / (mundo.ymax - mundo.ymin))) * (vp.ymax-vp.ymin);
}

UnicodeString Ponto2D::toString(){
    return "( " + FloatToStr(x) + ", " + FloatToStr(y) + ") ";
}
////////////////////////////

//transformacoes
void Ponto2D::translada(double dx, double dy){
	x += dx;
    y += dy;
}

void Ponto2D::escalonar(double sx, double sy){
	x = x * sx;
    y = y * sy;
}

void Ponto2D::refletir(bool x, bool y){
	if(x){
	  this->x = -this->x;
	}

	if(y){
        this->y = -this->y;
	}
}

void Ponto2D::rotacionar(double angulo){
	double cosAngulo = cos(angulo);
	double sinAngulo = sin(angulo);

	double aux = x;

	x = x * cosAngulo - y * sinAngulo;
	y = aux * sinAngulo + y * cosAngulo;
}
/////////////////////

//clipping
int Ponto2D::cohen(Janela janelaClipping){
	int numero = 0;

	if( x < janelaClipping.xmin ){
		numero += 1;
	}
	else if( x > janelaClipping.xmax){
		numero += 2;
	}

	if( y < janelaClipping.ymin	){
		numero += 4;
	}
	else if( y > janelaClipping.ymax){
        numero += 8;
	}

    return numero;
}

bool Ponto2D::clippingPontos(Janela janelaClipping){
	return x >= janelaClipping.xmin && x <= janelaClipping.xmax &&
                    y >= janelaClipping.xmin && y <= janelaClipping.xmax;
}
