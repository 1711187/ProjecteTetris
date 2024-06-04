#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "Joc.h"
#include "Cua.h"

using namespace std;

class Partida 
{
public:
    Partida(); //constructors
    int getPuntuacio() const { return m_puntuacio; } //getter de la puntuacio del jugador
    void inicialitza(bool testMode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);//funcio que inicialitza el tauler
    bool actualitza(bool testMode, double deltaTime, const string& fitxerFigures, const string& fitxerMoviments); //funcio que actualitza el tauler 
    void mostraTauler(); //funcio que mostra el estat del tauler
private:
    Cua testFigures;
    Cua testMoviments;
    Joc m_joc;
    bool m_modeTest;
    double m_temps;
    int m_puntuacio;
    int m_nivell;
};

#endif 
