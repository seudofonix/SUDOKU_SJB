#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tablero.h"

//------------- ---   CREACION TABLERO-------- 

// Definición de la variable global del tablero - matriz 9x9 inicializada con ceros
int tablero[9][9] = {0};
int tableroEstado[9][9] = {0};

struct valoresPosibles
{
	int numerosBase[9];
	int tamanoArreglo;
};

// Randomiza el orden de los elementos que se encuentran dentro de un arreglo
void randomizarArreglo(int* arreglo, int tamanoArreglo)
{
    for (int i = tamanoArreglo - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);  // índice aleatorio entre 0 e i
        int temp = arreglo[i];
		arreglo[i] = arreglo[j];
        arreglo[j] = temp;
    }
}

// Borra el elemento en el indice y desfasa todos los numeros subsiguientes en el arreglo para rellenar el espacio. 
void borrarElemento(int* arreglo, int indice, int tamanoArreglo)  
{
	for (int i = indice; i < tamanoArreglo-1; i++)
	{
		arreglo[i] = arreglo[i+1];
	}
}

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

// Intenta llenar la casilla con un numero aleatorio valido para su posicion
// Devuelve 0 cuando no hay movimientos validos para la casilla dada. 
int llenarCasilla(int fila, int columna)
{
    if (fila == 9)  // Caso base: tablero completo
        return 1;

    int siguienteFila = (columna == 8) ? fila + 1 : fila;
    int siguienteColumna = (columna + 1) % 9;

    struct valoresPosibles v = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        9
    };

    randomizarArreglo(v.numerosBase, v.tamanoArreglo);

    for (int i = 0; i < v.tamanoArreglo; i++)
    {
        int num = v.numerosBase[i];

        if (esMovimientoValido(fila, columna, num))
        {
            tablero[fila][columna] = num;

            // Intentar llenar la siguiente casilla
            if (llenarCasilla(siguienteFila, siguienteColumna))
                return 1;

            // Si no funcionó, retrocede
            tablero[fila][columna] = 0;
        }
    }

    // Si no se puede colocar ningún número válido aquí, vuelve atrás
    return 0;
}

void llenarTablero(int celdasMostradas)
{
	
	inicializarTableroVacio();
	printf("Generando Sudoku (%d CASILLAS)...\n", celdasMostradas);
	
	// Se llena el tablero completo con numeros validos.
	for(int fila = 0; fila < 9; fila++)
	{
		for(int columna = 0; columna < 9; columna++)
		{
			llenarCasilla(fila, columna);
		}
	}
	
	// Se eligen N numeros al azar para mostrar, el resto se borra. 
	int indiceCeldas[81];
	for(int i = 0; i < 81; i++)  // Se crea un arreglo de 81 numeros que corresponden a las casillas del tablero. 
	{
		indiceCeldas[i] = i;
	}
	
	randomizarArreglo(indiceCeldas, 81);
	for(int i = 0; i < (81 - celdasMostradas); i++)
	{
		tablero[indiceCeldas[i]/9][indiceCeldas[i]%9] = 0;
	}
	return;
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
