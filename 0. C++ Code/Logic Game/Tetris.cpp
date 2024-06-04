#include "Tetris.h"
#include "InfoJoc.h"
#include <fstream>

int Tetris::juga(Screen& pantalla, double deltaTime, bool testMode, bool& gameOver, const string& fitxerFigures, const string& fitxerMoviments)
{
    gameOver = m_partida.actualitza(testMode, deltaTime, fitxerFigures, fitxerMoviments);

    return m_partida.getPuntuacio();
}

void Tetris::mostraPuntuacions(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        string jugador;
        int punts;
        int quantitat = 1;
        cout << "======================" << endl;
        cout << "        TOP 5        " << endl << endl;
        fitxer >> jugador >> punts;
        while (!fitxer.eof())
        {
            cout << quantitat << ".- " << jugador << " " << punts << endl;
            fitxer >> jugador >> punts;
            quantitat++;
        }
        cout << endl << "======================" << endl;

        fitxer.close();
    }
}

void Tetris::actualitzaPuntuacions(const string& nomFitxer, int punts)
{
    string user;

    if (m_listPuntuacions.size() < LIST_SIZE || 
        punts > m_listPuntuacions.front().getPoints())
    {
        cout << "Ingrese su usuario: " << endl;
        cin >> user;

        Score newScore(punts, user);

        if (!(m_listPuntuacions.size() < LIST_SIZE))
        {
            m_listPuntuacions.pop_front();
        }
        m_listPuntuacions.push_front(newScore);
        m_listPuntuacions.sort(std::greater<Score>());

        ofstream fitxer;

        fitxer.open(nomFitxer);

        if (fitxer.is_open())
        {
            std::list<Score>::iterator aux = m_listPuntuacions.begin();
            while (aux != m_listPuntuacions.end())
            {
                fitxer << aux->getUser() << " " << aux->getPoints() << endl;
                aux++;
            }

            fitxer.close();
        }
    }
    


}

void Tetris::inicialitzaPuntuacions(const string& nomFitxer)
{
    ifstream fitxer;

    fitxer.open(nomFitxer);

    if (fitxer.is_open())
    {
        Score newScore;
        string user;
        int punts;

        fitxer >> user >> punts;
        while (!fitxer.eof())
        {
            newScore.setUser(user);
            newScore.setPoints(punts);

            m_listPuntuacions.push_front(newScore);

            fitxer >> user >> punts;
        }

        fitxer.close();
    }
}

void Tetris::vaciaListPuntuacions()
{
    m_listPuntuacions.erase(m_listPuntuacions.begin(), m_listPuntuacions.end());
}