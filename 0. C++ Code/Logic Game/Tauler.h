#ifndef TAULER_H
#define TAULER_H

#include "Figura.h"
#include <iostream>

const int N_FILES = 21;
const int N_COLUMNES = 11;
const int POS_INICIAL_X = 1;
const int POS_INICIAL_Y = 5;
const int MAX_FILA = N_FILES;
const int MAX_COL = N_COLUMNES;

class Tauler
{
public:
	//Constructors
	Tauler();
	Tauler(ColorFigura color, int cursorX, int cursorY);

	// Modifying Methods
	void vaciarTauler();
		//Setters
	void setCursorX(int x) { m_cursor.setX(x); };
	void setCursorY(int y) { m_cursor.setY(y); };
	void setColor(int fila, int columna, ColorFigura color) { m_tauler[fila][columna] = color; }

	// Incrementators & decrementators
	void mouredretaCursor() { m_cursor.incY(); };
	void moureesquerraCursor() { m_cursor.decY(); };
	void pujarCursor() { m_cursor.decX(); };
	void baixarCursor() { m_cursor.incX(); };

	// Consulting Methods
		//Getters
	int getCursorX() { return m_cursor.getX(); };
	int getCursorY() { return m_cursor.getY(); };
	Punt getCursor() { return m_cursor; };



	ColorFigura getValueColor(int fila, int columna) const { return m_tauler[fila][columna]; };
private:
	ColorFigura m_tauler[N_FILES][N_COLUMNES];
	Punt m_cursor;
};

#endif