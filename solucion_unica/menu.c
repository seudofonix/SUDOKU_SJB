#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "graficos.h"
#include "archivos.h" 

// Definir la variable global
EstadoJuego estadoActual = ESTADO_MENU;
char nombreJugador[21] = "";

//variables para recordar la sesion anterior
char ultimoJugador[21] = "---";
int ultimoPuntaje = 0;

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
    
    // 1. Declaramos jugarRect AQUÍ para poder usarlo en el if
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
    
    // --- LOGICA DE CLICKS ---
    
    // Verificar clics
    if (x >= jugarRect.x && x < jugarRect.x + jugarRect.w &&
        y >= jugarRect.y && y < jugarRect.y + jugarRect.h) {
        estadoActual = ESTADO_INGRESO_NOMBRE;
        
        // Activamos el teclado de SDL para poder escribir
        SDL_StartTextInput(); 
        printf("Cambiando a ingreso de nombre...\n");
    }
    
    // B. Click en INSTRUCCIONES
    else if (x >= instruccionesRect.x && x < instruccionesRect.x + instruccionesRect.w &&
             y >= instruccionesRect.y && y < instruccionesRect.y + instruccionesRect.h) {
        estadoActual = ESTADO_INSTRUCCIONES;
        printf("Mostrando instrucciones...\n");
    }
    
    // C. Click en SALIR
    else if (x >= salirRect.x && x < salirRect.x + salirRect.w &&
             y >= salirRect.y && y < salirRect.y + salirRect.h) {
        estadoActual = ESTADO_SALIR;
        printf("Saliendo del juego...\n");
    }
}


void dibujarIngresoNombre(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
    SDL_RenderClear(renderer);

    // Título
    SDL_Color colorTitulo = {100, 255, 100, 255};
    dibujarTextoCentrado(renderer, 0, 100, WINDOW_WIDTH, 50, "NUEVA PARTIDA", colorTitulo);

    // Instrucción
    SDL_Color colorBlanco = {255, 255, 255, 255};
    dibujarTextoCentrado(renderer, 0, 200, WINDOW_WIDTH, 30, "Ingresa tu nombre para comenzar:", colorBlanco);

    // Caja de Texto
    SDL_Rect cajaTexto = {WINDOW_WIDTH/2 - 150, 250, 300, 50};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &cajaTexto);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &cajaTexto);

    // Mostrar lo que se escribe
    if (strlen(nombreJugador) > 0) {
        SDL_Color colorNegro = {0, 0, 0, 255};
        dibujarTextoCentrado(renderer, cajaTexto.x, cajaTexto.y, cajaTexto.w, cajaTexto.h, nombreJugador, colorNegro);
    } else {
        SDL_Color colorGris = {150, 150, 150, 255};
        dibujarTextoCentrado(renderer, cajaTexto.x, cajaTexto.y, cajaTexto.w, cajaTexto.h, "Escribe aqui...", colorGris);
    }

    dibujarTextoCentrado(renderer, 0, 320, WINDOW_WIDTH, 30, "(Presiona ENTER para Jugar)", colorBlanco);
}

void manejarEscrituraNombre(SDL_Event* event) {
    if (event->type == SDL_TEXTINPUT) {
        if (strlen(nombreJugador) < 20) {
            strcat(nombreJugador, event->text.text);
        }
    } else if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_BACKSPACE && strlen(nombreJugador) > 0) {
            nombreJugador[strlen(nombreJugador) - 1] = '\0';
        }
        // CAMBIO CRITICO: Al dar Enter, iniciamos el juego
        else if (event->key.keysym.sym == SDLK_RETURN) {
            if (strlen(nombreJugador) > 0) {
                SDL_StopTextInput();
                estadoActual = ESTADO_JUGANDO; // <-- AHORA VAMOS A JUGAR
                crearTablero(); // Generamos un tablero nuevo
            }
        }
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


// --- COPIA ESTO AL FINAL DE menu.c ---

void dibujarRanking(SDL_Renderer* renderer) {
    // 1. Fondo
    SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
    SDL_RenderClear(renderer);

    // 2. Título
    SDL_Color colorTitulo = {255, 100, 100, 255};
    dibujarTextoCentrado(renderer, 0, 30, WINDOW_WIDTH, 60, "MEJORES PUNTAJES", colorTitulo);

    // 3. Leer Ranking (Necesitas tener implementado leerTopRankings en archivos.c)
    RegistroRanking tops[5];
    int cantidad = leerTopRankings(tops, 5); 

    // 4. Dibujar Tabla
    SDL_Color colorTexto = {255, 255, 255, 255};
    int startY = 120;
    int lineHeight = 40;

    // Encabezados
    dibujarTextoCentrado(renderer, 50, 90, 200, 30, "NOMBRE", colorTexto);
    dibujarTextoCentrado(renderer, 300, 90, 100, 30, "PUNTOS", colorTexto);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 50, 120, 450, 120); // Línea separadora

    int i;
    for (i = 0; i < cantidad; i++) {
        char bufferPuntos[20];
        sprintf(bufferPuntos, "%d", tops[i].puntaje);

        // Nombre 
        dibujarTextoCentrado(renderer, 50, startY + i*lineHeight, 200, 30, tops[i].nombre, colorTexto);
        // Puntos
        dibujarTextoCentrado(renderer, 300, startY + i*lineHeight, 100, 30, bufferPuntos, colorTexto);
    }

    // 5. Botón Volver
    SDL_Rect btnVolver = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT - 80, 200, 50};
    SDL_SetRenderDrawColor(renderer, 100, 100, 150, 255);
    SDL_RenderFillRect(renderer, &btnVolver);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &btnVolver);
    dibujarTextoCentrado(renderer, btnVolver.x, btnVolver.y, btnVolver.w, btnVolver.h, "VOLVER AL MENU", colorTexto);
}

void manejarClickRanking(int x, int y) {
    SDL_Rect btnVolver = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT - 80, 200, 50};
    
    if (x >= btnVolver.x && x < btnVolver.x + btnVolver.w &&
        y >= btnVolver.y && y < btnVolver.y + btnVolver.h) {
        estadoActual = ESTADO_MENU;
    }
}
