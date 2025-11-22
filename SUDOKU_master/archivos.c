#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "archivos.h"

const char NOMBRE_ARCHIVO[] = "rankings.txt";
const int PUNTUACION_MAXIMA = 10000;

// // Función interna para comparar puntajes (necesaria para ordenar)
int compararRegistros(const void* a, const void* b) {
    RegistroRanking* r1 = (RegistroRanking*)a;
    RegistroRanking* r2 = (RegistroRanking*)b;
    // Orden descendente (de mayor a menor)
    return r2->puntaje - r1->puntaje; 
}

int calcularPuntaje(double tiempoFinal) {
    if (tiempoFinal < 0) return 0;
  // Fórmula simple basada en tiempo
    return (int)(PUNTUACION_MAXIMA / (pow(tiempoFinal/60.0, 2) + 1)); 
}

void guardarPuntaje(const char* nombre, int puntaje) {
    // "a" = append (agrega al final sin borrar lo anterior)
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "a"); 
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo de rankings.\n");
        return;
    }
    // Guardamos: NOMBRE [espacio] PUNTAJE [enter]
    fprintf(archivo, "%s %d\n", nombre, puntaje);
    fclose(archivo);
}

int leerTopRankings(RegistroRanking* rankingArray, int maxCantidad) {
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL) {
        return 0; // Si no existe el archivo, devolvemos 0 rankings
    }

    // Buffer temporal para leer todos los datos
    RegistroRanking buffer[100];
    int count = 0;
    
    // Leer mientras haya datos y espacio
    while (count < 100 && fscanf(archivo, "%20s %d", buffer[count].nombre, &buffer[count].puntaje) == 2) {
        count++;
    }
    fclose(archivo);

    // Ordenar el arreglo usando la funcion compararRegistros
    qsort(buffer, count, sizeof(RegistroRanking), compararRegistros);

    // Copiar solo los mejores 'maxCantidad' al arreglo final
    int k;
    for (k = 0; k < count && k < maxCantidad; k++) {
        rankingArray[k] = buffer[k];
    }

    return k; // Devolvemos la cantidad real copiada
}
