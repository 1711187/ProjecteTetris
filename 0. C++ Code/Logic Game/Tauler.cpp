#include <iostream>
#include "Tauler.h"

using namespace std;

Tauler::Tauler()
{
	vaciarTauler();

	m_cursor.setX(POS_INICIAL_X);
	m_cursor.setY(POS_INICIAL_Y);
}

Tauler::Tauler(ColorFigura color, int cursorX, int cursorY)
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_tauler[i][j] = color;
		}
	}

	m_cursor.setX(cursorX);
	m_cursor.setY(cursorY);
}

void Tauler::vaciarTauler()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_tauler[i][j] = COLOR_NEGRE;
		}
	}
}