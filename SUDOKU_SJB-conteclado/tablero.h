#ifndef TABLERO_H
#define TABLERO_H

// Cambiamos de array estático a puntero doble para gestión dinámica
extern int **tablero;

//declaraciones de funciones 
void imprimirTablero();
void inicializarTableroVacio();
void llenarTableroNivelFacil();

//verificaciones
int esMovimientoValido(int fila, int columna, int numero);

// funciones para jugar
void hacerMovimientoUsuario();
int esJuegoCompleto();

// NUEVAS FUNCIONES PARA GESTIÓN DE MEMORIA
void crearTablero();
void destruirTablero();

#endif