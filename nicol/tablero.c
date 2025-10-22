#include <stdio.h>
#include <stdlib.h>
#include "tablero.h"


/* Dado que el juego entero se va a hacer en terminal hay que implementar
 * un sistema de cursor para poder dibujar a distintas partes de la pantalla
 * con tal de poder mostrar cosas como el timer en pantalla.
*/

/*
 * Despues voy a tener que reescribir esta funcion para que use 
 * cursores en lugar de printf y saltos de linea. 
 * */
 

// Definición de la variable global del tablero - matriz 9x9 inicializada con ceros
int tablero[9][9] = {0};

void imprimirTablero() {
    // Limpiar la pantalla de la terminal
    #ifdef _WIN32
    system("cls");
    #else
        system("clear"); // Para Linux/Mac
    #endif
    
    
    // Espacio superior para mejor presentación
    printf("\n");
    // Título del juego
    printf("    SUDOKU - TABLERO\n");
    printf("\n");
    
    // Imprimir números de columnas (1-9) en la parte superior
    printf("     ");  // 5 espacios para alinear números de columnas con letras de filas

    for (int col = 1; col <= 9; col++) { //Bucle para las 9 columnas (1 a 9)
        printf("%d   ", col);  // Imprime el número de columna seguido de 3 espacios
        // AGREGAR ESPACIO EXTRA ENTRE BLOQUES DE 3 COLUMNAS
        if (col % 3 == 0 && col != 9) { //Si es múltiplo de 3 y no es la última columna
            printf(" "); 
        }
    }
    printf("\n");  // Nueva línea después de los números de columnas
    
    // Línea horizontal superior del tablero (borde grueso)
    printf("   ╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗\n");
    
    // RECORRER TODAS LAS FILAS DEL TABLERO (0-8 que corresponden a A-I)
    for (int fila = 0; fila < 9; fila++) {

        // Imprimir letra de fila (A-I) y borde izquierdo
        printf(" %c ║", 'A' + fila); // Convierte número a letra: 0→A, 1→B, ..., 8→I
        
        
        // RECORRER TODAS LAS COLUMNAS DE LA FILA ACTUAL

        for (int col = 0; col < 9; col++) {
            // Verificar si la celda está vacía (valor 0)
            if (tablero[fila][col] == 0) {
                printf(" · ");  // Mostrar punto medio para celdas vacías
            } else {
                printf(" %d ", tablero[fila][col]);  // Mostrar número de la celda
            }

            
            // AGREGAR SEPARADORES ENTRE COLUMNAS (excepto después de la última columna)
            if (col < 8) {

                // VERIFICAR SI ESTAMOS EN EL BORDE DE UN BLOQUE 3x3

                if ((col + 1) % 3 == 0) { // Si la siguiente columna es múltiplo de 3
                    printf("║");  // Separador vertical grueso entre bloques
                } else {          // Si estamos dentro de un bloque
                    printf("│");  // Separador vertical fino dentro del bloque
                }
            }
        }
        printf("║\n");  // Borde derecho y nueva línea
        
        // AGREGAR SEPARADORES ENTRE FILAS (excepto después de la última fila)
        if (fila < 8) {

            // Verificar si estamos en el borde de un bloque 3x3 vertical

            if ((fila + 1) % 3 == 0) { // Si la siguiente fila es múltiplo de 3
                // Línea horizontal gruesa entre bloques
                printf("   ╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣\n");
            } else {
                // Línea horizontal fina dentro del bloque
                printf("   ╟───┼───┼───╫───┼───┼───╫───┼───┼───╢\n");
            }
        }
    }
    
    // Línea horizontal inferior del tablero (borde grueso)
    printf("   ╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝\n");
    printf("\n");  // Espacio final para mejor legibilidad
}

void inicializarTableroVacio() {
    // RECORRER TODAS LAS FILAS DEL TABLERO
    for (int i = 0; i < 9; i++) {
        // RECORRER TODAS LAS COLUMNAS DE CADA FILA
        for (int j = 0; j < 9; j++) {
            tablero[i][j] = 0;  // Establecer cada celda como vacía (valor 0)
        }
    }
}



void probarTableroEjemplo() {
    // Inicializar todo el tablero como vacío
    inicializarTableroVacio();
    
    /* 
     * AGREGAR NÚMEROS DE EJEMPLO EN POSICIONES ESPECÍFICAS
     * Esto sirve para visualizar cómo se ven los números en el tablero
     * y probar que el formato visual funciona correctamente
     */
    
    // Diagonal principal con números
    tablero[0][0] = 5;  // Esquina superior izquierda
    tablero[1][1] = 3;  // Centro del primer bloque
    tablero[2][2] = 7;  // Esquina inferior del primer bloque
    
    // Algunos números en el centro del tablero
    tablero[4][4] = 9;  // Centro exacto del tablero
    
    // Algunos números en diferentes bloques
    tablero[0][4] = 2;  // Primera fila, quinta columna
    tablero[4][0] = 6;  // Quinta fila, primera columna
    tablero[8][8] = 1;  // Esquina inferior derecha
    
    // Números que muestren los bloques 3x3
    tablero[3][3] = 4;  // Inicio del bloque central
    tablero[5][5] = 8;  // Fin del bloque central
}

