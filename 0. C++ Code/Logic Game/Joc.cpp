#include "joc.h"

Joc::Joc() 
{
	m_tauler.setCursorX(POS_INICIAL_X); //assigna cursor X a posición inicial
	m_tauler.setCursorY(POS_INICIAL_Y); //assigna cursor Y a posición inicial
	m_figuraActual.inicialitzaMatriuFigura(NO_FIGURA);
}

Joc::Joc(TipusFigura forma)
{		
	m_tauler.setCursorX(POS_INICIAL_X);
	m_tauler.setCursorY(POS_INICIAL_Y);

	m_figuraActual.inicialitzaMatriuFigura(forma);
}

bool Joc::detectCollision(const Figura& figura)
{
	bool colisio = false, posActual;
	int taulerX, taulerY, i = 0, j = 0;
	ColorFigura posTauler;

	//comprovem si surt del tauler
	while (!colisio && i < figura.getMida())
	{
		while (!colisio && j < figura.getMida())
		{
			posActual = figura.getValor(i, j);

			//Componente X celda equivalente tauler
			taulerX = m_tauler.getCursorX() - figura.getCentreX() + i;

			//Componente Y celda equivalente tauler
			taulerY = m_tauler.getCursorY() - figura.getCentreY() + j;

			if (((taulerX < 0 || taulerY < 0 || taulerY >= N_COLUMNES || taulerX >= N_FILES) && posActual))
			{
				colisio = true;
			}
			else
			{
				posTauler = m_tauler.getValueColor(taulerX, taulerY);

				// Revisamos si las celdas de las primeras/últimas columnas/filas de la matriz figuraActual se están saliendo del tauler
				// o si hay un 1 en la celda de la figuraActual y hay otra figura en la celda equivalente de la matriz tauler
				if (posActual && posTauler)
				{
					colisio = true;
				}
				else
				{
					j++;
				}
			}
		}
		j = 0;
		i++;
	}

	return colisio;
}

int Joc::baixaFigura()
{
	bool figuraMoguda = false;
	int nFilesComp = -1;
	bool colisio = false;
	borraDibuixa(true); //borrem la figura
	m_tauler.baixarCursor();

	colisio = detectCollision(m_figuraActual);

	if (!colisio)
	{
		figuraMoguda = true;
		borraDibuixa(false); //tornem a dibuixar la figura
	}
	else
	{
		m_tauler.pujarCursor();
		borraDibuixa(false); //tornem a dibuixar la figura
		nFilesComp = eliminaFiles();
	}

	return nFilesComp;
}

bool Joc::mouFigura(int direccio)
{
	DireccioMov dirX;
	if (direccio == 1)
	{
		dirX = MOV_DRE;
	}
	else if (direccio == -1)
	{
		dirX = MOV_ESQ;
	}

	bool figureMoved = false, isColliding = false;

	borraDibuixa(true);

	if (dirX == MOV_ESQ)
	{
		m_tauler.moureesquerraCursor();

		isColliding = detectCollision(m_figuraActual);

		if (!isColliding)
		{
			figureMoved = true;
		}
		else
		{
			// Devolvemos la figura a su posicion original
			m_tauler.mouredretaCursor();
		}
	}
	else if (dirX == MOV_DRE)
	{
		m_tauler.mouredretaCursor(); // Movemos la figura

		isColliding = detectCollision(m_figuraActual);

		if (!isColliding)
		{
			figureMoved = true;
		}
		else
		{
			//tornem la figura a la seva pos original
			m_tauler.moureesquerraCursor();
		}
	}

	borraDibuixa(false); //tornem a dibuixar la figura

	return figureMoved;
}

int Joc::hardDrop()
{
	int collision = baixaFigura();

	while (collision == -1)
	{
		collision = baixaFigura();
	}

	//PlaySound(". /data/Music/clc1.wav", NULL, SND_SYNC);

	return collision;
}

