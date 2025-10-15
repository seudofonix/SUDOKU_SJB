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
 
void imprimirTablero()
{
	// Se puede ajustar la posicion de la tabla con estos dos valores. 
	const int X_OFFSET = 4;
	const int Y_OFFSET = 2;
	
	const char VERTICAL = '|';
	char letra_columna = 'A';
	char numero_fila = '0';
	
	system("cls"); // Limpia la pantalla. Puede causar problemas con algunos antivirus.

	for (int i = 0 ; i < X_OFFSET ; i++)
		printf(" ");
	
	for (int i = 0 ; i < 9 ; i++)
		printf("%c ", numero_fila++);
	
	for (int i = 0 ; i < Y_OFFSET ; i++)
		printf("\n");
	
	for (int columna = 0 ; columna < 9 ; columna++)
	{
		printf("%c", letra_columna++);
		
		for (int i = 0 ; i < X_OFFSET-2 ; i++)
			printf(" ");
		
		for (int fila = 0 ; fila < 9 ; fila++)
		{	
			printf("%c", VERTICAL);
			
			if (tablero[columna][fila] == 0)
				printf(" ");
			else
				printf("%d", tablero[columna][fila]);
		}
		printf("%c", VERTICAL);
		printf("\n");
	}
}


void editarTablero(char* casillero, int movimiento)
{
	// int tablero[9][9]
	// char* casillero es una cadena de dos caracteres, un caracter en frente del otro 
	// la funcion asume que casillero es un parametro valido
	// e.g. "A7", "B9", "E2"
	
	int indiceLetra = (toupper(*casillero) - 'A') % 8;
	printf("%d", indiceLetra);
	casillero++;
	int indiceNumero = (*casillero - '0') % 8;
	printf("%d", indiceNumero);
	tablero[indiceLetra][indiceNumero] = movimiento % 8;
	
	return;
}

