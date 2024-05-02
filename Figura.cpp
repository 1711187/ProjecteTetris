#include "Figura.h"

void Figura::transposarMatriu()
{
    int temp;
    for (int i = 0; i < MAX_ALCADA; i++)
    {

        for (int j = i + 1; j < MAX_AMPLADA; j++) // Con j = i + 1 solo pillas los valores por encima de la diagonal
        {
            temp = forma[i][j];
            forma[i][j] = forma[j][i];
            forma[j][i] = temp; //temp es para quie no se duplique
        }
    }
}

void Figura::canviarColumnes()
{
    int temp;

    for (int j = 0; j < mida / 2; j++) //solo nos interesa mirar la primerea mitad, ya que si cogemos toda la matriz, esta volvera a cambiar las columnas y es como si no hubieramos hecho nada
    {
        for (int i = 0; i < MAX_ALCADA; i++)
        {
            temp = forma[i][j];
            forma[i][j] = forma[i][mida - 1 - j];
            forma[i][mida - 1 - j] = temp;
        }
    }
}



void Figura::inicialitzaFigura(TipusFigura tipus)
{
    for (int i = 0; i < MAX_ALCADA; i++)
    {
        for (int j = 0; j < MAX_AMPLADA; j++)
        {
            setFormaValor(i, j, matriuInicialitzadora[tipus][i][j]);
        }
    }
    ordreGirs = 0;
    mida = 3;
    posX = 1;
    posY = 1;

    switch (tipus)
    {
    case NO_FIGURA:
        color = NO_COLOR;
        break;
    case FIGURA_O:
        color = COLOR_GROC;
        mida = 2;
        break;
    case FIGURA_I:
        color = COLOR_BLAUCEL;
        mida = 4;
        posX = 1;
        posY = 2;
        break;
    case FIGURA_T:
        color = COLOR_MAGENTA;
        break;
    case FIGURA_L:
        color = COLOR_TARONJA;
        break;
    case FIGURA_J:
        color = COLOR_BLAUFOSC;
        break;
    case FIGURA_Z:
        color = COLOR_VERMELL;
        break;
    case FIGURA_S:
        color = COLOR_VERD;
        break;
    default:
        break;
    }
}

Figura::Figura()
{
    tipus = NO_FIGURA;
    color = NO_COLOR;
    ordreGirs = 0;
    posX = 0;
    posY = 0;
    mida = 1;
}

