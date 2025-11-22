#ifndef ARCHIVOS_H
#define ARCHIVOS_H

// Estructura para un registro de ranking
typedef struct {
    char nombre[21]; // 20 caracteres + null
    int puntaje;
} RegistroRanking;

// Funciones que el main y el menu necesitan
void guardarPuntaje(const char* nombre, int puntaje);
int leerTopRankings(RegistroRanking* rankingArray, int maxCantidad);
int calcularPuntaje(double tiempoFinal);

#endif

