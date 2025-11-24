#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "graficos.h"
#include "archivos.h" 
#include "tiempo.h"

// Definir la variable global
EstadoJuego estadoActual = ESTADO_MENU;
char nombreJugador[21] = "";

//variables para recordar la sesion anterior
char ultimoJugador[21] = "---";
int ultimoPuntaje = 0;

void dibujarMenuPrincipal(SDL_Renderer* renderer) {
    // 1. Fondo y Limpieza
    SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
    SDL_RenderClear(renderer);
    
    // 2. TÃ­tulo "SUDOKU MASTER"
    SDL_Rect tituloRect = {WINDOW_WIDTH / 2 - 200, 50, 400, 80}; // SubÃ­ un poco el tÃ­tulo (y=50)
    SDL_SetRenderDrawColor(renderer, 80, 80, 150, 255);
    SDL_RenderFillRect(renderer, &tituloRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &tituloRect);
    
    SDL_Color colorBlanco = {255, 255, 255, 255};
    dibujarTextoCentrado(renderer, tituloRect.x, tituloRect.y, 
                        tituloRect.w, tituloRect.h, "SUDOKU MASTER", colorBlanco);
    
    // 3. ConfiguraciÃ³n de Botones
    int botonWidth = 300;
    int botonHeight = 50; // Los hice un poquito mÃ¡s bajos para que entren bien
    int startY = 160;     // Empezamos mÃ¡s arriba
    int spacing = 15;     // Menos espacio entre ellos
    
    // --- BOTÃ“N JUGAR ---
    SDL_Rect jugarRect = {WINDOW_WIDTH/2 - botonWidth/2, startY, botonWidth, botonHeight};
    SDL_SetRenderDrawColor(renderer, 70, 100, 70, 255); // Verde
    SDL_RenderFillRect(renderer, &jugarRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &jugarRect);
    dibujarTextoCentrado(renderer, jugarRect.x, jugarRect.y, jugarRect.w, jugarRect.h, "JUGAR", colorBlanco);

    // --- BOTÃ“N RANKING (NUEVO) ---
    SDL_Rect rankingRect = {WINDOW_WIDTH/2 - botonWidth/2, startY + botonHeight + spacing, botonWidth, botonHeight};
    SDL_SetRenderDrawColor(renderer, 200, 150, 50, 255); // Color Naranja/Dorado
    SDL_RenderFillRect(renderer, &rankingRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rankingRect);
    dibujarTextoCentrado(renderer, rankingRect.x, rankingRect.y, rankingRect.w, rankingRect.h, "VER RANKING", colorBlanco);
    
    // --- BOTÃ“N INSTRUCCIONES ---
    SDL_Rect instruccRect = {WINDOW_WIDTH/2 - botonWidth/2, startY + 2*(botonHeight + spacing), botonWidth, botonHeight};
    SDL_SetRenderDrawColor(renderer, 70, 70, 100, 255); // Azulado
    SDL_RenderFillRect(renderer, &instruccRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &instruccRect);
    dibujarTextoCentrado(renderer, instruccRect.x, instruccRect.y, instruccRect.w, instruccRect.h, "INSTRUCCIONES", colorBlanco);
    
    // --- BOTÃ“N SALIR ---
    SDL_Rect salirRect = {WINDOW_WIDTH/2 - botonWidth/2, startY + 3*(botonHeight + spacing), botonWidth, botonHeight};
    SDL_SetRenderDrawColor(renderer, 100, 70, 70, 255); // Rojizo
    SDL_RenderFillRect(renderer, &salirRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &salirRect);
    dibujarTextoCentrado(renderer, salirRect.x, salirRect.y, salirRect.w, salirRect.h, "SALIR", colorBlanco);

    // 4. Mostrar Ãºltimo jugador (si existe) al pie de pÃ¡gina
    if (ultimoPuntaje > 0) {
        char infoAnterior[100];
        sprintf(infoAnterior, "Ultima partida: %s - %d pts", ultimoJugador, ultimoPuntaje);
        SDL_Color colorGris = {180, 180, 180, 255};
        dibujarTextoCentrado(renderer, 0, WINDOW_HEIGHT - 40, WINDOW_WIDTH, 30, infoAnterior, colorGris);
    }
}

