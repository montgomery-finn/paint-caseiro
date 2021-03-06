//---------------------------------------------------------------------------

#pragma hdrstop

#include "uPoligono.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define SIGN(x) ((x) < 0 ? (-1): (1))
#define ABS(x) ((x) < 0 ? (-x) : (x))
#define FALSE 0
#define TRUE 1


//desenho
void Poligono::desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta){

	if(tipo == 'C'){
		plotaPontos(canvas, mundo, vp);
	}
	else{
		switch(tipoReta) {
			case 0:
				lineTo(canvas, mundo, vp);
				break;
			case 1:
				DDA(canvas, mundo, vp);
				break;
			case 2:
				bresenham(canvas, mundo, vp);
				break;
		}
	}
}

void Poligono::plotaPontos(TCanvas *canvas, Janela mundo, Janela vp){
	int numeroPontos = pontos.size();

	int xvp, yvp;

	for(int i = 0; i < numeroPontos - 1; i++){
		xvp = pontos[i].xW2Vp(mundo, vp);
		yvp = pontos[i].yW2Vp(mundo, vp);

		canvas->Pixels[xvp][yvp] = clBlack;
	}
}

//////////////////////

//desenha retas

//DDA
void Poligono::DDA(TCanvas *canvas, Janela mundo, Janela vp){
	int xvp1, xvp2, yvp1, yvp2;


	int numeroPontos = pontos.size();

	for(int i = 0; i < numeroPontos - 1; i++){

		xvp1 = pontos[i].xW2Vp(mundo, vp);
		yvp1 = pontos[i].yW2Vp(mundo, vp);

		xvp2 = pontos[i+1].xW2Vp(mundo, vp);
		yvp2 = pontos[i+1].yW2Vp(mundo, vp);

		retaDDA(canvas, xvp1, yvp1, xvp2, yvp2);
	}
}

void Poligono::retaDDA(TCanvas *canvas, int x1, int y1, int x2, int y2){
	int dx = x2 - x1;
	int dy = y2 - y1;

	float length;

	if( ABS(dx) >= ABS(dy) )
		length = ABS(dx);
	else
		length = ABS(dy);

	if(length > 0){
		float stepX = (float) dx / (float) length;
		float stepY = (float) dy / (float) length;

		float x = x1;
		float y = y1;

		for (int i = 0; i < length; i++) {
			canvas->Pixels[round(x)][round(y)] = clBlack;
			x += stepX;
			y += stepY;
		}
	}
}

//Bresenham
void Poligono::bresenham(TCanvas *canvas, Janela mundo, Janela vp){
	int xvp1, xvp2, yvp1, yvp2;


	int numeroPontos = pontos.size();

	for(int i = 0; i < numeroPontos - 1; i++){

		xvp1 = pontos[i].xW2Vp(mundo, vp);
		yvp1 = pontos[i].yW2Vp(mundo, vp);

		xvp2 = pontos[i+1].xW2Vp(mundo, vp);
		yvp2 = pontos[i+1].yW2Vp(mundo, vp);

		retaDDA(canvas, xvp1, yvp1, xvp2, yvp2);
	}
}

void Poligono::retaBresenham(TCanvas *canvas, int x1, int y1, int x2, int y2){

	int deltax = ABS ( (x2 - x1) );
	int deltay = ABS ( (y2 - y1) );

	int signalx = SIGN ( (x2 - x1) );
	int signaly = SIGN ( (y2 - y1) );

	int x = x1;
	int y = y1;

	if (signalx < 0)
		x -=1;

	if (signaly < 0 )
		y -= 1;

	// trocar deltax com deltay dependendo da inclinacao da reta
	int interchange = FALSE;

	if ( deltay > deltax) {
		int tmp = deltax;
		deltax = deltay;
		deltay = tmp;
		interchange = TRUE;
	}

	int erro = 2 * deltay - deltax;


	for (int i = 0; i < deltax; i++) {
		canvas->Pixels[x][y] = clBlack;

		while (erro >= 0) {
			if (interchange)
				x = x + signalx;
			else
				y = y + signaly;

			erro = erro - 2 * deltax;
		}

		if (interchange)
			y = y + signaly;
		else
			x = x + signalx;
			erro = erro + 2 * deltay;
	}
}

//line to
void Poligono::lineTo(TCanvas *canvas, Janela mundo, Janela vp){
	int xvp, yvp;
	for(int x = 0; x< pontos.size(); x++){
		xvp = pontos[x].xW2Vp(mundo, vp);
		yvp = pontos[x].yW2Vp(mundo, vp);

		if(x == 0){
			canvas->MoveTo(xvp, yvp);
		}
		else{
			canvas->LineTo(xvp, yvp);
		}
	}
}
//////////////////////////////

