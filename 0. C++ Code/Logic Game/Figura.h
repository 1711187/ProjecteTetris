#ifndef FIGURA_H
#define FIGURA_H

const int MAX_MIDA_FIGURA = 4;
const int NUM_DE_FIGURES = 7;
const int NUM_DE_COLORS = 10;
const int BLOCS_PER_FIGURA = 4;

#include "Punt.h"
#include "InfoJoc.h"

const bool ESTAT_INICIAL_FIGURES[NUM_DE_FIGURES][BLOCS_PER_FIGURA] = //inicialitza la matriu figura
{
	{1, 1, 1, 1}, //figura del quadrat
	{0, 0, 0, 0}, //figura pal
	{0, 1, 0, 1}, //figura t
	{0, 0, 1, 1}, //figura l
	{1, 0, 0, 1}, //figura j
	{1, 1, 0, 0}, //figura z
	{0, 1, 1, 1}  //figura s 
};

typedef enum
{
	GIR_HORARI = 0,
	GIR_ANTI_HORARI
} DireccioGir;

//typedef enum
//{
//	COLOR_NEGRE = 0,
//	COLOR_GROC,
//	COLOR_BLAUCEL,
//	COLOR_MAGENTA,
//	COLOR_TARONJA,
//	COLOR_BLAUFOSC,
//	COLOR_VERMELL,
//	COLOR_VERD,
//	NO_COLOR
//} ColorFigura;
//
//typedef enum
//{
//	NO_FIGURA = 0,
//	FIGURA_O,
//	FIGURA_I,
//	FIGURA_T,
//	FIGURA_L,
//	FIGURA_J,
//	FIGURA_Z,
//	FIGURA_S,
//} TipusFigura;

//comentem aquests enums perque ens col·lapsa amb la classe figura i altres

class Figura 
{
public:
	//constr i destructors
	Figura();
	Figura(TipusFigura forma, ColorFigura color);

	~Figura() {};

	//metodes de la figura per inicialitzar y pels girs de la figura
	void matriuTrasposta();
	void matriuColumnesCanviades();
	void inicialitzaMatriuFigura(TipusFigura forma);
	//setters
	void setForma(TipusFigura forma) { m_forma = forma; };
	void setFormaGir(int formaGir) { m_formaGir = formaGir; };
	void setColor(ColorFigura color) { m_color = color; };
	//metodes per incrementar o disminuir els centres
	void incCentreX() { m_centre.incX();  };
	void incCentreY() { m_centre.incY(); };
	void decCentreX() { m_centre.decX(); };
	void decCentreY() { m_centre.decY(); };

	//metodes per mostrar la figura actual
	void mostraFigura() const;
	//getters
	TipusFigura getForma() const { return m_forma; };
	ColorFigura getColor() const { return m_color; };
	int getFormaGir() const { return m_formaGir; };
	int getMida() const { return m_mida; };
	bool getValor(int fila, int columna) const { return m_figura[fila][columna]; };
	int getCentreY() const { return m_centre.getY(); };
	int getCentreX() const { return m_centre.getX(); };
	Punt getCentre() { return m_centre; };

private:
	TipusFigura m_forma;
	ColorFigura m_color;
	Punt m_centre;
	bool m_figura[MAX_MIDA_FIGURA][MAX_MIDA_FIGURA];
	int m_mida;
	int m_formaGir;
};




#endif