void manejarClickMenu(int x, int y) {
    // Debemos usar LAS MISMAS coordenadas que en dibujarMenuPrincipal
    int botonWidth = 300;
    int botonHeight = 50;
    int startY = 160;
    int spacing = 15;
    
    // Definimos los rectÃ¡ngulos invisibles para detectar el click
    SDL_Rect jugarRect     = {WINDOW_WIDTH/2 - botonWidth/2, startY, botonWidth, botonHeight};
    SDL_Rect rankingRect   = {WINDOW_WIDTH/2 - botonWidth/2, startY + botonHeight + spacing, botonWidth, botonHeight};
    SDL_Rect instruccRect  = {WINDOW_WIDTH/2 - botonWidth/2, startY + 2*(botonHeight + spacing), botonWidth, botonHeight};
    SDL_Rect salirRect     = {WINDOW_WIDTH/2 - botonWidth/2, startY + 3*(botonHeight + spacing), botonWidth, botonHeight};

    // --- DETECCIÃ“N DE CLICKS ---

    // 1. JUGAR -> Va a ingreso de nombre
    if (x >= jugarRect.x && x < jugarRect.x + jugarRect.w && y >= jugarRect.y && y < jugarRect.y + jugarRect.h) {
        estadoActual = ESTADO_INGRESO_NOMBRE;
        SDL_StartTextInput(); 
    }
    
    // 2. RANKING (NUEVO) -> Va a la pantalla de ranking
    else if (x >= rankingRect.x && x < rankingRect.x + rankingRect.w && y >= rankingRect.y && y < rankingRect.y + rankingRect.h) {
        estadoActual = ESTADO_RANKING;
    }

    // 3. INSTRUCCIONES
    else if (x >= instruccRect.x && x < instruccRect.x + instruccRect.w && y >= instruccRect.y && y < instruccRect.y + instruccRect.h) {
        estadoActual = ESTADO_INSTRUCCIONES;
    }
    
    // 4. SALIR
    else if (x >= salirRect.x && x < salirRect.x + salirRect.w && y >= salirRect.y && y < salirRect.y + salirRect.h) {
        estadoActual = ESTADO_SALIR;
    }
}


void dibujarIngresoNombre(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
    SDL_RenderClear(renderer);

    // TÃ­tulo
    SDL_Color colorTitulo = {100, 255, 100, 255};
    dibujarTextoCentrado(renderer, 0, 100, WINDOW_WIDTH, 50, "NUEVA PARTIDA", colorTitulo);

    // InstrucciÃ³n
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
                
                // REINICIAR VIDAS Y PUNTUACIÓN AL INICIAR NUEVA PARTIDA
                vidasRestantes = 3;
                puntuacionActual = 1500;
                reiniciarTemporizador(); 
        
        		estadoActual = ESTADO_JUGANDO;
        		crearTablero(); // Generamos un tablero nuevo
        
        		printf("Nueva partida iniciada para: %s\n", nombreJugador);
            }
        }
    }
}

void dibujarInstrucciones(SDL_Renderer* renderer) {
    // Fondo
    SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
    SDL_RenderClear(renderer);
    
    // TÃ­tulo
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
    
    // Ãrea de texto de instrucciones
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
                        textoRect.w, 30, "- Llena el tablero 9x9 con numeros 1-9", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 90, 
                        textoRect.w, 30, "- No repetir numeros en filas", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 120, 
                        textoRect.w, 30, "- No repetir numeros en columnas", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 150, 
                        textoRect.w, 30, "- No repetir numeros en bloques 3x3", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 180, 
                        textoRect.w, 30, "- Clic en celda + seleccionar numero", colorBlanco);
    dibujarTextoCentrado(renderer, textoRect.x, textoRect.y + 210, 
                        textoRect.w, 30, "- ¡Completa todo el tablero!", colorBlanco);
    
    // BotÃ³n VOLVER
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
                        volverRect.w, volverRect.h, "VOLVER AL MENU", colorBlanco);
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

// NUEVA FUNCIÓN: Dibujar pantalla de Game Over
void dibujarGameOver(SDL_Renderer* renderer) {
    // Fondo negro
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Texto "GAME OVER" grande en rojo
    SDL_Color rojo = {255, 0, 0, 255};
    dibujarTextoCentrado(renderer, 0, 160, WINDOW_WIDTH, 80, "GAME OVER", rojo);
    
    // Mensaje explicativo
    SDL_Color blanco = {255, 255, 255, 255};
    dibujarTextoCentrado(renderer, 0, 250, WINDOW_WIDTH, 40, "Te quedaste sin vidas!", blanco);
    
    // Mostrar puntuación final
    char puntuacionStr[50];
    sprintf(puntuacionStr, "Puntuacion final: %d pts", puntuacionActual);
    dibujarTextoCentrado(renderer, 0, 300, WINDOW_WIDTH, 30, puntuacionStr, blanco);
    
    // Instrucción para continuar
    dibujarTextoCentrado(renderer, 0, 350, WINDOW_WIDTH, 30, "Haz clic para volver al menu", blanco);
}

