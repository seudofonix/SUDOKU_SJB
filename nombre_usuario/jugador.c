#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jugador.h"

#ifdef _WIN32
#define limpiarPantalla() system("cls")
#else
#define limpiarPantalla() system("clear")
#endif

// Ingreso del nombre del jugador (sin cuadro SUDOKU)
    void nombre_jugador(char w_NombreIngresado[]) {
    limpiarPantalla();

    // (Se eliminó el cuadro que decía "SUDOKU")

    printf("\nIngrese su nombre (puede incluir espacios):\n");
    printf("%sNombre del jugador:%s ", COLOR_VERDE, COLOR_RESET);

    fgets(w_NombreIngresado, 50, stdin);
    w_NombreIngresado[strcspn(w_NombreIngresado, "\n")] = '\0';

    if (strlen(w_NombreIngresado) == 0)
        strcpy(w_NombreIngresado, "Jugador");

    printf("\n%s=============================================================%s\n", COLOR_VERDE, COLOR_RESET);
    printf("%s ¡Bienvenido/a al Sudoku, %s%s%s! %s\n", COLOR_VERDE, COLOR_CYAN, w_NombreIngresado, COLOR_VERDE, COLOR_RESET);
    printf("%s=============================================================%s\n\n", COLOR_VERDE, COLOR_RESET);
}

// Reglas del Sudoku
    void consigna(const char w_NombreIngresado[]) {
    printf("%sHola %s%s%s, antes de comenzar, repasemos las reglas del Sudoku:%s\n\n",
        COLOR_AMARILLO, COLOR_CYAN, w_NombreIngresado, COLOR_AMARILLO, COLOR_RESET);

    printf("%s======================= REGLAS DEL JUEGO =======================%s\n", COLOR_MAGENTA, COLOR_RESET);
    printf("%s1)%s El Sudoku es un tablero de 9x9 dividido en 9 subcuadrículas de 3x3.\n", COLOR_CYAN, COLOR_RESET);
    printf("%s2)%s El objetivo es llenar todas las casillas vacías con números del 1 al 9.\n", COLOR_CYAN, COLOR_RESET);
    printf("%s3)%s Cada número puede aparecer solo una vez por fila, columna y subcuadrícula.\n", COLOR_CYAN, COLOR_RESET);
    printf("%s4)%s El tablero empieza con algunos números ya colocados (pistas iniciales).\n", COLOR_CYAN, COLOR_RESET);
    printf("%s5)%s No se puede modificar los números predefinidos del tablero.\n", COLOR_CYAN, COLOR_RESET);
    printf("%s6)%s El juego termina cuando el tablero está completamente correcto.\n", COLOR_CYAN, COLOR_RESET);
    printf("%s7)%s Si completás el tablero correctamente, ganás la partida.\n", COLOR_CYAN, COLOR_RESET);
    printf("%s================================================================%s\n", COLOR_MAGENTA, COLOR_RESET);
    printf("%sConsejo:%s Usa la lógica, no adivines. Observá los patrones.\n", COLOR_AMARILLO, COLOR_RESET);
    printf("%s================================================================%s\n\n", COLOR_MAGENTA, COLOR_RESET);
}
