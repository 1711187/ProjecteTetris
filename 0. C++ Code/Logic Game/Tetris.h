#ifndef TETRIS_H
#define TETRIS_H

#include "../Graphic Lib/libreria.h"
#include <conio.h>      /* getch */ 
#include "Partida.h"
#include "Score.h"
#include <list>



class Tetris
{
public:
	void inicialitza(bool testMode, 
		const string& fitxerInicial, 
		const string& fitxerPuntuacions, 
		const string& fitxerFigures, 
		const string& fitxerMoviments)
	{
		m_partida.inicialitza(testMode, fitxerInicial, fitxerFigures, fitxerMoviments);
		inicialitzaPuntuacions(fitxerPuntuacions);
	}
	int juga(Screen& pantalla, double deltaTime, bool testMode, bool& gameOver, 
		const string& fitxerFigures, 
		const string& fitxerMoviments);
	void mostraPuntuacions(const string& nomFitxer);
	void actualitzaPuntuacions(const string& nomFitxer, int punts);
	void inicialitzaPuntuacions(const string& nomFitxer);
	void vaciaListPuntuacions();
private:
	static const int LIST_SIZE = 5;
	std::list<Score> m_listPuntuacions;
	Partida m_partida;
};

#endif