#pragma once
#ifndef JOC_H
#define JOC_H
#include "Figura.h"
#include "Tauler.h"


class Joc
{
private:
	Tauler m_tauler;
	Figura m_figura;
	bool fiPartida;
public:
	Joc();
	void novaFigura();
	void inicialitza(const string& nomFitxer);
	void mostrarTualer();
	void mostrarFigura();

	void borrarFigura();
	void posarFigura();

	bool giraFigura(DireccioGir direccio);
	void calculGir(DireccioGir direccio, Figura& figura);

	bool mirarSiHaColisionsFigura();
	bool mouFigura(int dirX);
	int baixaFigura();

	int eliminarFila();
	void escriuTauler(const string& nomFitxer);
	void inicialitzaFigura(const int tipusFiguraNova);
	bool getFiPartida()  const { return fiPartida; };
};

#endif