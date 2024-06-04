#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include <windows.h>

Partida::Partida()
{
    srand(time(NULL));
    m_puntuacio = 0;
    m_nivell = 1;
    m_temps = 0;
}

void Partida::inicialitza(bool testMode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    m_puntuacio = 0;
    m_nivell = 1;
    m_temps = 0;
    m_joc.vaciarTauler();

    if (testMode)
    {
        m_joc.inicialitza(fitxerInicial);

        int array[MAX_VALORS_NODE] = {};
        ifstream fitxer;

        // Leemos los movimientos del archivo y los guardamos en la cola
        fitxer.open(fitxerMoviments);

        if (fitxer.is_open())
        {
            fitxer >> array[0];

            while (!fitxer.eof())
            {
                testMoviments.afegeix(array, 1);
                fitxer >> array[0];
            }

            fitxer.close();
        }

        // Leemos las figuras del archivo y las guardamos en la cola
        fitxer.open(fitxerFigures);

        if (fitxer.is_open())
        {

            while (!fitxer.eof())
            {
                for (int i = 0; i < MAX_VALORS_NODE; i++)
                    fitxer >> array[i];

                testFigures.afegeix(array, MAX_VALORS_NODE);
            }

            fitxer.close();
        }
    }
    else
    {
        // Generamos una figura aleatoria
        m_joc.generarFig(randomNumber(1, 7), POS_INICIAL_X, POS_INICIAL_Y, 0);

        m_joc.borraDibuixa(false);
    }
}

void Partida::mostraTauler()
{
    ColorFigura colorTauler;
    //inicialitzem el tauler
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);
    //mostrem per pantalla el nivell actual del joc i els punts del jugador
    string msgLvl = "Nivell: " + to_string(m_nivell);
    string msgPunt = "Puntuacio: " + to_string(m_puntuacio);
    GraphicManager::getInstance()->drawFont(RETRO_FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 70, 0.5, msgLvl);
    GraphicManager::getInstance()->drawFont(RETRO_FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 0.5, msgPunt);

    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            colorTauler = m_joc.getTauler(i, j);

            if (colorTauler != COLOR_NEGRE)
            {
                GraphicManager::getInstance()->drawSprite(static_cast<IMAGE_NAME>(static_cast<int>(colorTauler) + 1),
                    POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
            }

        }
    }
}