//transform???es
 void Poligono::translada(double dx, double dy, double dz, int tipoTransformacao){
	if(tipoTransformacao == 0){
		for(int i = 0; i < pontos.size(); i++){
			pontos[i].translada(dx, dy, dz);
		}
	}
	else{
		std::vector<std::vector<double>> vetorPonto;
		vetorPonto.push_back(std::vector<double>());
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(1);

		std::vector<std::vector<double>> matrizTranslacao = getMatrizTranslacao(dx, dy, dz);
		std::vector<std::vector<double>> vetorResultado;

		for(int i = 0; i < pontos.size(); i++){
			vetorPonto[0][0] = pontos[i].x;
			vetorPonto[0][1] = pontos[i].y,
			vetorPonto[0][2] = pontos[i].z,

			vetorResultado = multiplicaMatrizVector(&vetorPonto, &matrizTranslacao);

			pontos[i].x = vetorResultado[0][0];
			pontos[i].y = vetorResultado[0][1];
			pontos[i].z = vetorResultado[0][2];
		}
	}
}

void Poligono::escalonar(double sx, double sy, double sz, int tipoTransformacao){
	if(tipoTransformacao == 0){
		for(int i = 0; i < pontos.size(); i++){
			pontos[i].escalonar(sx, sy, sz);
		}
	}
	else{
		Ponto pontoCentral = this->calcularPontoCentral();

		std::vector<std::vector<double>> matrizEscalonamento =
			getMatrizEscalonamento(sx, sy, sz);

		std::vector<std::vector<double>> matrizTranslacaoPre =
			getMatrizTranslacao(-pontoCentral.x, -pontoCentral.y, -pontoCentral.z);

		std::vector<std::vector<double>> aux =
			multiplicaMatrizVector(&matrizTranslacaoPre, &matrizEscalonamento);

		std::vector<std::vector<double>> matrizTranslacaoPos =
			getMatrizTranslacao(pontoCentral.x, pontoCentral.y, pontoCentral.z);

		std::vector<std::vector<double>> matrizTransformacao =
			multiplicaMatrizVector(&aux, &matrizTranslacaoPos);

		std::vector<std::vector<double>> vetorPonto;
		vetorPonto.push_back(std::vector<double>());
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(1);

		std::vector<std::vector<double>> vetorResultado;

		for(int i = 0; i < pontos.size(); i++){
			vetorPonto[0][0] = pontos[i].x;
			vetorPonto[0][1] = pontos[i].y,
			vetorPonto[0][2] = pontos[i].z,

			vetorResultado = multiplicaMatrizVector(&vetorPonto, &matrizTransformacao);

			pontos[i].x = vetorResultado[0][0];
			pontos[i].y = vetorResultado[0][1];
			pontos[i].z = vetorResultado[0][2];
		}
	}
}

void Poligono::refletir(bool x, bool y, bool z, int tipoTransformacao){
	if(tipoTransformacao == 0){
		for(int i = 0; i < pontos.size(); i++){
			pontos[i].refletir(x, y, z);
		}
	}
	else{
		std::vector<std::vector<double>> vetorPonto;
		vetorPonto.push_back(std::vector<double>());
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(1);

		std::vector<std::vector<double>> matrizReflexao =
			getMatrizReflexao(x, y, z);

		std::vector<std::vector<double>> vetorResultado;

		for(int i = 0; i < pontos.size(); i++){
			vetorPonto[0][0] = pontos[i].x;
			vetorPonto[0][1] = pontos[i].y,
			vetorPonto[0][2] = pontos[i].z,

			vetorResultado = multiplicaMatrizVector(&vetorPonto, &matrizReflexao);

			pontos[i].x = vetorResultado[0][0];
			pontos[i].y = vetorResultado[0][1];
			pontos[i].z = vetorResultado[0][2];
		}
	}

}

