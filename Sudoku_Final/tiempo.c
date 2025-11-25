#include <stdio.h>
#include "tiempo.h"

// Variables globales de tiempo

//almacena el instante (en milisegundos) obtenido por SDL_GetTicks() en el momento en el que se reinicia o inicia el temporizador
Uint32 tiempoInicio = 0;

//tiempo total transcurrido,expresado en segundos desde el ultimo inicio del temporizador
double tiempoTranscurrido = 0;

void iniciarTemporizador() {
    tiempoInicio = SDL_GetTicks();//inicio en milisegundos 
    tiempoTranscurrido = 0; // reinicio del contador en segundos 
    printf("Temporizador iniciado\n");
}

void actualizarTiempo() {
    if (tiempoInicio > 0) {
        Uint32 msPasados = SDL_GetTicks() - tiempoInicio; //milisegundos transcurridos 
        tiempoTranscurrido = msPasados / 1000.0; //lo pasamos a segundos 
    }
}

// reinicio del temporizador 
void reiniciarTemporizador() {
    tiempoInicio = SDL_GetTicks();
    tiempoTranscurrido = 0;
    printf("Temporizador reiniciado\n");
}

//devuelve el tiempo total que va pasando en segundos 
double obtenerTiempoTranscurrido() {
    return tiempoTranscurrido;
}
// convierte el tiempo a formato HH:MM:SS
void formatearTiempo(char* buffer, int tamano) {
    int totalSegundos = (int)tiempoTranscurrido;
    int horas = totalSegundos / 3600;
    int minutos = (totalSegundos % 3600) / 60;
    int segundos = totalSegundos % 60;
    
    snprintf(buffer, tamano, "%02d:%02d:%02d", horas, minutos, segundos);
}

