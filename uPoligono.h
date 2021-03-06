//---------------------------------------------------------------------------

#ifndef uPoligonoH
#define uPoligonoH

#include "uPonto.h"
#include "uPonto3d.h"
#include <vector>

#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>

using namespace std;

class Poligono{
	public:
		//propriedades
		std::vector<Ponto> pontos;
		int id;
		char tipo;

		//desenho
		void desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta);
		void plotaPontos(TCanvas *canvas, Janela mundo, Janela vp);

		//transformacoes
		void translada(double dx, double dy, double dz, int tipoTransformacao);
		void escalonar(double sx, double sy, double sz, int tipoTransformacao);
		void refletir(bool x, bool y, bool z, int tipoTransformacao);
		void rotacionar(double angulo, int eixo, int tipoTransformacao);

		//circunferencia
		void gerarCircunferencia(double xc, double yc, double r);

		//clipping
		Poligono cohen(Janela janelaClipping);
		Poligono clippingPontos(Janela janelaClipping);

		//conversoes
		UnicodeString toString();
		void mostraPontos(TListBox *listbox);

		//curvas
		Poligono calteljau(int e);
		void calteljau(int e, Poligono *poligono);
		void caltejauSubdividirCurva(Poligono *novoEsquerda, Poligono *novoDireita);
        Poligono hermite(double dt);
        Poligono bezier(double dt);
        Poligono bSpline(double dt);
        Poligono forwardDifference(double dt);


	private:
		//desenho retas
		void lineTo(TCanvas *canvas, Janela mundo, Janela vp);
		void DDA(TCanvas *canvas, Janela mundo, Janela vp);
		void retaDDA(TCanvas *canvas, int x1, int y1, int x2, int y2);
		void bresenham(TCanvas *canvas, Janela mundo, Janela vp);
		void retaBresenham(TCanvas *canvas, int x1, int y1, int x2, int y2);

		//circunferencia
		void gerarPontosCircunferencia(double x, double y);

		//matrizes transformação
		std::vector<std::vector<double>> getMatrizRotacaoX(double angulo);

		std::vector<std::vector<double>> getMatrizRotacaoY(double angulo);

        std::vector<std::vector<double>> getMatrizRotacaoZ(double angulo);

		std::vector<std::vector<double>> getMatrizTranslacao(double dx, double dy, double dz);

		std::vector<std::vector<double>> getMatrizEscalonamento(double sx,
		 double sy, double sz);

		std::vector<std::vector<double>> getMatrizReflexao(bool x, bool y, bool z);
		
		std::vector<std::vector<double>> multiplicaMatrizVector(
			std::vector<std::vector<double>> *a,
			std::vector<std::vector<double>> *b);

		std::vector<std::vector<Ponto>> getMatrizGH();

		std::vector<std::vector<double>> getMatrizXFromMatrizPonto(
			std::vector<std::vector<Ponto>>* matrizPonto);

		std::vector<std::vector<double>> getMatrizYFromMatrizPonto(
			std::vector<std::vector<Ponto>>* matrizPonto);

		std::vector<std::vector<double>> getMatrizH();

		std::vector<std::vector<double>> getMatrizT(double t);

		std::vector<std::vector<double>> getMatrizB();

		std::vector<std::vector<Ponto>> getMatrizGB();

		std::vector<std::vector<double>> getMatrizBS();

		std::vector<std::vector<Ponto>> getMatrizGBS(int i);

		std::vector<std::vector<double>> getMatrizFD(double intervalo);


		//clipping
		void retaCohen(Ponto p1, Ponto p2, Janela janelaClipping, Poligono *novoPoligono);

		//auxiliares
		int round(float n);
		Ponto calcularPontoCentral();

		//curvas
		bool calteljauMenorQueErro(int e);
		bool calteljauMenorQueErro(int e, Ponto p1, Ponto p2);
		Poligono geraPoligonoForwardDifference(double dt,
											   double x, double dx, double dx2, double dx3,
											   double y, double dy, double dy2, double dy3);



		//void espelharPontosCircunferencia(double xc, double yc);
};
//---------------------------------------------------------------------------
#endif