void Poligono::rotacionar(double angulo, int eixo, int tipoTransformacao){
	Ponto pontoCentral = calcularPontoCentral();

	if(tipoTransformacao == 0){
		for(int i = 0; i < pontos.size(); i++){
			//pontos[i].translada(-pontoCentral.x, -pontoCentral.y);
			pontos[i].rotacionar(angulo, eixo);
			//pontos[i].translada(pontoCentral.x, pontoCentral.y);
		}
	}
	else{
		std::vector<std::vector<double>> matrizRotacao =
			eixo == 0 ? getMatrizRotacaoX(angulo) :
			eixo == 1 ? getMatrizRotacaoY(angulo) :
			getMatrizRotacaoZ(angulo);

		std::vector<std::vector<double>> matrizTranslacaoPre =
			getMatrizTranslacao(-pontoCentral.x, -pontoCentral.y, -pontoCentral.z);

		std::vector<std::vector<double>> aux =
			multiplicaMatrizVector(&matrizTranslacaoPre, &matrizRotacao);

		std::vector<std::vector<double>> matrizTranslacaoPos =
			getMatrizTranslacao(pontoCentral.x, pontoCentral.y, pontoCentral.z);

		std::vector<std::vector<double>> matrizTransformacao =
			multiplicaMatrizVector(&aux, &matrizTranslacaoPos);

		std::vector<std::vector<double>> vetorPonto;
		vetorPonto.push_back(std::vector<double>());
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(0);
		vetorPonto[0].push_back(1);

		std::vector<std::vector<double>> vetorResultado;

		for(int i = 0; i < pontos.size(); i++){
			vetorPonto[0][0] = pontos[i].x;
			vetorPonto[0][1] = pontos[i].y;
			vetorPonto[0][2] = pontos[i].z;

			vetorResultado = multiplicaMatrizVector(&vetorPonto, &matrizTransformacao);

			pontos[i].x = vetorResultado[0][0];
			pontos[i].y = vetorResultado[0][1];
			pontos[i].z = vetorResultado[0][2];
		}
	}
}
//////////////////////////////////////////

//matrizes transforma??o

std::vector<std::vector<double>> Poligono::getMatrizRotacaoX(double angulo){
	double cosAngulo = cos(angulo);
	double sinAngulo = sin(angulo);

	std::vector<std::vector<double>> matriz;

	matriz.push_back(std::vector<double>());
	matriz[0].push_back(1);
	matriz[0].push_back(0);
	matriz[0].push_back(0);
	matriz[0].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[1].push_back(0);
	matriz[1].push_back(cosAngulo);
	matriz[1].push_back(sinAngulo);
	matriz[1].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[2].push_back(0);
	matriz[2].push_back(-sinAngulo);
	matriz[2].push_back(cosAngulo);
	matriz[2].push_back(0);

    matriz.push_back(std::vector<double>());
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(1);

	return matriz;
}

std::vector<std::vector<double>> Poligono::getMatrizRotacaoY(double angulo){
	double cosAngulo = cos(angulo);
	double sinAngulo = sin(angulo);

	std::vector<std::vector<double>> matriz;

	matriz.push_back(std::vector<double>());
	matriz[0].push_back(cosAngulo);
	matriz[0].push_back(0);
	matriz[0].push_back(-sinAngulo);
	matriz[0].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[1].push_back(0);
	matriz[1].push_back(1);
	matriz[1].push_back(0);
	matriz[1].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[2].push_back(sinAngulo);
	matriz[2].push_back(0);
	matriz[2].push_back(cosAngulo);
	matriz[2].push_back(0);

    matriz.push_back(std::vector<double>());
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(1);

	return matriz;
}

std::vector<std::vector<double>> Poligono::getMatrizRotacaoZ(double angulo){
	double cosAngulo = cos(angulo);
	double sinAngulo = sin(angulo);

	std::vector<std::vector<double>> matriz;

	matriz.push_back(std::vector<double>());
	matriz[0].push_back(cosAngulo);
	matriz[0].push_back(sinAngulo);
	matriz[0].push_back(0);
	matriz[0].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[1].push_back(-sinAngulo);
	matriz[1].push_back(cosAngulo);
	matriz[1].push_back(0);
	matriz[1].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[2].push_back(0);
	matriz[2].push_back(0);
	matriz[2].push_back(1);
	matriz[2].push_back(0);

    matriz.push_back(std::vector<double>());
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(1);

	return matriz;
}

std::vector<std::vector<double>> Poligono::getMatrizTranslacao(double dx, double dy, double dz){
	std::vector<std::vector<double>> matriz;

	matriz.push_back(std::vector<double>());
	matriz[0].push_back(1);
	matriz[0].push_back(0);
	matriz[0].push_back(0);
	matriz[0].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[1].push_back(0);
	matriz[1].push_back(1);
	matriz[1].push_back(0);
	matriz[1].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[2].push_back(0);
	matriz[2].push_back(0);
	matriz[2].push_back(1);
	matriz[2].push_back(0);

    matriz.push_back(std::vector<double>());
	matriz[3].push_back(dx);
	matriz[3].push_back(dy);
	matriz[3].push_back(dz);
	matriz[3].push_back(1);

	return matriz;
}

