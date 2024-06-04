//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Tetris.h"
#include "./InfoJoc.h"

// Librerias de la musica
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")

int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);

    Tetris tetris;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    char userOption;
    bool testMode = false, gameOver = false, fin = false;
    int puntuacio;

    mciSendString("open \"./data/Music/song.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);

    do
    {
        // Reinicializacion de variables
        gameOver = false;

        // Menu de la consola
        cout << "    MENU PRINCIPAL    " << endl;
        cout << "======================" << endl;
        cout << "1. Joc en mode normal" << endl;
        cout << "2. Joc en mode test" << endl;
        cout << "3. Mostrar puntuacions" << endl;
        cout << "4. Sortir" << endl;
        cin >> userOption;

        switch (userOption)
        {
        case '1':
            testMode = false;
            fin = false;
            puntuacio = 0;
            break;
        case '2':
            testMode = true;
            break;
        case '3':
            tetris.mostraPuntuacions("./data/Games/puntuacions.txt");
            break;
        case '4':
            cout << "Sortint" << endl;
            break;
        default:
            cout << "Error. Opcio invalida." << endl;
            break;
        }

        if (userOption != '3' && userOption != '4')
        {
            tetris.inicialitza(testMode,
                "./data/Games/partida.txt",
                "./data/Games/puntuacions.txt",
                "./data/Games/figures.txt",
                "./data/Games/moviments.txt");

            mciSendString("play mp3 repeat", NULL, 0, NULL);

            // Bucle principal del juego
            do
            {
                //Mostrem la finestra grafica
                pantalla.show();

                LAST = NOW;
                NOW = SDL_GetPerformanceCounter();
                deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

                // Captura tots els events de ratolí i teclat de l'ultim cicle
                pantalla.processEvents();

                if (!fin)
                {
                    puntuacio = tetris.juga(pantalla, deltaTime, testMode, fin,
                        "./data/Games/figures.txt",
                        "./data/Games/moviments.txt");

                    // Actualitza la pantalla
                    pantalla.update();
                }
                else
                {
                    if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
                    {
                        fin = false;
                        gameOver = true;
                        SDL_HideWindow(g_Video.window);
                    }
                }
                //Sortim del bucle si pressionem ESC
            } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !gameOver);

            if (!fin)
            {
                SDL_HideWindow(g_Video.window);
                mciSendString("stop mp3", NULL, 0, NULL);
            }

            if (!testMode)
            {
                // Actualiza las puntuaciones
                tetris.actualitzaPuntuacions("./data/Games/puntuacions.txt", puntuacio);
                tetris.vaciaListPuntuacions();
            }

            mciSendString("close mp3", NULL, 0, NULL);
        }
        
    } while (userOption != '4');
    

    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}

