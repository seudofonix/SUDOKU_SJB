#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Estados del juego
typedef enum {
    ESTADO_MENU,
    ESTADO_JUGANDO,
    ESTADO_INSTRUCCIONES,
    ESTADO_SALIR
} EstadoJuego;

// Variable global del estado (se define en menu.c)
extern EstadoJuego estadoActual;

// Funciones del menú
void dibujarMenuPrincipal(SDL_Renderer* renderer);
void manejarClickMenu(int x, int y);
void dibujarInstrucciones(SDL_Renderer* renderer);
void manejarClickInstrucciones(int x, int y);

#endif