std::vector<std::vector<double>> Poligono::getMatrizEscalonamento(double sx, double sy, double sz){
	std::vector<std::vector<double>> matriz;

	matriz.push_back(std::vector<double>());
	matriz[0].push_back(sx);
	matriz[0].push_back(0);
	matriz[0].push_back(0);
	matriz[0].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[1].push_back(0);
	matriz[1].push_back(sy);
	matriz[1].push_back(0);
	matriz[1].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[2].push_back(0);
	matriz[2].push_back(0);
	matriz[2].push_back(sz);
	matriz[2].push_back(0);

    matriz.push_back(std::vector<double>());
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(1);

	return matriz;
}

std::vector<std::vector<double>> Poligono::getMatrizReflexao(bool x, bool y, bool z){
    std::vector<std::vector<double>> matriz;

	matriz.push_back(std::vector<double>());
	matriz[0].push_back(x ? -1 : 1);
	matriz[0].push_back(0);
	matriz[0].push_back(0);
	matriz[0].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[1].push_back(0);
	matriz[1].push_back(y ? -1 : 1);
	matriz[1].push_back(0);
	matriz[1].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[2].push_back(0);
	matriz[2].push_back(0);
	matriz[2].push_back(z ? -1 : 1);
	matriz[2].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(1);

	return matriz;
}

////////////////////////////////////////////

//circunferencia

 void Poligono::gerarCircunferencia(double xc, double yc, double r)
{
	double x, y, p;
	x = 0;
	y = r;

	gerarPontosCircunferencia(x, y);

	p = 1 - r;

	while (x < y) {
		if (p < 0)
			x ++;
		else {
			x ++;
			y --;
		}

		if (p < 0)
			p += 2 * x + 1;
		else
			p += 2 * (x - y) + 1;

		gerarPontosCircunferencia(x, y);
	}

	translada(xc, yc, 0, 1);
}

void Poligono::gerarPontosCircunferencia(double x, double y){
	pontos.push_back(Ponto(x, y));
	pontos.push_back(Ponto(y, x));
	pontos.push_back(Ponto(y, -x));
	pontos.push_back(Ponto(x, - y));
	pontos.push_back(Ponto(- x, -y));
	pontos.push_back(Ponto(- y, -x));
	pontos.push_back(Ponto(- y, x));
	pontos.push_back(Ponto(- x, y));
}
/////////////////////////////////////////////////

//auxiliares

Ponto Poligono::calcularPontoCentral(){
	double somatorioX = 0, somatorioY = 0, somatorioZ = 0;

	int numeroPontos = pontos.size();

	if(numeroPontos > 0){
		for(int i = 0; i < pontos.size(); i++){
			somatorioX += pontos[i].x;
			somatorioY += pontos[i].y;
			somatorioZ += pontos[i].z;
		}

		return Ponto(somatorioX / numeroPontos, somatorioY / numeroPontos, somatorioZ/numeroPontos);
	}

	return Ponto(0,0);
}

int Poligono::round(float n){
	float decimal = n - (int(n));

	if(n > 0.5)
		return ((int)n) +1;

	return ((int)n);
}
//////////////////////////////////////////////

//clipping
Poligono Poligono::cohen(Janela janelaClipping){
   int numeroPontos = pontos.size();

   Poligono novoPoligono;

	for(int i = 0; i < numeroPontos - 1; i++){
		retaCohen(pontos[i], pontos[i+1], janelaClipping,&novoPoligono);
	}

    return novoPoligono;
}



void Poligono::retaCohen(Ponto p1, Ponto p2, Janela janelaClipping, Poligono *novoPoligono)
{
	double x, y;
	bool accept = false, done = false;

	int codigo1= p1.cohen(janelaClipping);
	int codigo2= p2.cohen(janelaClipping);

	int codigoAux;

	double dy = p2.y - p1.y;
	double dx = p2.x - p1.x;


	do {
		if (codigo1 == 0 && codigo2 == 0) {
			accept = true;
			done = true; // desenha inteiro
		}

		else if((codigo1 & codigo2) != 0) {
			done = true; // n?o desenha
		}

		else { // talvez desenhe
			codigoAux = (codigo1 != 0) ? codigo1 : codigo2; // escolher um ponto

			if (codigoAux & 8) { //cima
				x = p1.x + dx * (janelaClipping.ymax - p1.y) / dy; y = janelaClipping.ymax;
			}
			else if(codigoAux & 4) { //baixo
				x = p1.x + dx * (janelaClipping.ymin - p1.y) / dy; y = janelaClipping.ymin;
			}

			else if(codigoAux & 2) { //direita
				y = p1.y + dy * (janelaClipping.xmax - p1.x) / dx; x = janelaClipping.xmax;
			}
			else if(codigoAux & 1) { //esquerda
				y = p1.y + dy * (janelaClipping.xmin - p1.x) / dx; x = janelaClipping.xmin;
			}

			if (codigoAux == codigo1) {
				p1.x = x; p1.y = y;
				codigo1 = p1.cohen(janelaClipping);
			} else {
				p2.x = x;
				p2.y = y;
				codigo2 = p2.cohen(janelaClipping);
			}
		}
	} while (!done);

	if (accept){
		novoPoligono->pontos.push_back(p1);
		novoPoligono->pontos.push_back(p2);
	}
}

