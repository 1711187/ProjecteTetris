#include <iostream>
#include "Figura.h"

using namespace std;


void Figura::matriuColumnesCanviades() //funcio que canvia les col·lumnes, es part dels girs de la figura
{
	for (int j = 0; j < m_mida / 2; j++)
	{
		for (int i = 0; i < m_mida; i++)
		{
			if (m_figura[i][j] != m_figura[i][m_mida - 1 - j])
			{
				swap(m_figura[i][j], m_figura[i][m_mida - 1 - j]);
			}
		}
	}
}

void Figura::matriuTrasposta() //aquesta funcio transposa la matriu per acabar de girar la figura (depén de la direccio del gir)
{
	for (int i = 0; i < m_mida; i++)
	{
		for (int j = i + 1; j < m_mida; j++)
		{
			if (m_figura[i][j] != m_figura[j][i])
			{
				swap(m_figura[i][j], m_figura[j][i]);
			}
		}
	}
}

void Figura::inicialitzaMatriuFigura(TipusFigura forma)
{
	m_forma = forma;
	m_mida = 3; //inicialitzem la mida y el centre al cas de les figures 3x3, després, depenent de la figura, editarem aquests atributs
	m_centre.setX(1);
	m_centre.setY(1);

	//onicialitzem tota la matriu a zeros
	for (int i = 0; i < MAX_MIDA_FIGURA; i++)
	{
		for (int j = 0; j < MAX_MIDA_FIGURA; j++)
		{
			m_figura[i][j] = 0;
		}
	}

	//assignem els atributs anteriorment mencionats depenent de la figura
	switch (forma)
	{
	case NO_FIGURA:
		m_color = NO_COLOR;
		break;
	case FIGURA_O:
		m_color = COLOR_GROC;
		m_mida = 2;
		break;
	case FIGURA_I:
		m_centre.setY(2);
		m_color = COLOR_BLAUCEL;
		m_mida = 4;
		break;
	case FIGURA_T:
		m_color = COLOR_MAGENTA;
		break;
	case FIGURA_L:
		m_color = COLOR_TARONJA;
		break;
	case FIGURA_J:
		m_color = COLOR_BLAUFOSC;
		break;
	case FIGURA_Z:
		m_color = COLOR_VERMELL;
		break;
	case FIGURA_S:
		m_color = COLOR_VERD;
		break;

	default:
		//missatge d'error en el cas de que hi hagui un problema
		cout << "Error en el constructor amb paràmetres de la classe Figura. S'ha introduit una figura invalida." << endl;
		break;
	}

	if (forma != NO_FIGURA)
	{
		//posem els quatre blocs depenemt de la figura
		int quadratsPlens = 0;
		int posInicialArray = 0;

		for (int i = 0; i < m_mida; i++)
		{
			for (int j = 0; j < m_mida; j++)
			{
				if ((ESTAT_INICIAL_FIGURES[static_cast<int>(forma) - 1][posInicialArray] && quadratsPlens < BLOCS_PER_FIGURA)) //static cast fa la conversio de les dades m
				{
					m_figura[i][j] = 1;
					quadratsPlens++;
				}
				else if (!(posInicialArray < BLOCS_PER_FIGURA) && quadratsPlens < BLOCS_PER_FIGURA)
				{
					m_figura[i][j] = 1;
					quadratsPlens++;
				}

				if (posInicialArray< BLOCS_PER_FIGURA)
				{
					posInicialArray++;
				}
			}
		}
	}
	
}

Figura::Figura()
{
	m_forma = NO_FIGURA;
	m_color = NO_COLOR;
	m_formaGir = 0;
	m_centre.setX(1);
	m_centre.setY(1);
	m_mida = 3;

	for (int i = 0; i < MAX_MIDA_FIGURA; i++)
	{
		for (int j = 0; j < MAX_MIDA_FIGURA; j++)
		{
			m_figura[i][j] = 0;
		}
	}
}

Figura::Figura(TipusFigura forma, ColorFigura color) 
{ 
	m_forma = forma; 
	m_color = color;
	m_formaGir = 0;
	m_centre.setX(1);
	m_centre.setY(1);
	
	inicialitzaMatriuFigura(forma);
}

void Figura::mostraFigura() const
{
	for (int i = 0; i < m_mida; i++)
	{
		for (int j = 0; j < m_mida; j++)
		{
			if (m_figura[i][j])
				cout << m_color << " ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
}
