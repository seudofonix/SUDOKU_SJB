#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "archivos.h"
#include "tablero.h"
#include "graficos.h"

#define FACIL 35
#define NORMAL 20	// La cantidad de celdas a generar dependiendo de la dificultad. 
#define DIFICIL 10

int main(int argc, char* argv[]) {
    printf("Iniciando Sudoku con SDL2...\n");
    
    // INICIALIZAR SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error SDL2: %s\n", SDL_GetError());
        return -1;
    }
    
    // INICIALIZAR GRÁFICOS
    if (!inicializarGraficos()) {
        SDL_Quit();
        return -1;
    }
    
    // CREAR VENTANA
    SDL_Window* window = SDL_CreateWindow("SUDOKU 9x9 - Version Grafica", 
                                         SDL_WINDOWPOS_CENTERED, 
                                         SDL_WINDOWPOS_CENTERED,
                                         WINDOW_WIDTH, 
                                         WINDOW_HEIGHT, 
                                         SDL_WINDOW_SHOWN);
    
    if (!window) {
        printf("Error ventana: %s\n", SDL_GetError());
        limpiarGraficos();
        SDL_Quit();
        return -1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
                                               SDL_RENDERER_ACCELERATED);
    
    printf("¡SDL2 y gráficos inicializados! Ventana grafica abierta.\n");
    
    // INICIALIZAR JUEGO
    srand(time(NULL));
    llenarTablero(80);  // Te lo dejo en 80 para ganar en un movimiento. El chequeo de victoria no funciona de momento asi que hay que revisar eso :p
    printf("Tablero 9x9 generado.\n");
    
    int running = 1;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    manejarClick(event.button.x, event.button.y);
                }
            }
        }
        
        // FONDO
        SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
        SDL_RenderClear(renderer);
        
        // DIBUJAR TABLERO
        dibujarTableroGrafico(renderer);
        
        // ACTUALIZAR PANTALLA
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    // LIMPIAR RECURSOS
    limpiarGraficos();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    printf("Juego terminado.\n");
    return 0;
}