Poligono Poligono::clippingPontos(Janela janelaClipping){
   int numeroPontos = pontos.size();

   Poligono novoPoligono;

   bool insere;

	for(int i = 0; i < numeroPontos; i++){
		insere = pontos[i].clippingPontos(janelaClipping);

		if(insere){
			novoPoligono.pontos.push_back(pontos[i]);
		}
	}

    return novoPoligono;
}

//////////////////////////////////////

//conversoes
void Poligono::mostraPontos(TListBox *listbox){
	listbox->Clear();

	for(int i = 0; i < pontos.size(); i++){
		listbox->Items->Add(pontos[i].toString());
	}
}

UnicodeString Poligono::toString(){
	return IntToStr(id) + "-" + tipo;
}
///////////////////////////////

//curvas

Poligono Poligono::calteljau(int e){
	if(pontos.size() < 3){
	   throw UnicodeString("N?mero de pontos insuficiente para a execu??o do algoritmo de Calteljau.\n O poligono precisa ter tr?s ou mais pontos");
	}

	Poligono novoPoligono;

	calteljau(e, &novoPoligono);

    return novoPoligono;
}

void Poligono::calteljau(int e, Poligono *poligono){
	if(calteljauMenorQueErro(e)){
		for(int i = 0; i < 3; i++){
			poligono->pontos.push_back(pontos[i]);
		}
	}
	else{
		Poligono novoEsquerda, novoDireita;
		caltejauSubdividirCurva(&novoEsquerda, &novoDireita);
		novoEsquerda.calteljau(e, poligono);
		novoDireita.calteljau(e, poligono);
	}
}


bool Poligono::calteljauMenorQueErro(int e){
	return calteljauMenorQueErro(e, pontos[0], pontos[1]) && calteljauMenorQueErro(e, pontos[1], pontos[2]);
}

bool Poligono::calteljauMenorQueErro(int e, Ponto p1, Ponto p2){
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;

	float length;

	if( ABS(dx) >= ABS(dy) )
		length = ABS(dx);
	else
		length = ABS(dy);

	return length <= e;
}

void Poligono::caltejauSubdividirCurva(Poligono *novoEsquerda, Poligono *novoDireita){

	Poligono esquerda;
	esquerda.pontos.push_back(pontos[0]);
	esquerda.pontos.push_back(pontos[1]);
	Ponto pontoCentralEsquerda = esquerda.calcularPontoCentral();

	Poligono direita;
	direita.pontos.push_back(pontos[1]);
	direita.pontos.push_back(pontos[2]);
	Ponto pontoCentralDireita = direita.calcularPontoCentral();

	Poligono aux;
	aux.pontos.push_back(pontoCentralEsquerda);
	aux.pontos.push_back(pontoCentralDireita);
	Ponto pontoCentralAux = aux.calcularPontoCentral();

	novoEsquerda->pontos.push_back(esquerda.pontos[0]);
	novoEsquerda->pontos.push_back(pontoCentralEsquerda);
	novoEsquerda->pontos.push_back(pontoCentralAux);

	novoDireita->pontos.push_back(pontoCentralAux);
	novoDireita->pontos.push_back(pontoCentralDireita);
	novoDireita->pontos.push_back(direita.pontos[1]);
}

