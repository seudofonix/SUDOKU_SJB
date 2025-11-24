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
#include "tiempo.h" // incluimos el tiempo

// NUEVAS VARIABLES PARA VIDAS
int vidasRestantes = 3;
int puntuacionActual = 1500;

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
                        case ESTADO_GAME_OVER:  // NUEVO CASO
                            manejarClickGameOver(event.button.x, event.button.y);
                            break;
                        default: break;
                    }
                }
            }
        }

        if (estadoActual == ESTADO_SALIR) running = 0;
        
		if (estadoActual == ESTADO_JUGANDO) {
    		// Actualizar el tiempo transcurrido usando la nueva función
    		actualizarTiempo();
            
            //Verificar si se quedó sin vidas durante el juego
            if (vidasRestantes == 0) {
                estadoActual = ESTADO_GAME_OVER;
            }
        }

        // LOGICA DE VICTORIA (Modificada)
        if (estadoActual == ESTADO_JUGANDO && esJuegoCompleto()) {
            
		// Calcular puntaje FINAL considerando tiempo y vidas
    	int puntosFinal = calcularPuntaje(tiempoTranscurrido);
    
   		// Aplicar penalización por vidas perdidas
    	int vidasPerdidas = 3 - vidasRestantes;
    	puntosFinal -= vidasPerdidas * 100; // 100 puntos por vida perdida
    
    	// Asegurar que no sea negativo
    	if (puntosFinal < 0) puntosFinal = 0;
    
    	// CORREGIR: Llamar sin el parámetro tiempo
    	guardarPuntaje(nombreJugador, puntosFinal);
    
    	// Actualizar variables para mostrar en el menu despues
    	strcpy(ultimoJugador, nombreJugador);
    	ultimoPuntaje = puntosFinal;

    	// Mostrar Pantalla de Victoria momentanea
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
                dibujarMenuPrincipal(renderer);
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
            case ESTADO_GAME_OVER:  // NUEVO CASO
                dibujarGameOver(renderer);
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
