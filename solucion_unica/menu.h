#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Estados del juego
typedef enum {
    ESTADO_MENU,
    ESTADO_INGRESO_NOMBRE,
    ESTADO_JUGANDO,
    ESTADO_RANKING,
    ESTADO_INSTRUCCIONES,
    ESTADO_SALIR,
    ESTADO_GAME_OVER  // NUEVO ESTADO
} EstadoJuego;

// Variable global del estado (se define en menu.c)
extern EstadoJuego estadoActual;
extern char nombreJugador[21];

extern char ultimoJugador[21];
extern int ultimoPuntaje;

// NUEVAS VARIABLES PARA VIDAS
extern int vidasRestantes;
extern int puntuacionActual;

// Funciones del men√∫
void dibujarMenuPrincipal(SDL_Renderer* renderer);
void manejarClickMenu(int x, int y);
void dibujarIngresoNombre(SDL_Renderer* renderer);
void manejarEscrituraNombre(SDL_Event* event); // Ahora inicia el juego
void dibujarRanking(SDL_Renderer* renderer);
void manejarClickRanking(int x, int y);
void dibujarInstrucciones(SDL_Renderer* renderer);
void manejarClickInstrucciones(int x, int y);
void dibujarGameOver(SDL_Renderer* renderer);  // NUEVA FUNCI”N
void manejarClickGameOver(int x, int y);       // NUEVA FUNCI”N

#endif