Poligono Poligono::hermite(double dt){
	if(pontos.size() < 4){
	   throw UnicodeString("N?mero de pontos insuficiente para a execu??o do algoritmo de Hermite.\n O poligono precisa ter quatro ou mais pontos");
	}

	std::vector<std::vector<double>> matrizH = getMatrizH();

	std::vector<std::vector<Ponto>> matrizGH = getMatrizGH();

	std::vector<std::vector<double>> matrizGHx = getMatrizXFromMatrizPonto(&matrizGH);

	std::vector<std::vector<double>> matrizGHy = getMatrizYFromMatrizPonto(&matrizGH);

	std::vector<std::vector<double>> matrizCoeficienteX =
		multiplicaMatrizVector(&matrizH, &matrizGHx);

	std::vector<std::vector<double>> matrizCoeficienteY =
		multiplicaMatrizVector(&matrizH, &matrizGHy);

	std::vector<std::vector<double>> matrizT;

	Poligono poligono;

	Ponto aux = Ponto(0,0);

	for(double t = 0; t <= 1; t += dt){
		matrizT = getMatrizT(t);

		aux.x = multiplicaMatrizVector(&matrizT, &matrizCoeficienteX)[0][0];
		aux.y = multiplicaMatrizVector(&matrizT, &matrizCoeficienteY)[0][0];
		poligono.pontos.push_back(aux);
	}

	return poligono;
}



std::vector<std::vector<Ponto>> Poligono::getMatrizGH(){
	Ponto p1 = pontos[0];
	Ponto p2 = pontos[1];
	Ponto p3 = pontos[2];
	Ponto p4 = pontos[3];

	Ponto r1 = Ponto(p2.x - p1.x, p2.y - p1.y);
	Ponto r4 = Ponto(p4.x - p3.x, p4.y - p3.y);

	std::vector<std::vector<Ponto>> matriz;

	matriz.push_back(std::vector<Ponto>());
	matriz[0].push_back(p1);

	matriz.push_back(std::vector<Ponto>());
	matriz[1].push_back(p4);

	matriz.push_back(std::vector<Ponto>());
	matriz[2].push_back(r1);

	matriz.push_back(std::vector<Ponto>());
	matriz[3].push_back(r4);

	return matriz;
}

std::vector<std::vector<double>> Poligono::getMatrizXFromMatrizPonto(
	std::vector<std::vector<Ponto>>* matrizPonto){

	std::vector<std::vector<double>> matriz;

	int numeroLinhas = matrizPonto->size();
	int numeroColunas;
	
	for(int l = 0; l < numeroLinhas; l++){
		matriz.push_back(std::vector<double>());

		numeroColunas = (*matrizPonto)[l].size();

		for(int c = 0; c < numeroColunas; c++){
			matriz[l].push_back((*matrizPonto)[l][c].x);
		}	
	}

	return matriz;
}

std::vector<std::vector<double>> Poligono::getMatrizYFromMatrizPonto(
	std::vector<std::vector<Ponto>>* matrizPonto){

	std::vector<std::vector<double>> matriz;

	int numeroLinhas = matrizPonto->size();
	int numeroColunas;
	
	for(int l = 0; l < numeroLinhas; l++){
		matriz.push_back(std::vector<double>());

		numeroColunas = (*matrizPonto)[l].size();

		for(int c = 0; c < numeroColunas; c++){
			matriz[l].push_back((*matrizPonto)[l][c].y);
		}	
	}

	return matriz;
}

std::vector<std::vector<double>> Poligono::getMatrizH(){

	std::vector<std::vector<double>> matriz;

	matriz.push_back(std::vector<double>());
	matriz[0].push_back(2);
	matriz[0].push_back(-2);
	matriz[0].push_back(1);
	matriz[0].push_back(1);

	matriz.push_back(std::vector<double>());
	matriz[1].push_back(-3);
	matriz[1].push_back(3);
	matriz[1].push_back(-2);
	matriz[1].push_back(-1);

	matriz.push_back(std::vector<double>());
	matriz[2].push_back(0);
	matriz[2].push_back(0);
	matriz[2].push_back(1);
	matriz[2].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[3].push_back(1);
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(0);

	return matriz;
}

std::vector<std::vector<double>> Poligono::getMatrizT(double t){

	std::vector<std::vector<double>> matriz;

	matriz.push_back(std::vector<double>());

	matriz[0].push_back(t * t * t);
	matriz[0].push_back(t*t);
	matriz[0].push_back(t);
	matriz[0].push_back(1);

	return matriz;
}


std::vector<std::vector<double>> Poligono::multiplicaMatrizVector(
	std::vector<std::vector<double>> *a,
	std::vector<std::vector<double>> *b){

	int linhasA = a->size();
	if(linhasA == 0) throw UnicodeString("matriz vazia");
	int colunasA = (*a)[0].size();

	int linhasB = b->size();
	if(linhasB == 0) throw UnicodeString("matriz vazia");
	int colunasB = (*b)[0].size();

	if(colunasA != linhasB) throw UnicodeString("n?o foi poss?vel multiplicar as matrizes");

	std::vector<std::vector<double>> res;

	double vlA, vlB;

	for(int l = 0; l < linhasA; l++){
		res.push_back(vector<double>());

		for(int c = 0; c < colunasB; c++){
			res[l].push_back(0);

			for(int x = 0; x < linhasB; x++){
				vlA = (*a)[l][x];
				vlB =  (*b)[x][c];
				res[l][c] += vlA * vlB;
			}
		}
	}

	return res;
}


