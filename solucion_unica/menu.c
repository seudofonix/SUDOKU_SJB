#include <stdio.h>
#include "menu.h"
#include "graficos.h"  // Para usar dibujarTextoCentrado

// Definir la variable global del estado
EstadoJuego estadoActual = ESTADO_MENU;

void dibujarMenuPrincipal(SDL_Renderer* renderer) {
    // Fondo del menú
    SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
    SDL_RenderClear(renderer);
    
    // Título del juego
    SDL_Rect tituloRect = {
        WINDOW_WIDTH / 2 - 200,
        80,
        400,
        80
    };
    SDL_SetRenderDrawColor(renderer, 80, 80, 150, 255);
    SDL_RenderFillRect(renderer, &tituloRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &tituloRect);
    
    SDL_Color colorBlanco = {255, 255, 255, 255};
    dibujarTextoCentrado(renderer, tituloRect.x, tituloRect.y, 
                        tituloRect.w, tituloRect.h, "SUDOKU MASTER", colorBlanco);
    
    // Botones del menú
    int botonWidth = 300;
    int botonHeight = 60;
    int startY = 200;
    int spacing = 20;
    
    // Botón JUGAR
    SDL_Rect jugarRect = {
        WINDOW_WIDTH / 2 - botonWidth / 2,
        startY,
        botonWidth,
        botonHeight
    };
    SDL_SetRenderDrawColor(renderer, 70, 100, 70, 255);
    SDL_RenderFillRect(renderer, &jugarRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &jugarRect);
    dibujarTextoCentrado(renderer, jugarRect.x, jugarRect.y, 
                        jugarRect.w, jugarRect.h, "JUGAR", colorBlanco);
    
    // Botón INSTRUCCIONES
    SDL_Rect instruccionesRect = {
        WINDOW_WIDTH / 2 - botonWidth / 2,
        startY + botonHeight + spacing,
        botonWidth,
        botonHeight
    };
    SDL_SetRenderDrawColor(renderer, 70, 70, 100, 255);
    SDL_RenderFillRect(renderer, &instruccionesRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &instruccionesRect);
    dibujarTextoCentrado(renderer, instruccionesRect.x, instruccionesRect.y, 
                        instruccionesRect.w, instruccionesRect.h, "INSTRUCCIONES", colorBlanco);
    
    // Botón SALIR
    SDL_Rect salirRect = {
        WINDOW_WIDTH / 2 - botonWidth / 2,
        startY + 2 * (botonHeight + spacing),
        botonWidth,
        botonHeight
    };
    SDL_SetRenderDrawColor(renderer, 100, 70, 70, 255);
    SDL_RenderFillRect(renderer, &salirRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &salirRect);
    dibujarTextoCentrado(renderer, salirRect.x, salirRect.y, 
                        salirRect.w, salirRect.h, "SALIR", colorBlanco);
}

void manejarClickMenu(int x, int y) {
    int botonWidth = 300;
    int botonHeight = 60;
    int startY = 200;
    int spacing = 20;
    
    // Botón JUGAR
    SDL_Rect jugarRect = {
        WINDOW_WIDTH / 2 - botonWidth / 2,
        startY,
        botonWidth,
        botonHeight
    };
    
    // Botón INSTRUCCIONES
    SDL_Rect instruccionesRect = {
        WINDOW_WIDTH / 2 - botonWidth / 2,
        startY + botonHeight + spacing,
        botonWidth,
        botonHeight
    };
    
    // Botón SALIR
    SDL_Rect salirRect = {
        WINDOW_WIDTH / 2 - botonWidth / 2,
        startY + 2 * (botonHeight + spacing),
        botonWidth,
        botonHeight
    };
    
    // Verificar clics
    if (x >= jugarRect.x && x < jugarRect.x + jugarRect.w &&
        y >= jugarRect.y && y < jugarRect.y + jugarRect.h) {
        estadoActual = ESTADO_JUGANDO;
        printf("Iniciando juego...\n");
    }
    else if (x >= instruccionesRect.x && x < instruccionesRect.x + instruccionesRect.w &&
             y >= instruccionesRect.y && y < instruccionesRect.y + instruccionesRect.h) {
        estadoActual = ESTADO_INSTRUCCIONES;
        printf("Mostrando instrucciones...\n");
    }
    else if (x >= salirRect.x && x < salirRect.x + salirRect.w &&
             y >= salirRect.y && y < salirRect.y + salirRect.h) {
        estadoActual = ESTADO_SALIR;
        printf("Saliendo del juego...\n");
    }
}

void dibujarInstrucciones(SDL_Renderer* renderer) {
    // Fondo
    SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
    SDL_RenderClear(renderer);
    
    // Título
    SDL_Rect tituloRect = {
        WINDOW_WIDTH / 2 - 200,
        50,
        400,
        60
    };
    SDL_SetRenderDrawColor(renderer, 80, 80, 150, 255);
    SDL_RenderFillRect(renderer, &tituloRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &tituloRect);
    
    SDL_Color colorBlanco = {255, 255, 255, 255};
    dibujarTextoCentrado(renderer, tituloRect.x, tituloRect.y, 
                        tituloRect.w, tituloRect.h, "INSTRUCCIONES", colorBlanco);
    
    // Área de texto de instrucciones
    SDL_Rect textoRect = {
        WINDOW_WIDTH / 2 - 250,
        130,
        500,
        300
    };
    SDL_SetRenderDrawColor(renderer, 60, 60, 80, 255);
    SDL_RenderFillRect(renderer, &textoRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &textoRect);
    
    // Texto de instrucciones (puedes personalizar esto)
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 20, 
                        textoRect.w, 30, "REGLAS DEL SUDOKU:", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 60, 
                        textoRect.w, 30, "- Llena el tablero 9x9 con números 1-9", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 90, 
                        textoRect.w, 30, "- No repetir números en filas", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 120, 
                        textoRect.w, 30, "- No repetir números en columnas", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 150, 
                        textoRect.w, 30, "- No repetir números en bloques 3x3", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 180, 
                        textoRect.w, 30, "- Clic en celda + seleccionar número", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 210, 
                        textoRect.w, 30, "- ¡Completa todo el tablero!", colorBlanco);
    
    // Botón VOLVER
    SDL_Rect volverRect = {
        WINDOW_WIDTH / 2 - 100,
        450,
        200,
        50
    };
    SDL_SetRenderDrawColor(renderer, 70, 70, 100, 255);
    SDL_RenderFillRect(renderer, &volverRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &volverRect);
    dibujarTextoCentrado(renderer, volverRect.x, volverRect.y, 
                        volverRect.w, volverRect.h, "VOLVER AL MENÚ", colorBlanco);
}

void manejarClickInstrucciones(int x, int y) {
    SDL_Rect volverRect = {
        WINDOW_WIDTH / 2 - 100,
        450,
        200,
        50
    };
    
    if (x >= volverRect.x && x < volverRect.x + volverRect.w &&
        y >= volverRect.y && y < volverRect.y + volverRect.h) {
        estadoActual = ESTADO_MENU;
    }
}
