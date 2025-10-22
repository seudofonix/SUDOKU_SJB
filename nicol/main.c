/*  PROTOTIPO DE ARCHIVO SUDOKU.
	Todas las definiciones de las funciones y las variables globales hay que definirlas en tablero.h y graficos.h
*/

// ------ LIBRERIAS ------
#include <stdio.h>
#include "tablero.h"


// ------ VARIABLES GLOBALES ------


// ------ ESTRUCTURAS ------


int main(){
	// Titulo del programa
	printf("=== VISUALIZADOR DE TABLERO SUDOKU=== \n\n");
	
	// Llamar a la funcion de ejemplo para mostrar el tablero con algunos numeros
	probarTableroEjemplo();
	
	// Imprimir el tablero con el ejemplo
    imprimirTablero();
    
    // Mensaje informativo para el usuario
    printf("Este es el tablero de Sudoku con algunos números de ejemplo.\n");
    printf("Las celdas vacías se muestran con '·' (punto medio).\n");
    printf("Los bloques 3x3 están separados con bordes más gruesos.\n\n");
    
    // Pausa para que el usuario pueda ver el resultado
    printf("Presione Enter para continuar...");
    getchar();  // Esperar a que el usuario presione Enter
    
    return 0;
	
	}