std::vector<std::vector<double>> Poligono::getMatrizB(){
	std::vector<std::vector<double>> matriz;

	matriz.push_back(std::vector<double>());
	matriz[0].push_back(-1);
	matriz[0].push_back(3);
	matriz[0].push_back(-3);
	matriz[0].push_back(1);

	matriz.push_back(std::vector<double>());
	matriz[1].push_back(3);
	matriz[1].push_back(-6);
	matriz[1].push_back(3);
	matriz[1].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[2].push_back(-3);
	matriz[2].push_back(3);
	matriz[2].push_back(0);
	matriz[2].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[3].push_back(1);
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(0);

	return matriz;
}

std::vector<std::vector<Ponto>> Poligono::getMatrizGB(){
	Ponto p1 = pontos[0];
	Ponto p2 = pontos[1];
	Ponto p3 = pontos[2];
	Ponto p4 = pontos[3];

	std::vector<std::vector<Ponto>> matriz;

	matriz.push_back(std::vector<Ponto>());
	matriz[0].push_back(p1);

	matriz.push_back(std::vector<Ponto>());
	matriz[1].push_back(p2);

	matriz.push_back(std::vector<Ponto>());
	matriz[2].push_back(p3);

	matriz.push_back(std::vector<Ponto>());
	matriz[3].push_back(p4);

	return matriz;
}

Poligono Poligono::bezier(double dt){
	if(pontos.size() < 4){
	   throw UnicodeString("N?mero de pontos insuficiente para a execu??o do algoritmo de Bezier.\n O poligono precisa ter quatro ou mais pontos");
	}

	std::vector<std::vector<double>> matrizB = getMatrizB();

	std::vector<std::vector<Ponto>> matrizGB = getMatrizGB();

	std::vector<std::vector<double>> matrizGBx = getMatrizXFromMatrizPonto(&matrizGB);

	std::vector<std::vector<double>> matrizGBy = getMatrizYFromMatrizPonto(&matrizGB);

	std::vector<std::vector<double>> matrizCoeficienteX =
		multiplicaMatrizVector(&matrizB, &matrizGBx);

	std::vector<std::vector<double>> matrizCoeficienteY =
		multiplicaMatrizVector(&matrizB, &matrizGBy);

	std::vector<std::vector<double>> matrizT;

	Poligono poligono;

	Ponto aux = Ponto(0,0);

	for(double t = 0; t <= 1; t += dt){
		matrizT = getMatrizT(t);

		aux.x = multiplicaMatrizVector(&matrizT, &matrizCoeficienteX)[0][0];
		aux.y = multiplicaMatrizVector(&matrizT, &matrizCoeficienteY)[0][0];
		poligono.pontos.push_back(aux);
	}

	return poligono;
}

std::vector<std::vector<double>> Poligono::getMatrizBS(){
	std::vector<std::vector<double>> matriz;

	matriz.push_back(std::vector<double>());
	matriz[0].push_back(-1);
	matriz[0].push_back(3);
	matriz[0].push_back(-3);
	matriz[0].push_back(1);

	matriz.push_back(std::vector<double>());
	matriz[1].push_back(3);
	matriz[1].push_back(-6);
	matriz[1].push_back(3);
	matriz[1].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[2].push_back(-3);
	matriz[2].push_back(0);
	matriz[2].push_back(3);
	matriz[2].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[3].push_back(1);
	matriz[3].push_back(4);
	matriz[3].push_back(1);
	matriz[3].push_back(0);

	return matriz;
}

std::vector<std::vector<Ponto>> Poligono::getMatrizGBS(int i){

	std::vector<std::vector<Ponto>> matriz;

	Ponto aux = pontos[i-3];
	matriz.push_back(std::vector<Ponto>());
	matriz[0].push_back(aux);

	aux = pontos[i-2];
	matriz.push_back(std::vector<Ponto>());
	matriz[1].push_back(aux);
	
	aux = pontos[i-1];
	matriz.push_back(std::vector<Ponto>());
	matriz[2].push_back(aux);

	aux = pontos[i];
	matriz.push_back(std::vector<Ponto>());
	matriz[3].push_back(aux);

	return matriz;
}

