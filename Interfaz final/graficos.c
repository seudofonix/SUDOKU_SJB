#include <stdio.h>
#include "graficos.h"
#include "tablero.h"

// Variables globales de gráficos
TTF_Font* font = NULL;
int numeroSeleccionado = 0;
int celdaSeleccionadaFila = -1;
int celdaSeleccionadaColumna = -1;

// Función para inicializar gráficos
int inicializarGraficos() {
    // INICIALIZAR SDL_ttf
    if (TTF_Init() != 0) {
        printf("Error SDL_ttf: %s\n", TTF_GetError());
        return 0;
    }
    
    // CARGAR FUENTE
    font = TTF_OpenFont("arial.ttf", 20);
    if (!font) {
        font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 20);
        if (!font) {
            printf("Error: No se pudo cargar arial.ttf\n");
            return 0;
        }
    }
    
    return 1;
}

// Función para limpiar recursos gráficos
void limpiarGraficos() {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

// Función para dibujar texto centrado
void dibujarTextoCentrado(SDL_Renderer* renderer, int x, int y, int w, int h, const char* texto, SDL_Color color) {
    if (!font) return;
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, texto, color);
    if (!surface) {
        printf("Error creando surface: %s\n", TTF_GetError());
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Error creando texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    
    // Centrar el texto
    SDL_Rect rect = {
        x + (w - surface->w) / 2,
        y + (h - surface->h) / 2,
        surface->w,
        surface->h
    };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void dibujarNumeros(SDL_Renderer* renderer) {
    int i, j;
    
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (tablero[i][j] != 0) {
                // Determinar color según el estado
                SDL_Color color;
                if (tableroEstado[i][j] == 1) {  // Números fijos - NEGRO
                    color = (SDL_Color){0, 0, 0, 255};
                } else if (tableroEstado[i][j] == 2) {  // Usuario correcto - VERDE
                    color = (SDL_Color){0, 255, 0, 255};
                } else if (tableroEstado[i][j] == 3) {  // Usuario incorrecto - ROJO
                    color = (SDL_Color){255, 0, 0, 255};
                } else {  // Por defecto - AZUL
                    color = (SDL_Color){0, 100, 255, 255};
                }
                
                // Dibujar el número como texto
                char numStr[2];
                sprintf(numStr, "%d", tablero[i][j]);
                
                dibujarTextoCentrado(renderer,
                    MARGIN_X + j * CELL_SIZE,
                    MARGIN_Y + i * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE,
                    numStr,
                    color);
            }
        }
    }
}

void dibujarSelectorNumeros(SDL_Renderer* renderer) {
    int i;
    int selectorX = MARGIN_X + BOARD_SIZE * CELL_SIZE + 20;
    int selectorY = MARGIN_Y + 180;
    int numeroSize = 35;
    int spacing = 10;
    
    // Título del selector
    SDL_Rect tituloSelector = {
        selectorX,
        selectorY - 40,
        SIDEBAR_WIDTH - 40,
        30
    };
    SDL_SetRenderDrawColor(renderer, 100, 100, 150, 255);
    SDL_RenderFillRect(renderer, &tituloSelector);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &tituloSelector);
    
    // Texto del título
    SDL_Color colorBlanco = {255, 255, 255, 255};
    dibujarTextoCentrado(renderer, tituloSelector.x, tituloSelector.y, 
                        tituloSelector.w, tituloSelector.h, 
                        "SELECCIONAR", colorBlanco);
    
    // Calcular centrado horizontal
    int totalWidth = 3 * numeroSize + 2 * spacing;
    int startX = selectorX + (SIDEBAR_WIDTH - 40 - totalWidth) / 2;
    
    // Dibujar cuadritos con números del 1 al 9
    for (i = 0; i < 9; i++) {
        SDL_Rect numeroRect = {
            startX + (i % 3) * (numeroSize + spacing),
            selectorY + (i / 3) * (numeroSize + spacing),
            numeroSize,
            numeroSize
        };
        
        // Color del cuadrito
        if (numeroSeleccionado == i + 1) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 200, 200, 220, 255);
        }
        SDL_RenderFillRect(renderer, &numeroRect);
        
        // Borde del cuadrito
        SDL_SetRenderDrawColor(renderer, 100, 100, 150, 255);
        SDL_RenderDrawRect(renderer, &numeroRect);
        
        // Dibujar número como texto
        char numStr[2];
        sprintf(numStr, "%d", i + 1);
        SDL_Color colorNumero = {50, 50, 100, 255};
        dibujarTextoCentrado(renderer, numeroRect.x, numeroRect.y, 
                            numeroRect.w, numeroRect.h, numStr, colorNumero);
    }
    
    // Botón para borrar
    SDL_Rect borrarRect = {
        startX,
        selectorY + 3 * (numeroSize + spacing) + 10,
        totalWidth,
        numeroSize
    };
    
    if (numeroSeleccionado == 0) {
        SDL_SetRenderDrawColor(renderer, 255, 200, 200, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 220, 150, 150, 255);
    }
    SDL_RenderFillRect(renderer, &borrarRect);
    SDL_SetRenderDrawColor(renderer, 150, 50, 50, 255);
    SDL_RenderDrawRect(renderer, &borrarRect);
    
    // Texto del botón borrar
    dibujarTextoCentrado(renderer, borrarRect.x, borrarRect.y, 
                        borrarRect.w, borrarRect.h, "BORRAR", colorBlanco);
}