int Joc::eliminaFiles()
{
	bool filaLlena = true;
	int filesEliminades = 0, j = N_COLUMNES - 1;

	//revisem totes las posicions del Tauler
	for (int i = N_FILES - 1; i >= 0; i--)
	{
		while (j >= 0 && filaLlena)
		{
			if (!m_tauler.getValueColor(i, j))
				filaLlena = false;
			else
				j--;
		}
		if (filaLlena)
		{
			filesEliminades++;

			for (int x = i; x > 0; x--)
			{
				for (int y = N_COLUMNES - 1; y >= 0; y--)
					m_tauler.setColor(x, y, m_tauler.getValueColor(x - 1, y));
			}

			for (int y = N_COLUMNES - 1; y >= 0; y--)
				m_tauler.setColor(0, y, COLOR_NEGRE);

			i++;
		}

		j = N_COLUMNES - 1;
		filaLlena = true;
	}

	return filesEliminades;

}

void Joc::calculGir(DireccioGir direccio, Figura& figura)
{
	if (direccio == GIR_HORARI && figura.getForma() != FIGURA_O)
	{
		//girar
		figura.matriuTrasposta();
		figura.matriuColumnesCanviades();

		//recalcular el centre de la figura al tauler
		if (figura.getForma() == FIGURA_I)
		{
			switch (figura.getFormaGir())
			{
			case 0:
				figura.incCentreX();
				m_tauler.baixarCursor();
				break;
			case 1:
				figura.decCentreY();
				m_tauler.moureesquerraCursor();
				break;
			case 2:
				figura.decCentreX();
				m_tauler.pujarCursor();
				break;
			case 3:
				figura.incCentreY();
				m_tauler.mouredretaCursor();
				break;
			default:
				break;
			}
		}
		//actualitzem gir
		if (figura.getFormaGir() < 3)
			figura.setFormaGir(figura.getFormaGir() + 1);
		else
			figura.setFormaGir(0);
	}
	else if (direccio == GIR_ANTI_HORARI && figura.getForma() != FIGURA_O)
	{
		//girar
		figura.matriuColumnesCanviades();
		figura.matriuTrasposta();

		if (figura.getForma() == FIGURA_I)
		{
			switch (figura.getFormaGir())
			{
			case 3:
				figura.incCentreX();
				m_tauler.baixarCursor();
				break;
			case 2:
				figura.incCentreY();
				m_tauler.mouredretaCursor();
				break;
			case 1:
				figura.decCentreX();
				m_tauler.pujarCursor();
				break;
			case 0:
				figura.decCentreY();
				m_tauler.moureesquerraCursor();
				break;
			default:
				break;
			}
		}

		if (figura.getFormaGir() > 0)
			figura.setFormaGir(figura.getFormaGir() - 1);
		else
			figura.setFormaGir(3);
	}
	else if (direccio != GIR_ANTI_HORARI && direccio != GIR_HORARI)
	{
		cout << "Error." << endl;
	}
}

bool Joc::giraFigura(DireccioGir direccio)
{
	bool figureSpinned = false, isColliding = false;
	Figura copiaFiguraGirada;
	int originalCursorX, originalCursorY;
	int i = 0, j = 0;

	//borrem la fig
	borraDibuixa(true);

	copiaFiguraGirada = m_figuraActual;
	originalCursorX = m_tauler.getCursorX();
	originalCursorY = m_tauler.getCursorY();

	//gir copia de la figura
	calculGir(direccio, copiaFiguraGirada);

	//comprobem si colisiona
	isColliding = detectCollision(copiaFiguraGirada);

	//si no colisiona, igualem la copia a la original
	if (!isColliding)
	{
		figureSpinned = true;
		m_figuraActual = copiaFiguraGirada;
	}
	else
	{
		//¡sino, posem els cursors originals
		m_tauler.setCursorX(originalCursorX);
		m_tauler.setCursorY(originalCursorY);
	}

	borraDibuixa(false);

	return figureSpinned;
}

