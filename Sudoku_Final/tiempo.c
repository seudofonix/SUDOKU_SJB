#include <stdio.h>
#include "tiempo.h"

// Variables globales de tiempo
Uint32 tiempoInicio = 0;
double tiempoTranscurrido = 0;

void iniciarTemporizador() {
    tiempoInicio = SDL_GetTicks();
    tiempoTranscurrido = 0;
    printf("Temporizador iniciado\n");
}

void actualizarTiempo() {
    if (tiempoInicio > 0) {
        Uint32 msPasados = SDL_GetTicks() - tiempoInicio;
        tiempoTranscurrido = msPasados / 1000.0;
    }
}

void reiniciarTemporizador() {
    tiempoInicio = SDL_GetTicks();
    tiempoTranscurrido = 0;
    printf("Temporizador reiniciado\n");
}

double obtenerTiempoTranscurrido() {
    return tiempoTranscurrido;
}

void formatearTiempo(char* buffer, int tamano) {
    int totalSegundos = (int)tiempoTranscurrido;
    int horas = totalSegundos / 3600;
    int minutos = (totalSegundos % 3600) / 60;
    int segundos = totalSegundos % 60;
    
    snprintf(buffer, tamano, "%02d:%02d:%02d", horas, minutos, segundos);
}
