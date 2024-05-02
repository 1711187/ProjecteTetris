#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
	Tauler();

	void setPosX(const int pos) { posX = pos; };
	void setPosY(const int pos) { posY = pos; };
	void setPosition(const int posX, const int posY, const ColorFigura valueColor) { taulerJoc[posX][posY] = valueColor; };

	ColorFigura getPositionColor(const int i, const int j) const { return taulerJoc[i][j]; };
	int getPosX() const { return posX; };
	int getPosY() const { return posY; };

private:
	ColorFigura taulerJoc[MAX_FILA][MAX_COL];
	int posX;
	int posY;
};

ostream& operator<<(ostream& out, const Tauler& partida);


#endif