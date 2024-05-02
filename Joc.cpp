#include <iostream>
#include <fstream>
#include <string>
#include "Joc.h"
#include "Tauler.h"
#include "Figura.h"

using namespace std;

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);

	int x, y, gir, forma, color;

	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			m_tauler.setPosition(i, j, COLOR_NEGRE);
		}
	}
	m_figura.setOrdreGirs(0);

	if (fitxer.is_open())
	{
		fitxer >> forma >> x >> y >> gir;

		m_figura.setTipus(canviDeBase[forma]);
		m_figura.inicialitzaFigura(m_figura.getTipus());
		m_tauler.setPosX(x);
		m_tauler.setPosY(y);

		if (gir != 0)
		{
			for (int i = 0; i < gir; i++)
			{
				calculGir(GIR_HORARI, m_figura);
			}
		}

		m_figura.setOrdreGirs(gir);

		if (m_figura.getTipus() == FIGURA_I)
		{
			m_tauler.setPosX(x + m_figura.getPosX() - 1);
			m_tauler.setPosY(y + m_figura.getPosY() - 1);
		}

		int i = 0, j = 0;

		fitxer >> color;
		while (!fitxer.eof() && i < MAX_FILA)
		{
			while (j < MAX_COL)
			{
				m_tauler.setPosition(i, j, canviDeColor[color]);
				fitxer >> color;
				j++;
			}
			j = 0;
			i++;
		}
		fitxer.close();

		posarFigura();
	}
}

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer << m_tauler.getPositionColor(i, j);
				if (j < MAX_COL - 1)
				{
					fitxer << " ";
				}
			}
			if (i < MAX_FILA - 1)
			{
				fitxer << endl;
			}
		}
		fitxer.close();
	}
}

int Joc::eliminarFila()
{
	int cont = 0;
	int j = 0;
	bool liniaCompletada = true;
	for (int i = MAX_FILA - 1; i >= 0; i--)
	{
		while (j < MAX_COL&& liniaCompletada)
		{
			if (m_tauler.getPositionColor(i, j) == false)
			{
				liniaCompletada = false;
			}
			j++;
		}
		if (liniaCompletada)
		{
			cont++;
			for (int x = i; x > 0; x--)
			{
				for (j = 0; j < MAX_COL; j++)
				{
					m_tauler.setPosition(x, j, m_tauler.getPositionColor(x - 1, j));
				}
			}


			for (j = 0; j < MAX_COL; j++)
			{
				m_tauler.setPosition(0, j, COLOR_NEGRE);
			}

			i++;
		}


		j = 0;
		liniaCompletada = true;
	}
	return cont;
}

bool Joc::mouFigura(int dirX)
{
	int posX = m_figura.getPosX();
	int posY = m_figura.getPosY();

	bool potMoure = true;

	borrarFigura();

	// dirX == -1 Esquerra
	// dirX == 1 Dreta

	int i = 0, j = 0, filesCompletes = 0;


	while (potMoure && i < m_figura.getMida())
	{
		while (potMoure && j < m_figura.getMida())
		{
			if ((m_figura.getFormaValor(i, j) == true && //revisamos si hay un 1 en la matriz
				(m_tauler.getPosY() - m_figura.getPosY() + j + dirX >= MAX_COL ||
					m_tauler.getPosY() - m_figura.getPosY() + j + dirX < 0)) || //y si nos estamos saliendo del tauler
				(m_figura.getFormaValor(i, j) == true && //o revisamos si hay un 1 en la matriz
					m_tauler.getPositionColor(m_tauler.getPosX() - m_figura.getPosX() + i, m_tauler.getPosY() - m_figura.getPosY() + j + dirX))) //y si la casilla izq de la casilla equivalente
			{																															//de la figura en el tauler esta llena
				potMoure = false;
			}
			j++;
		}
		j = 0;
		i++;
	}


	if (potMoure)
	{
		m_tauler.setPosY(m_tauler.getPosY() + dirX); //x es una mena de i, i la y es una mena de j
	}

	posarFigura();

	return potMoure;
}

int Joc::baixaFigura()
{
	bool potBaixar = true;
	int i = 0, j = 0, filesCompletes = 0;

	borrarFigura();

	while (potBaixar && i < m_figura.getMida())
	{
		while (potBaixar && j < m_figura.getMida())
		{
			if (m_figura.getFormaValor(i, j) == true && //revisamos si hay un 1 en la casilla de matriz figura
				m_tauler.getPositionColor(m_tauler.getPosX() - m_figura.getPosX() + i + 1, m_tauler.getPosY() - m_figura.getPosY() + j)) //revisamos si la casilla debajo de la casilla equivalente
			{																															//de la figura en el tauler esta llena
				potBaixar = false;
			}
			j++;
		}
		j = 0;
		i++;
	}

	if (potBaixar)
	{
		m_tauler.setPosX(m_tauler.getPosX() + 1);
		posarFigura();
	}
	else
	{
		posarFigura();
		filesCompletes = eliminarFila();
	}




	return filesCompletes;
}

