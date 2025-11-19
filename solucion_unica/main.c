#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Incluimos tus headers
#include "archivos.h"
#include "tablero.h"
#include "graficos.h"
#include "menu.h" // <--- Importante: Incluimos el menú

int main(int argc, char* argv[]) {
    printf("Iniciando Sudoku Master...\n");
    
    // --- 1. INICIALIZACIÓN DE SDL Y SISTEMAS ---
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error SDL2: %s\n", SDL_GetError());
        return -1;
    }
    
    if (!inicializarGraficos()) {
        SDL_Quit();
        return -1;
    }
    
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
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Inicializar la lógica del tablero (memoria)
    crearTablero();
    printf("Sistema listo.\n");
    
    // Variables del bucle principal
    int running = 1;
    SDL_Event event;
    
    // Nos aseguramos de empezar en el menú
    estadoActual = ESTADO_MENU; 
    
    // --- 2. BUCLE PRINCIPAL DEL JUEGO ---
    while (running) {
        
        // A. MANEJO DE EVENTOS
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } 
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Dependiendo del estado, llamamos a una función de click distinta
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
                            
                        default:
                            break;
                    }
                }
            }
        }

        // Verificar si el menú ordenó salir
        if (estadoActual == ESTADO_SALIR) {
            running = 0;
        }
        
        // B. LOGICA DE VICTORIA (Solo si estamos jugando)
        if (estadoActual == ESTADO_JUGANDO && esJuegoCompleto()) {
             dibujarPantallaVictoria(renderer);
             SDL_RenderPresent(renderer);
             
             // Pequeño bucle de espera para la victoria
             int esperando = 1;
             SDL_Event ev;
             while (esperando && running) {
                 while(SDL_PollEvent(&ev)){
                     if(ev.type == SDL_QUIT){
                         esperando = 0;
                         running = 0;
                     }
                     else if(ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN){
                         esperando = 0; 
                     }
                 }
                 SDL_Delay(10);
             }
             // Al terminar la victoria, volvemos al menú principal
             estadoActual = ESTADO_MENU;
             // Opcional: Aquí podrías llamar a una función para reiniciar el tablero si la tienes
             // crearTablero(); 
        }

        // C. DIBUJADO (RENDER)
        // Limpiamos pantalla (el color de fondo depende de la función de dibujo específica, 
        // pero ponemos uno base por seguridad)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Dibujamos según el estado
        switch (estadoActual) {
            case ESTADO_MENU:
                dibujarMenuPrincipal(renderer);
                break;
                
            case ESTADO_INSTRUCCIONES:
                dibujarInstrucciones(renderer);
                break;
                
            case ESTADO_JUGANDO:
                // Fondo específico del juego
                SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
                SDL_RenderClear(renderer);
                dibujarTableroGrafico(renderer);
                break;
                
            default:
                break;
        }
        
        // Mostrar lo dibujado
        SDL_RenderPresent(renderer);
        
        // Control de FPS (~60 FPS)
        SDL_Delay(16);
    }
    
    // --- 3. LIMPIEZA DE RECURSOS ---
    destruirTablero();
    limpiarGraficos();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    printf("Juego terminado exitosamente.\n");
    return 0;
}