Poligono Poligono::bSpline(double dt){
	int numeroPontos = pontos.size(); 

	if(numeroPontos < 4){
	   throw UnicodeString("N?mero de pontos insuficiente para a execu??o do algoritmo de Bezier.\n O poligono precisa ter quatro ou mais pontos");
	}

	std::vector<std::vector<double>> matrizBS = getMatrizBS();

	std::vector<std::vector<Ponto>> matrizGBSi; 
	std::vector<std::vector<double>> matrizGBSiX;
	std::vector<std::vector<double>> matrizGBSiY; 
  

	std::vector<std::vector<double>> matrizCoeficienteX;
	std::vector<std::vector<double>> matrizCoeficienteY;

	std::vector<std::vector<double>> matrizT;

	Poligono poligono;
	Ponto aux = Ponto(0,0);
	
	for(int i = 3; i < numeroPontos; i++){
		matrizGBSi = getMatrizGBS(i);
		matrizGBSiX = getMatrizXFromMatrizPonto(&matrizGBSi); 
		matrizGBSiY = getMatrizYFromMatrizPonto(&matrizGBSi);

		matrizCoeficienteX = multiplicaMatrizVector(&matrizBS, &matrizGBSiX);
		matrizCoeficienteY = multiplicaMatrizVector(&matrizBS, &matrizGBSiY);

		for(double t = 0; t <= 1; t += dt){
			matrizT = getMatrizT(t);

			aux.x = multiplicaMatrizVector(&matrizT, &matrizCoeficienteX)[0][0] / 6;
			aux.y = multiplicaMatrizVector(&matrizT, &matrizCoeficienteY)[0][0] / 6;
			poligono.pontos.push_back(aux);
		}
	}

	return poligono;
}

Poligono Poligono::forwardDifference(double dt){
	if(pontos.size() < 4){
	   throw UnicodeString("N?mero de pontos insuficiente para a execu??o do algoritmo de Bezier.\n O poligono precisa ter quatro ou mais pontos");
	}

	std::vector<std::vector<double>> matrizB = getMatrizB();

	std::vector<std::vector<Ponto>> matrizGB = getMatrizGB();

	std::vector<std::vector<double>> matrizGBx = getMatrizXFromMatrizPonto(&matrizGB);

	std::vector<std::vector<double>> matrizGBy = getMatrizYFromMatrizPonto(&matrizGB);

	std::vector<std::vector<double>> matrizCoeficienteX =
		multiplicaMatrizVector(&matrizB, &matrizGBx);

	std::vector<std::vector<double>> matrizCoeficienteY =
		multiplicaMatrizVector(&matrizB, &matrizGBy);

	std::vector<std::vector<double>> matrizFD = getMatrizFD(dt);

	std::vector<std::vector<double>> matrizDx =
						multiplicaMatrizVector(&matrizFD, &matrizCoeficienteX);

	std::vector<std::vector<double>> matrizDy =
						multiplicaMatrizVector(&matrizFD, &matrizCoeficienteY);

	return geraPoligonoForwardDifference(dt,
		matrizDx[0][0], matrizDx[1][0], matrizDx[2][0], matrizDx[3][0],
		matrizDy[0][0], matrizDy[1][0], matrizDy[2][0], matrizDy[3][0]);
}

std::vector<std::vector<double>> Poligono::getMatrizFD(double intervalo){
	std::vector<std::vector<double>> matriz;

	double intervalo2 = intervalo * intervalo;
	double intervalo3 = intervalo2 * intervalo;

	matriz.push_back(std::vector<double>());
	matriz[0].push_back(0);
	matriz[0].push_back(0);
	matriz[0].push_back(0);
	matriz[0].push_back(1);

	matriz.push_back(std::vector<double>());
	matriz[1].push_back(intervalo3);
	matriz[1].push_back(intervalo2);
	matriz[1].push_back(intervalo);
	matriz[1].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[2].push_back(6*intervalo3);
	matriz[2].push_back(2*intervalo2);
	matriz[2].push_back(0);
	matriz[2].push_back(0);

	matriz.push_back(std::vector<double>());
	matriz[3].push_back(6*intervalo3);
	matriz[3].push_back(0);
	matriz[3].push_back(0);
	matriz[3].push_back(0);

	return matriz;
}

Poligono Poligono::geraPoligonoForwardDifference(double dt,
											   double x, double dx, double dx2, double dx3,
											   double y, double dy, double dy2, double dy3)
{
   Poligono poligono;
   Ponto aux = Ponto(x, y);

   for(double t = 0; t <= 1; t += dt){
		poligono.pontos.push_back(aux);

		x += dx;
		dx += dx2;
		dx2 += dx3;

		y += dy;
		dy += dy2;
		dy2 += dy3;

		aux = Ponto(x,y);
	}

    return poligono;
}