bool Partida::actualitza(bool testMode, double deltaTime, const string& fitxerFigures, const string& fitxerMoviments)
{
    int returnColisio = -1;
    bool final = false;
    double speed;

    // Dibujamos el estado actual del tauler
    mostraTauler();
    
    // Bajamos la figura automaticamente dependiendo de la velocidad del nivel
    m_temps += deltaTime;
    speed = (3.0 / (m_nivell + 2));
    if (m_temps > speed && !testMode)
    {
        returnColisio = m_joc.baixaFigura();
        m_temps = 0.0;
    }

    // Leemos los movimientos de las figuras dependiendo del modo de juego
    if (!testMode)
    {
        if (Keyboard_GetKeyTrg(KEYBOARD_UP) || Keyboard_GetKeyTrg(KEYBOARD_W))
            m_joc.giraFigura(GIR_HORARI);

        if (Keyboard_GetKeyTrg(KEYBOARD_DOWN) || Keyboard_GetKeyTrg(KEYBOARD_S))
            m_joc.giraFigura(GIR_ANTI_HORARI);

        if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT) || Keyboard_GetKeyTrg(KEYBOARD_D))
            m_joc.mouFigura(1);

        if (Keyboard_GetKeyTrg(KEYBOARD_LEFT) || Keyboard_GetKeyTrg(KEYBOARD_A))
            m_joc.mouFigura(-1);

        if (Keyboard_GetKeyTrg(KEYBOARD_Z) || Keyboard_GetKeyTrg(KEYBOARD_P))
        {
            returnColisio = m_joc.baixaFigura();
            m_puntuacio++;
        }


        if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
        {
            m_puntuacio += N_FILES - m_joc.getCursor().getY();
            returnColisio = m_joc.hardDrop();
        }
    }
    else
    {
        TipusTecla tecla = NO_TECLA;

        if (testMoviments.size())
        {
            tecla = static_cast<TipusTecla>(testMoviments.getPrimer()->getValor(0)); //convertim el valor del fitxer a la tecla pressionada
            testMoviments.treure();
        }
        switch (tecla)
        {
        case TECLA_ESQUERRA:
            m_joc.mouFigura(-1);
            break;
        case TECLA_DRETA:
            m_joc.mouFigura(1);
            break;
        case TECLA_AMUNT:
            m_joc.giraFigura(GIR_HORARI);
            break;
        case TECLA_ABAIX:
            m_joc.giraFigura(GIR_ANTI_HORARI);
            break;
        case TECLA_ESPAI:
            returnColisio = m_joc.baixaFigura();
            m_puntuacio++;
            break;
        case TECLA_ESCAPE:
            returnColisio = m_joc.hardDrop();
            break;
        default:
            break;
        }

        if (testMoviments.empty())
        {
            final = true;
        }
        Sleep(1000);
    }
    

    
    //detectamos si una figura ha colisionado
    if (returnColisio != -1)
    {
        //calculamos el aumento de puntuacion
        if (returnColisio == 0)
        {
            m_puntuacio += 50;
        }
        else
        {
            m_puntuacio += 100 * returnColisio;
        }
        m_puntuacio += m_nivell * 10;

        if (!testMode)
        {
            //en el cas en el que no estem en el mode test, generem una figura random
            m_joc.generarFig(randomNumber(1, NUM_DE_FIGURES), POS_INICIAL_X, POS_INICIAL_Y, 0);
        }
        else
        {
            //en el cas en el que estem en el mode test, llegim en ordre
            int fig, posY, posX, gir;

            fig = testFigures.getPrimer()->getValor(0); //llegeix el tipus de figura
            posX = testFigures.getPrimer()->getValor(1); // llegeix la posicio x de la figura en el tauler
            posY = testFigures.getPrimer()->getValor(2); //llegeix la posicio y de la figura en el tauler
            gir = testFigures.getPrimer()->getValor(3);//llegeix el gir que ha de fer la figura

            testFigures.treure();

            //Guardando la nueva figura en la matriz de Joc y poniendo el cursor en la posicion siguiente de la cola
            m_joc.generarFig(fig, posX, posY, gir);
            
            m_joc.setCursor(posX + m_joc.getCentre().getX() - 1, posY + m_joc.getCentre().getY() - 1);

            //giramos la figura en caso de que sea necesario
            if (gir != 0)
            {
                Figura copiaFigura = m_joc.getFigura(); //fem una copia de figura perque sigui més facil de manipular
                for (int i = 0; i < gir; i++)
                {
                    m_joc.calculGir(GIR_HORARI, copiaFigura);
                }

                m_joc.setFigura(copiaFigura);
            }
        }

        //detectem si al generar la figura, col·lisiona
        final = m_joc.detectCollision(m_joc.getFigura());

        m_joc.borraDibuixa(false);
    }

    //calculem si el jugador tés els punts necessaris per pujar de nivell
    if (m_puntuacio >= 600 * (m_nivell * m_nivell + 2 * m_nivell + 1)
        && m_nivell < 25) //el maxim nivell del tetris es 25
    {
        m_puntuacio++;
    }

    if (final)
    {

        //imprimim el game over
        GraphicManager::getInstance()->drawSprite(GRAFIC_TRANSPARENT_FONS, 0, 0, false);
        string msgFin = "GAME OVER";
        GraphicManager::getInstance()->drawFont(RETRO_FONT_RED_30, SCREEN_SIZE_X / 8.0, SCREEN_SIZE_Y / 2.0, 1.4, msgFin);

        if (testMode)
        {
            testMoviments.clear();
            testFigures.clear();
        }
    }

    return final;
}
