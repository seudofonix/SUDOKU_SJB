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
#include "menu.h" //  Incluimos el menu

// ---- TEMPORIZADOR ---- 
Uint32 tiempoInicio = 0;        // momento en que empieza la partida
double tiempoTranscurrido = 0;  // segundos que lleva la partida



int main(int argc, char* argv[]) {
    printf("Iniciando Sudoku Master...\n");
    
    // --- 1. INICIALIZACION DE SDL Y SISTEMAS ---
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
    
    // Inicializar la logica del tablero (memoria)
    //crearTablero();
    //printf("Sistema listo.\n");
    
    // Variables del bucle principal
    int running = 1;
    SDL_Event event;
    estadoActual = ESTADO_MENU; // Empezamos en menu

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            // logica de inputs segun estado
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
        
		if (estadoActual == ESTADO_JUGANDO) {
            // Milisegundos desde que empezó la partida
            Uint32 msPasados = SDL_GetTicks() - tiempoInicio;

            // Lo pasamos a segundos (double)
            tiempoTranscurrido = msPasados / 1000.0;
        }

        // LOGICA DE VICTORIA (Modificada)
        if (estadoActual == ESTADO_JUGANDO && esJuegoCompleto()) {
            
            // Calcular puntaje (ejemplo)
            // int puntos = calcularPuntaje(tiempo); 
            int puntos = 1500; // Valor ejemplo, usa tu logica de tiempo

            // Guardar AUTOMATICAMENTE (Ya tenemos el nombre del inicio)
            guardarPuntaje(nombreJugador, puntos);
            
            // Actualizar variables para mostrar en el menu despues
            strcpy(ultimoJugador, nombreJugador);
            ultimoPuntaje = puntos;

            //  Mostrar Pantalla de Victoria momentanea
            dibujarPantallaVictoria(renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(2000); // Esperar 2 segundos para que vea que gano

            // Ir directo al Ranking
            estadoActual = ESTADO_RANKING;
        }

        // DIBUJADO
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (estadoActual) {
            case ESTADO_MENU:
                dibujarMenuPrincipal(renderer); // Ahora muestra el ultimo puntaje
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
