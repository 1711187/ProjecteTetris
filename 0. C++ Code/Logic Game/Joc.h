#ifndef JOC_H
#define JOC_H

#include <iostream>
#include "Tauler.h"
#include <fstream>
#include <windows.h>
#include "Figura.h"
#include <string>

using namespace std;

int randomNumber(int numMin, int numMax);

typedef enum
{
	NO_DIR = 0,
	MOV_ESQ,
	MOV_DRE
} DireccioMov;

typedef enum
{
	MOV_VERTICAL = 0,
	MOV_HORIZONTAL,
	MOV_GIRO
} TipusDeMov;

class Joc {
public:
	// Constructors
	Joc();
	Joc(TipusFigura forma);

	// Modifying Methods
	void inicialitza(const string& nomFitxer);
	void calculGir(DireccioGir direccio, Figura& figura);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int direccio);
	int baixaFigura();
	int hardDrop();
	void borraDibuixa(bool borraodibuixa);
	int eliminaFiles();
	void setCursor(int x, int y) { m_tauler.setCursorX(x), m_tauler.setCursorY(y); };
	void setFigura(Figura& fig) { m_figuraActual = fig; };

	void vaciarTauler() { m_tauler.vaciarTauler(); }
	void generarFig(int tipusFigura, int posFil, int posCol, int gir);

	// Consulting Methods
	ColorFigura getTauler(int fila, int columna) { return m_tauler.getValueColor(fila, columna); };
	Punt getCursor() { return m_tauler.getCursor(); };
	Punt getCentre() { return m_figuraActual.getCentre(); };
	Figura getFigura() { return m_figuraActual; };
	bool detectCollision(const Figura& figura);
	void escriuTauler(const string& nomFitxer);
	void escriuTaulerConsola(bool showCursor);
private:
	Figura m_figuraActual;
	Tauler m_tauler;
};

#endif