void Joc::borraDibuixa(bool dibuixaoborra)
{
	ColorFigura color;

	//dibuixaoborra=true, eliminem, else dibuixem
	if (dibuixaoborra)
	{
		color = COLOR_NEGRE; //borrem la figura
	}
	else
	{
		color = m_figuraActual.getColor();
	}

	for (int i = 0; i < m_figuraActual.getMida(); i++)
	{
		for (int j = 0; j < m_figuraActual.getMida(); j++)
		{
			if (m_figuraActual.getValor(i, j))
			{
				m_tauler.setColor(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i, 
				m_tauler.getCursorY() - m_figuraActual.getCentreY() + j, 
				color);
			}
		}
	}

}

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;

	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		int formaFigura, color, x, y, formaGir, i = 0, j = 0;
		Punt centre;

		// Leemos datos de la figura a inicializar del fitxer
		fitxer >> formaFigura >> x >> y >> formaGir;

		// Desdibujamos la figura del tauler, en caso de que estuviera dibujada
		borraDibuixa(true);

		// Guardamos los datos leídos
		m_figuraActual.setFormaGir(0);
		m_figuraActual.inicialitzaMatriuFigura(static_cast<TipusFigura>(formaFigura));
		m_tauler.setCursorX(x + m_figuraActual.getCentreX() - 1);
		m_tauler.setCursorY(y + m_figuraActual.getCentreY() - 1);

		// Giramos la figura en caso de que sea necesario
		if (formaGir != 0)
		{
			for (int i = 0; i < formaGir; i++)
			{
				calculGir(GIR_HORARI, m_figuraActual);
			}
		}

		// Leemos datos del tauler a inicializar del fitxer
		fitxer >> color;
		while (!fitxer.eof() && i < N_FILES)
		{
			while (j < N_COLUMNES)
			{
				m_tauler.setColor(i, j, static_cast<ColorFigura>(color));
				fitxer >> color;
				j++;
			}
			j = 0;
			i++;
		}

		fitxer.close();

		borraDibuixa(false);
	}
}

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;

	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				fitxer << m_tauler.getValueColor(i, j);
				if (j < N_COLUMNES - 1)
				{
					fitxer << " ";
				}
			}
			if (i < N_FILES - 1)
			{
				fitxer << endl;
			}
		}

		fitxer.close();
	}
}

void Joc::escriuTaulerConsola(bool showCursor)
{
	int minX, minY, maxX, maxY;

	minX = m_tauler.getCursorX() - m_figuraActual.getCentreX();
	minY = m_tauler.getCursorY() - m_figuraActual.getCentreY();
	maxX = minX + m_figuraActual.getMida() - 1;
	maxY = minY + m_figuraActual.getMida() - 1;

	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			if ((i >= minX && i <= maxX) && (j >= minY && j <= maxY))
			{
				if (i == m_tauler.getCursorX() && j == m_tauler.getCursorY())
				{
					if (showCursor)
					{
						cout << "X ";
					}
					else
					{
						cout << m_figuraActual.getColor() << " ";
					}
				}
				else if (m_figuraActual.getValor(i - minX, j - minY))
				{
					cout << m_figuraActual.getColor() << " ";
				}
				else
				{
					cout << m_tauler.getValueColor(i, j) << " ";
				}
			}
			else
			{
				cout << m_tauler.getValueColor(i, j) << " ";
			}
		}
		cout << endl;
	}
}

int randomNumber(int numMin, int numMax)
{
	int numAleatori;
	numAleatori = numMin + (rand() % (numMax - numMin + 1));
	return numAleatori;
}

void Joc::generarFig(int tipusFigura, int posFil, int posCol, int gir)
{
	TipusFigura nombreFigura = static_cast<TipusFigura>(tipusFigura);
	m_figuraActual.inicialitzaMatriuFigura(nombreFigura);
	m_tauler.setCursorX(posFil);
	m_tauler.setCursorY(posCol);
}