void Joc::calculGir(DireccioGir direccio, Figura& figura)
{
	if (direccio == GIR_HORARI)
	{
		figura.transposarMatriu();
		figura.canviarColumnes();

		if (figura.getOrdreGirs() < 3)
		{
			figura.setOrdreGirs(figura.getOrdreGirs() + 1);
		}
		else
		{
			figura.setOrdreGirs(0);
		}
	}
	else
	{
		figura.canviarColumnes();
		figura.transposarMatriu();

		if (figura.getOrdreGirs() > 0)
		{
			figura.setOrdreGirs(figura.getOrdreGirs() - 1);
		}
		else
		{
			figura.setOrdreGirs(3);
		}
	}

	if (figura.getTipus() == FIGURA_I)
	{
		switch (figura.getOrdreGirs())
		{
		case 0:
			figura.setPosX(1);
			figura.setPosY(2);

			if (direccio == GIR_HORARI)
			{
				m_tauler.setPosX(m_tauler.getPosY() + 1);
			}
			else
				m_tauler.setPosX(m_tauler.getPosX() - 1);

			break;
		case 1:
			figura.setPosX(2);
			figura.setPosY(2);
			if (direccio == GIR_HORARI)
			{
				m_tauler.setPosX(m_tauler.getPosX() + 1);
			}
			else
				m_tauler.setPosX(m_tauler.getPosY() - 1);
			break;
		case 2:
			figura.setPosX(2);
			figura.setPosY(1);
			if (direccio == GIR_HORARI)
			{
				m_tauler.setPosX(m_tauler.getPosY() - 1);
			}
			else
				m_tauler.setPosX(m_tauler.getPosX() + 1);
			break;
		case 3:
			figura.setPosX(1);
			figura.setPosY(1);
			if (direccio == GIR_HORARI)
			{
				m_tauler.setPosX(m_tauler.getPosX() - 1);
			}
			else
				m_tauler.setPosY(m_tauler.getPosY() - 1);
			break;
		}
	}
}

bool Joc::giraFigura(DireccioGir direccio)
{
	Figura figura;
	bool potGirar = true;
	int i = 0, j = 0;

	borrarFigura();

	int cursorX = m_tauler.getPosX();
	int cursorY = m_tauler.getPosY();

	figura = m_figura;
	calculGir(direccio, figura);

	while (potGirar && i < figura.getMida())
	{
		while (potGirar && j < figura.getMida())
		{
			if ((figura.getFormaValor(i, j) == true && //revisamos si hay un 1 en la matriz
				(m_tauler.getPosY() - figura.getPosY() + j >= MAX_COL ||
					m_tauler.getPosY() - figura.getPosY() + j < 0 ||
					m_tauler.getPosX() - figura.getPosX() + i >= MAX_FILA ||
					m_tauler.getPosX() - figura.getPosX() + i < 0)) || //y si nos estamos saliendo del tauler por cualquier lado
				(figura.getFormaValor(i, j) == true && //revisamos si hay un 1 en la casilla de matriz figura
					m_tauler.getPositionColor(m_tauler.getPosX() - figura.getPosX() + i, m_tauler.getPosY() - figura.getPosY() + j))) //revisamos si la casilla equivalente
			{																															//de la figura en el tauler esta llena
				potGirar = false;
			}
			j++;
		}
		j = 0;
		i++;
	}

	if (potGirar == true)
	{
		m_figura = figura;
	}
	else if (potGirar == false)
	{
		m_tauler.setPosX(cursorX);
		m_tauler.setPosY(cursorY);
	}

	posarFigura();

	return potGirar;
}

void Joc::posarFigura()
{
	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			if (m_figura.getFormaValor(i, j) == true)
			{
				m_tauler.setPosition(m_tauler.getPosX() - m_figura.getPosX() + i, m_tauler.getPosY() - m_figura.getPosY() + j, m_figura.getColor());
			}
		}
	}
}

void Joc::borrarFigura()
{
	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			if (m_figura.getFormaValor(i, j) == true)
			{
				m_tauler.setPosition(m_tauler.getPosX() - m_figura.getPosX() + i, m_tauler.getPosY() - m_figura.getPosY() + j, COLOR_NEGRE);
			}
		}
	}
}


Joc::Joc()
{
	m_tauler.setPosX(0);
	m_tauler.setPosY(0);
	fiPartida = false;
}