// NUEVA FUNCIÓN: Manejar click en pantalla de Game Over
void manejarClickGameOver(int x, int y) {
    // Cualquier click vuelve al menú
    estadoActual = ESTADO_MENU;
}


void dibujarRanking(SDL_Renderer* renderer) {
    // 1. Fondo
    SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
    SDL_RenderClear(renderer);

    // 2. Título
    SDL_Color colorTitulo = {255, 100, 100, 255};
    dibujarTextoCentrado(renderer, 0, 30, WINDOW_WIDTH, 60, "MEJORES PUNTAJES", colorTitulo);

    // 3. Leer Ranking
    RegistroRanking tops[10];
    int cantidad = leerTopRankings(tops, 10); 

    // 4. Dibujar Tabla
    SDL_Color colorTexto = {255, 255, 255, 255};
    int startY = 120;
    int lineHeight = 40;

    // Encabezados - AGREGAR "VIDAS"
    dibujarTextoCentrado(renderer, 50, 90, 120, 30, "NOMBRE", colorTexto);
    dibujarTextoCentrado(renderer, 170, 90, 80, 30, "PUNTOS", colorTexto);
    dibujarTextoCentrado(renderer, 250, 90, 100, 30, "TIEMPO", colorTexto);
    dibujarTextoCentrado(renderer, 350, 90, 80, 30, "VIDAS", colorTexto); // NUEVO ENCABEZADO
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 50, 120, 430, 120); // Línea separadora

    int i;
    for (i = 0; i < cantidad; i++) {
        char bufferPuntos[20];
        char bufferTiempo[20];
        
        sprintf(bufferPuntos, "%d", tops[i].puntaje);
        
        // Formatear tiempo en minutos:segundos
        int minutos = (int)tops[i].tiempo / 60;
        int segundos = (int)tops[i].tiempo % 60;
        sprintf(bufferTiempo, "%02d:%02d", minutos, segundos);

        // Nombre 
        dibujarTextoCentrado(renderer, 50, startY + i*lineHeight, 120, 30, tops[i].nombre, colorTexto);
        // Puntos
        dibujarTextoCentrado(renderer, 170, startY + i*lineHeight, 80, 30, bufferPuntos, colorTexto);
        // Tiempo
        dibujarTextoCentrado(renderer, 250, startY + i*lineHeight, 100, 30, bufferTiempo, colorTexto);
        // VIDAS - NUEVO: Mostrar corazones pixelados para las vidas
        dibujarVidasRanking(renderer, 350, startY + i*lineHeight, tops[i].vidas);
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

// NUEVA FUNCIÓN: Dibujar corazones de vidas en el ranking
void dibujarVidasRanking(SDL_Renderer* renderer, int x, int y, int vidas) {
    int vidaSize = 20;  // Tamaño más pequeño para el ranking
    int spacing = 4;
    
    // Dibujar corazones pixelados
    int i;
    for (i = 0; i < 3; i++) {
        int posX = x + i * (vidaSize + spacing);
        int posY = y + 5; // Centrar verticalmente
        
        // Color del corazón
        if (i < vidas) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo
        } else {
            SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255); // Gris oscuro
        }
        
        // Patrón de corazón 6x6 pixelado (más pequeño para ranking)
        int pixelSize = vidaSize / 6;
        
        // Definir el patrón del corazón reducido (1 = dibujar pixel, 0 = vacío)
        int heartPattern[6][6] = {
            {0,1,1,0,1,1},
            {1,1,1,1,1,1},
            {1,1,1,1,1,1},
            {0,1,1,1,1,0},
            {0,0,1,1,0,0},
            {0,0,0,0,0,0}
        };
        
        // Dibujar el corazón pixel por pixel
        int row, col;
        for (row = 0; row < 6; row++) {
            for (col = 0; col < 6; col++) {
                if (heartPattern[row][col] == 1) {
                    SDL_Rect pixel = {
                        posX + col * pixelSize,
                        posY + row * pixelSize,
                        pixelSize,
                        pixelSize
                    };
                    SDL_RenderFillRect(renderer, &pixel);
                }
            }
        }
    }
}