void dibujarCeldaSeleccionada(SDL_Renderer* renderer) {
    if (celdaSeleccionadaFila != -1 && celdaSeleccionadaColumna != -1) {
        SDL_Rect seleccionRect = {
            MARGIN_X + celdaSeleccionadaColumna * CELL_SIZE + 2,
            MARGIN_Y + celdaSeleccionadaFila * CELL_SIZE + 2,
            CELL_SIZE - 4,
            CELL_SIZE - 4
        };
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &seleccionRect);
        SDL_RenderDrawRect(renderer, &seleccionRect);
    }
}

void dibujarTableroGrafico(SDL_Renderer* renderer) {
    int i, j;
    
    // 1. Fondo del panel lateral (degradado)
    int y;
    int colorBase;
    for (y = 0; y < BOARD_SIZE * CELL_SIZE; y++) {
        colorBase = 60 + (y * 20) / (BOARD_SIZE * CELL_SIZE);
        SDL_SetRenderDrawColor(renderer, colorBase, colorBase, colorBase + 20, 255);
        SDL_RenderDrawLine(renderer, 
                      MARGIN_X + BOARD_SIZE * CELL_SIZE, MARGIN_Y + y,
                      MARGIN_X + BOARD_SIZE * CELL_SIZE + SIDEBAR_WIDTH, MARGIN_Y + y);
    }
    
    // TIMER (caja en panel lateral)
    SDL_Rect timerBox = {
        MARGIN_X + BOARD_SIZE * CELL_SIZE + 20,
        MARGIN_Y + 30,
        SIDEBAR_WIDTH - 40,
        50
    };
    SDL_SetRenderDrawColor(renderer, 70, 70, 100, 255);
    SDL_RenderFillRect(renderer, &timerBox);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &timerBox);
    
    // PUNTOS (caja en panel lateral)
    SDL_Rect puntosBox = {
        MARGIN_X + BOARD_SIZE * CELL_SIZE + 20,
        MARGIN_Y + 100,
        SIDEBAR_WIDTH - 40,
        50
    };
    SDL_SetRenderDrawColor(renderer, 70, 100, 70, 255);
    SDL_RenderFillRect(renderer, &puntosBox);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &puntosBox);
    
    // TÍTULO PRINCIPAL
    SDL_Rect titulo = {
        MARGIN_X,
        30,
        BOARD_SIZE * CELL_SIZE,
        50
    };
    SDL_SetRenderDrawColor(renderer, 80, 80, 150, 255);
    SDL_RenderFillRect(renderer, &titulo);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &titulo);
    
    // COLORES PARA LAS CELDAS
    SDL_Color colorCelda1 = {100, 150, 255, 255};  // Azul claro
    SDL_Color colorCelda2 = {255, 255, 255, 255};  // Blanco
    SDL_Color colorBorde = {80, 80, 120, 255};     // Azul grisáceo
    
    // DIBUJAR TODAS LAS CELDAS DEL TABLERO
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            SDL_Rect celda = {
                MARGIN_X + j * CELL_SIZE,
                MARGIN_Y + i * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };
            
            // Color alternado (como tablero de ajedrez)
            if ((i + j) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, colorCelda1.r, colorCelda1.g, colorCelda1.b, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, colorCelda2.r, colorCelda2.g, colorCelda2.b, 255);
            }
            SDL_RenderFillRect(renderer, &celda);
            
            // Borde de celda
            SDL_SetRenderDrawColor(renderer, colorBorde.r, colorBorde.g, colorBorde.b, 255);
            SDL_RenderDrawRect(renderer, &celda);
        }
    }
    
    // BORDES GRUESOS PARA BLOQUES 3x3 (regiones del sudoku)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (i = 1; i < BOARD_SIZE; i++) {
        if (i % 3 == 0) {
            // Líneas verticales gruesas
            SDL_RenderDrawLine(renderer, 
                              MARGIN_X + i * CELL_SIZE, MARGIN_Y,
                              MARGIN_X + i * CELL_SIZE, MARGIN_Y + BOARD_SIZE * CELL_SIZE);
            SDL_RenderDrawLine(renderer, 
                              MARGIN_X + i * CELL_SIZE + 1, MARGIN_Y,
                              MARGIN_X + i * CELL_SIZE + 1, MARGIN_Y + BOARD_SIZE * CELL_SIZE);
            
            // Líneas horizontales gruesas
            SDL_RenderDrawLine(renderer,
                              MARGIN_X, MARGIN_Y + i * CELL_SIZE,
                              MARGIN_X + BOARD_SIZE * CELL_SIZE, MARGIN_Y + i * CELL_SIZE);
            SDL_RenderDrawLine(renderer,
                              MARGIN_X, MARGIN_Y + i * CELL_SIZE + 1,
                              MARGIN_X + BOARD_SIZE * CELL_SIZE, MARGIN_Y + i * CELL_SIZE + 1);
        }
    }
    
    // LLAMAR FUNCIONES DE DIBUJADO ESPECÍFICAS
    dibujarNumeros(renderer);           // Números dentro del tablero
    dibujarSelectorNumeros(renderer);   // Selector lateral de números
    dibujarCeldaSeleccionada(renderer); // Resaltado de celda seleccionada
}

