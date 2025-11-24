#ifndef TIEMPO_H
#define TIEMPO_H

#include <SDL2/SDL.h>

// Variables globales de tiempo
extern Uint32 tiempoInicio;
extern double tiempoTranscurrido;

// Funciones de manejo de tiempo
void iniciarTemporizador();
void actualizarTiempo();
void reiniciarTemporizador();
double obtenerTiempoTranscurrido();
void formatearTiempo(char* buffer, int tamano);

#endif
