#include "Tauler.h"


Tauler::Tauler()
{
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			taulerJoc[i][j] = COLOR_NEGRE;
		}
	}
}