void manejarClick(int x, int y) {
    // Verificar si se hizo click en el tablero
    if (x >= MARGIN_X && x < MARGIN_X + BOARD_SIZE * CELL_SIZE &&
        y >= MARGIN_Y && y < MARGIN_Y + BOARD_SIZE * CELL_SIZE) {
        
        int col = (x - MARGIN_X) / CELL_SIZE;
        int fila = (y - MARGIN_Y) / CELL_SIZE;
        
        // Verificar que la celda no sea fija usando la nueva función
        if (!esCeldaFija(fila, col)) {
            celdaSeleccionadaFila = fila;
            celdaSeleccionadaColumna = col;
            printf("Celda seleccionada: (%d, %d)\n", fila, col);
            
            // Si hay un número seleccionado, colocarlo en la celda
            if (numeroSeleccionado > 0) {
                printf("Colocando número %d en celda (%d, %d)\n", numeroSeleccionado, fila, col);
                colocarNumero(fila, col, numeroSeleccionado);
            }
        }
    }
    
    // Verificar si se hizo click en el selector de números
    int selectorX = MARGIN_X + BOARD_SIZE * CELL_SIZE + 20;
    int selectorY = MARGIN_Y + 180;
    int numeroSize = 35;
    int spacing = 10;
    
    int totalWidth = 3 * numeroSize + 2 * spacing;
    int startX = selectorX + (SIDEBAR_WIDTH - 40 - totalWidth) / 2;
    
    if (x >= startX && x < startX + totalWidth &&
        y >= selectorY && y < selectorY + 3 * (numeroSize + spacing)) {
        
        int relX = x - startX;
        int relY = y - selectorY;
        int colNum = relX / (numeroSize + spacing);
        int filaNum = relY / (numeroSize + spacing);
        int numIndex = filaNum * 3 + colNum;
        
        if (numIndex >= 0 && numIndex < 9) {
            numeroSeleccionado = numIndex + 1;
            printf("Número seleccionado: %d\n", numeroSeleccionado);
        }
    }
    
    // Verificar si se hizo click en el botón borrar
    SDL_Rect borrarRect = {
        startX,
        selectorY + 3 * (numeroSize + spacing) + 10,
        totalWidth,
        numeroSize
    };
    
    if (x >= borrarRect.x && x < borrarRect.x + borrarRect.w &&
        y >= borrarRect.y && y < borrarRect.y + borrarRect.h) {
        numeroSeleccionado = 0;
        printf("Selección borrada\n");
    }
}
