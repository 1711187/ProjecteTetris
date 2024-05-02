#pragma once
#include <iostream>
#include <string>

using namespace std;

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;
const int NUM_TIPUS_FIGURES = 8;
const int NUM_COLORS = 9;
const int MAX_CELLES_FIGURES = 16;

typedef enum
{
	GIR_HORARI = 0,
	GIR_ANTI_HORARI
} DireccioGir;

typedef enum
{
	NO_FIGURA = 0,
	FIGURA_O,
	FIGURA_I,
	FIGURA_T,
	FIGURA_L,
	FIGURA_J,
	FIGURA_Z,
	FIGURA_S
} TipusFigura;

typedef enum
{
	COLOR_NEGRE = 0,
	COLOR_GROC,
	COLOR_BLAUCEL,
	COLOR_MAGENTA,
	COLOR_TARONJA,
	COLOR_BLAUFOSC,
	COLOR_VERMELL,
	COLOR_VERD,
	NO_COLOR
} ColorFigura;

const TipusFigura canviDeBase[NUM_TIPUS_FIGURES] =
{
	NO_FIGURA,
	FIGURA_O,
	FIGURA_I,
	FIGURA_T,
	FIGURA_L,
	FIGURA_J,
	FIGURA_Z,
	FIGURA_S
};

const ColorFigura canviDeColor[NUM_COLORS] =
{
	COLOR_NEGRE,
	COLOR_GROC,
	COLOR_BLAUCEL,
	COLOR_MAGENTA,
	COLOR_TARONJA,
	COLOR_BLAUFOSC,
	COLOR_VERMELL,
	COLOR_VERD,
	NO_COLOR
};

const bool matriuInicialitzadora[NUM_TIPUS_FIGURES][MAX_ALCADA][MAX_AMPLADA] =
{
	{},

	{{1, 1},
	 {1, 1}},

	{{0, 0, 0, 0},
	 {1, 1, 1, 1},
	 {0, 0, 0, 0},
	 {0, 0, 0, 0}},

	{{0, 1, 0},
	 {1, 1, 1},
	 {0, 0, 0}},

	{{0, 0, 1},
	 {1, 1, 1},
	 {0, 0, 0}},

	{{1, 0, 0},
	 {1, 1, 1},
	 {0, 0, 0}},

	{{1, 1, 0},
	 {0, 1, 1},
	 {0, 0, 0}},

	{{0, 1, 1},
	 {1, 1, 0},
	 {0, 0, 0}},
};



class Figura {

public:
	Figura();
	Figura(TipusFigura t, ColorFigura c, int x, int y) : tipus(t), color(c), posX(x), posY(y) {}

	void setTipus(TipusFigura tipusFigura) { tipus = tipusFigura; };
	void setPosX(int pos) { posX = pos; };
	void setPosY(int pos) { posY = pos; };
	void setMida(int valorMida) { mida = valorMida; };
	void setOrdreGirs(int gir) { ordreGirs = gir; };

	int getOrdreGirs() const { return ordreGirs; };
	TipusFigura getTipus() const { return tipus; }
	ColorFigura getColor() const { return color; }
	int getPosX() const { return posX; }
	int getPosY() const { return posY; }
	int getMida() const { return mida; };
	bool getFormaValor(const int i, const int j) const { return forma[i][j]; };
	void setFormaValor(const int i, const int j, bool color) { forma[i][j] = color; };

	void inicialitzaFigura(TipusFigura tipus);
	void girFigura();
	void transposarMatriu();
	void canviarColumnes();

private:
	TipusFigura tipus;
	ColorFigura color;
	bool forma[MAX_ALCADA][MAX_AMPLADA];
	int mida;
	int posX;
	int posY;
	int ordreGirs;
};