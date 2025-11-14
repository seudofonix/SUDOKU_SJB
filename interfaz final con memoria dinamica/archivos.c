#include <stdio.h>
#include "archivos.h"
#include <math.h>

/* 
													puntuacionMaxima
    Puntuacion (tiempo en segundos) =    ----------------------------------------
											(x / (puntuacionMaxima/10))²  +  1
    
    La funcion para determinar la puntuacion tiene un decrecimiento cuadratico de forma que 
    f(0) = puntuacionMaxima
    f(->∞) = 0;
    
    Los rankings se guardan con el siguiente formato: 
    nombre;puntuacion;tiempoensegundos*10\n
*/

#define BUFFER_NOMBRE 20
const int puntuacionMaxima = 10000;
const char RANKINGS[] = {"rankings.txt"};

FILE *rankingEscritura, *rankingLectura;

struct posicionRanking
{
	char* nombre[BUFFER_NOMBRE];
	int puntuacion;
	int tiempo;
	struct posicionRanking *siguiente;
};

void abrirArchivos()
{
	rankingEscritura = fopen(RANKINGS, "w");
	rankingLectura = fopen(RANKINGS, "r");
}

int calcularPuntaje(double tiempoFinal)
{
	return (int)puntuacionMaxima / (pow(tiempoFinal/10, 2) + 1);
}

void cerrarArchivos()
{
	fclose(rankingEscritura);
	fclose(rankingLectura);
}
