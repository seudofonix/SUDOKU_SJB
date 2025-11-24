#ifndef GRAFICOS_H
#define GRAFICOS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Constantes gráficas
#define CELL_SIZE 40
#define BOARD_SIZE 9
#define MARGIN_X 50
#define MARGIN_Y 80
#define SIDEBAR_WIDTH 200
#define WINDOW_WIDTH (MARGIN_X * 2 + BOARD_SIZE * CELL_SIZE + SIDEBAR_WIDTH)
#define WINDOW_HEIGHT (MARGIN_Y * 2 + BOARD_SIZE * CELL_SIZE)

// Variables globales de gráficos
extern TTF_Font* font;
extern int numeroSeleccionado;
extern int celdaSeleccionadaFila;
extern int celdaSeleccionadaColumna;

// SOLO DECLARAR como extern (definidas en main.c)
extern int vidasRestantes;
extern int puntuacionActual;

// Funciones de inicialización
int inicializarGraficos();
void limpiarGraficos();

// Funciones de dibujo
void dibujarTextoCentrado(SDL_Renderer* renderer, int x, int y, int w, int h, const char* texto, SDL_Color color);
void dibujarNumeros(SDL_Renderer* renderer);
void dibujarSelectorNumeros(SDL_Renderer* renderer);
void dibujarCeldaSeleccionada(SDL_Renderer* renderer);
void dibujarTableroGrafico(SDL_Renderer* renderer);
void dibujarPantallaVictoria(SDL_Renderer* renderer);
void dibujarBarraVidas(SDL_Renderer* renderer);  // NUEVA FUNCIÓN

// Función de manejo de eventos
void manejarClick(int x, int y);

#endif
