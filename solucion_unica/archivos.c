#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "archivos.h"
#include "tiempo.h"

const char NOMBRE_ARCHIVO[] = "rankings.txt";
const int PUNTUACION_MAXIMA = 1500;

// // Función interna para comparar puntajes (necesaria para ordenar)
int compararRegistros(const void* a, const void* b) {
    RegistroRanking* r1 = (RegistroRanking*)a;
    RegistroRanking* r2 = (RegistroRanking*)b;
    
    //Primero por puntaje (descendente)
    if (r2->puntaje != r1->puntaje) {
        return r2->puntaje - r1->puntaje;
    }
    // Si mismo puntaje, por tiempo (ascendente - menor tiempo es mejor)
    if (r1->tiempo < r2->tiempo) return -1;
    if (r1->tiempo > r2->tiempo) return 1;
    return 0;
}

int calcularPuntaje(double tiempoFinal) {
    if (tiempoFinal < 0) return 0;
    
    // Tiempo límite para puntaje perfecto (2 minutos)
    double tiempoLimitePerfecto = 120.0; // 2 minutos
    
    if (tiempoFinal <= tiempoLimitePerfecto) {
        return PUNTUACION_MAXIMA; // Puntaje perfecto si termina en 2 minutos o menos
    }
    
    // Reducción progresiva después del tiempo límite
    double reduccion = (tiempoFinal - tiempoLimitePerfecto) / 60.0 * 50; // 50 puntos por minuto extra
    
    int puntaje = PUNTUACION_MAXIMA - (int)reduccion;
    
    // Mínimo 0 puntos
    return (puntaje > 0) ? puntaje : 0;
}

void guardarPuntaje(const char* nombre, int puntaje) {
    // Usar el tiempo actual del juego
   // extern double tiempoTranscurrido;
    double tiempo = tiempoTranscurrido;
	
	// Primero leer todos los puntajes existentes
    RegistroRanking rankings[200];
    int count = 0;
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "r");
    
    if (archivo != NULL) {
        // Leer todos los registros existentes
        while (count < 200 && fscanf(archivo, "%20s %d %lf", rankings[count].nombre, &rankings[count].puntaje, &rankings[count].tiempo) == 3) {
            count++;
        }
        fclose(archivo);
    }
    
    // Si no leímos nada, intentar con formato viejo (nombre, puntos)
        if (count == 0) {
            rewind(archivo);
            while (count < 200 && fscanf(archivo, "%20s %d", 
                rankings[count].nombre, &rankings[count].puntaje) == 2) {
                rankings[count].tiempo = 600.0; // Tiempo por defecto: 10 minutos
                count++;
            }
        }
        fclose(archivo);
    
    // Buscar si el jugador ya existe
    int jugadorEncontrado = 0;
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(rankings[i].nombre, nombre) == 0) {
            // Actualizar si mejor puntaje o mismo puntaje con menos tiempo
            if (puntaje > rankings[i].puntaje || (puntaje == rankings[i].puntaje && tiempo < rankings[i].tiempo)) {
                rankings[i].puntaje = puntaje;
                rankings[i].tiempo = tiempo;
                printf("Actualizado: %s - %d pts en %.0fs\n", nombre, puntaje, tiempo);
            } else {
                printf("%s ya tiene mejor puntaje: %d pts vs %d pts\n", 
                    nombre, rankings[i].puntaje, puntaje);
            }
            jugadorEncontrado = 1;
            break;
        }
    }
    
     // Si no existe, agregar nuevo jugador
    if (!jugadorEncontrado) {
        if (count < 200) {
            strcpy(rankings[count].nombre, nombre);
            rankings[count].puntaje = puntaje;
            rankings[count].tiempo = tiempo;
            count++;
            printf("Nuevo jugador: %s con %d puntos en %.0f segundos\n", nombre, puntaje, tiempo);
        }
    }
    
    // Ordenar el arreglo
    qsort(rankings, count, sizeof(RegistroRanking), compararRegistros);
    
    // Reescribir todo el archivo
    archivo = fopen(NOMBRE_ARCHIVO, "w");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo de rankings para escribir.\n");
        return;
    }
    
    // Guardar todos los registros ordenados
    for (i = 0; i < count; i++) {
        fprintf(archivo, "%s %d %.2f\n", rankings[i].nombre, rankings[i].puntaje, rankings[i].tiempo);
    }
    fclose(archivo);
}

int leerTopRankings(RegistroRanking* rankingArray, int maxCantidad) {
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL) {
        // Si no existe el archivo, crear uno con datos de ejemplo
        printf("Creando archivo de rankings con datos de ejemplo...\n");
        archivo = fopen(NOMBRE_ARCHIVO, "w");
        if (archivo) {
            // Crear algunos datos de ejemplo con tiempo
            fprintf(archivo, "melisa 1500 300.00\n");
            fprintf(archivo, "evelyn 1500 350.00\n"); 
            fprintf(archivo, "katsuki 1000 450.00\n");
            fprintf(archivo, "naturo 1000 500.00\n");
            fprintf(archivo, "hinata 500 600.00\n");
            fclose(archivo);
            
            // Volver a abrir para leer
            archivo = fopen(NOMBRE_ARCHIVO, "r");
        }
    }

    if (archivo == NULL) {
        return 0; // Si no existe el archivo, devolvemos 0 rankings
    }

    // Buffer temporal para leer todos los datos
    RegistroRanking buffer[200];
    int count = 0;
    
    // CORREGIR: Leer con el formato correcto
    while (count < 200 && fscanf(archivo, "%20s %d %lf", 
           buffer[count].nombre, &buffer[count].puntaje, &buffer[count].tiempo) == 3) {
        count++;
    }
    
    // Si no funciona con formato nuevo, intentar formato viejo
    if (count == 0) {
        rewind(archivo);
        while (count < 200 && fscanf(archivo, "%20s %d", 
               buffer[count].nombre, &buffer[count].puntaje) == 2) {
            buffer[count].tiempo = 600.0; // Tiempo por defecto
            count++;
        }
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
