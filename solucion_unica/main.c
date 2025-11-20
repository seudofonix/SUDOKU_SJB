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
    //crearTablero();
    //printf("Sistema listo.\n");
    
    // Variables del bucle principal
    int running = 1;
    SDL_Event event;
    estadoActual = ESTADO_MENU; // Empezamos en menú

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            // Lógica de inputs según estado
            if (estadoActual == ESTADO_INGRESO_NOMBRE) {
                manejarEscrituraNombre(&event); // Detecta Enter para ir a JUGANDO
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    switch (estadoActual) {
                        case ESTADO_MENU:
                            manejarClickMenu(event.button.x, event.button.y);
                            // Nota: manejarClickMenu cambia estado a INGRESO_NOMBRE
                            break;
                        case ESTADO_JUGANDO:
                            manejarClick(event.button.x, event.button.y);
                            break;
                        case ESTADO_RANKING:
                            manejarClickRanking(event.button.x, event.button.y);
                            break;
                        case ESTADO_INSTRUCCIONES:
                            manejarClickInstrucciones(event.button.x, event.button.y);
                            break;
                        default: break;
                    }
                }
            }
        }

        if (estadoActual == ESTADO_SALIR) running = 0;

        // LOGICA DE VICTORIA (Modificada)
        if (estadoActual == ESTADO_JUGANDO && esJuegoCompleto()) {
            
            // 1. Calcular puntaje (ejemplo)
            // int puntos = calcularPuntaje(tiempo); 
            int puntos = 1500; // Valor ejemplo, usa tu lógica de tiempo

            // 2. Guardar AUTOMÁTICAMENTE (Ya tenemos el nombre del inicio)
            guardarPuntaje(nombreJugador, puntos);
            
            // 3. Actualizar variables para mostrar en el menú después
            strcpy(ultimoJugador, nombreJugador);
            ultimoPuntaje = puntos;

            // 4. Mostrar Pantalla de Victoria momentánea
            dibujarPantallaVictoria(renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(2000); // Esperar 2 segundos para que vea que ganó

            // 5. Ir directo al Ranking
            estadoActual = ESTADO_RANKING;
        }

        // DIBUJADO
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (estadoActual) {
            case ESTADO_MENU:
                dibujarMenuPrincipal(renderer); // Ahora muestra el último puntaje
                break;
            case ESTADO_INGRESO_NOMBRE:
                dibujarIngresoNombre(renderer);
                break;
            case ESTADO_JUGANDO:
                SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
                SDL_RenderClear(renderer);
                dibujarTableroGrafico(renderer);
                break;
            case ESTADO_RANKING:
                dibujarRanking(renderer);
                break;
            case ESTADO_INSTRUCCIONES:
                dibujarInstrucciones(renderer);
                break;
        }

        SDL_RenderPresent(renderer);
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
