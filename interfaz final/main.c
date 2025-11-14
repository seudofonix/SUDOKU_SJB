#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tablero.h"
#include "graficos.h"
#include "menu.h"

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
    SDL_Window* window = SDL_CreateWindow("SUDOKU MASTER", 
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
    
    // INICIALIZAR JUEGO (pero no mostrar hasta que el usuario pulse JUGAR)
    srand(time(NULL));
    llenarTableroNivelFacil();
    printf("Tablero 9x9 generado.\n");
    
    int running = 1;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Manejar clics según el estado actual
                    switch (estadoActual) {
                        case ESTADO_MENU:
                            manejarClickMenu(event.button.x, event.button.y);
                            break;
                        case ESTADO_INSTRUCCIONES:
                            manejarClickInstrucciones(event.button.x, event.button.y);
                            break;
                        case ESTADO_JUGANDO:
                            manejarClick(event.button.x, event.button.y);
                            break;
                    }
                }
            }
        }
        
        // Verificar si hay que salir
        if (estadoActual == ESTADO_SALIR) {
            running = 0;
            continue;
        }
        
        // FONDO
        SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
        SDL_RenderClear(renderer);
        
        // Dibujar según el estado actual
        switch (estadoActual) {
            case ESTADO_MENU:
                dibujarMenuPrincipal(renderer);
                break;
            case ESTADO_INSTRUCCIONES:
                dibujarInstrucciones(renderer);
                break;
            case ESTADO_JUGANDO:
                dibujarTableroGrafico(renderer);
                break;
        }
        
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
