#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tablero.h"

//------------- ---   CREACION TABLERO-------- 

// Definición de la variable global del tablero - matriz 9x9 inicializada con ceros
int tablero[9][9] = {0};
int tableroEstado[9][9] = {0};



void inicializarTableroVacio() {
	int i, j;
	
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			tablero[i][j] = 0;
			tableroEstado[i][j] = 0;
		}
	}
}

//----------- GENERADOR DE NUM ALEATORIOS------

// Función para generar un número aleatorio entre min y max
int generarNumeroAleatorio(int min, int max){
    return rand() % (max - min + 1) + min;
}

//-------- LLENA TABLERO CON NUMEROS VALIDOS LISTO PARA JUGAR-----

//FUNCION PARA VERIFICAR SI UN MOVIMIENTO ES VALIDO
int esMovimientoValido(int fila, int columna, int numero){
    int c, f, i, j;
    int inicioFila, inicioColumna;

    //verificar fila
    for (c = 0; c < 9; c++){
        if (tablero[fila][c] == numero) return 0;
    }

    //verificar columna
    for (f = 0; f < 9; f++){
        if (tablero[f][columna] == numero) return 0;
    }

    //verificar bloque 3x3
    inicioFila = (fila/3)*3;
    inicioColumna = (columna/3) *3;

    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (tablero[inicioFila + i][inicioColumna + j] == numero) return 0;
        }
    }

    return 1;
}

// Función para llenar el tablero con un patrón de Sudoku FACIL
void llenarTableroNivelFacil(){
	int celdasLlenadas = 0;
	int fila, columna, numero;
	
	inicializarTableroVacio();
	printf("Generando Sudoku facil...\n");
	
	while (celdasLlenadas < 35){
		//Elegimos celdas al azar
		fila = generarNumeroAleatorio(0,8);
		columna = generarNumeroAleatorio(0,8);
		
		//si la celda está vacia, intentar poner numero..
		if (tablero[fila][columna] == 0){
			//probar numeros del 1 al 9 
			for (numero =1; numero <=9; numero++){
				if(esMovimientoValido(fila, columna, numero)){
					
					tablero[fila][columna] = numero;
					tableroEstado[fila][columna] = 1;  // Marcar como número fijo
					celdasLlenadas++;
					break;
				}
			}
		}
	}
}



//-------- FUNCION PARA VERIFICAR SI EL JUEGO ESTÁ COMPLETO( SIN VALIDACION DE SOL. UNICA)-----
int esJuegoCompleto(){
	int fila, columna;
	
    for (fila =0; fila < 9; fila++){
        for (columna=0; columna < 9; columna++){
            if (tablero[fila][columna] == 0){
                return 0; // SI  Hay celdas vacías - juego no completo
            }
        }
    }
    return 1; // TODAS las celdas llenas- juego COMPLETO
}

// ================= NUEVAS FUNCIONES PARA LA INTERFAZ GRÁFICA =================

// Función para actualizar el estado de una celda (correcto/incorrecto)
void actualizarEstadoCelda(int fila, int columna) {
    if (tableroEstado[fila][columna] == 1) return; // No modificar celdas fijas
    
    if (esMovimientoValido(fila, columna, tablero[fila][columna])) {
        tableroEstado[fila][columna] = 2; // Verde - correcto
    } else {
        tableroEstado[fila][columna] = 3; // Rojo - incorrecto
    }
}

// Función para obtener número de una celda
int obtenerNumeroCelda(int fila, int columna) {
    return tablero[fila][columna];
}

// Función para colocar número (reemplaza la lógica en manejarClick)
void colocarNumero(int fila, int columna, int numero) {
    if (tableroEstado[fila][columna] != 1) { // Solo si no es fija
        tablero[fila][columna] = numero;
        actualizarEstadoCelda(fila, columna);
    }
}

// Función para verificar si una celda es fija
int esCeldaFija(int fila, int columna) {
    return tableroEstado[fila][columna] == 1;
}
