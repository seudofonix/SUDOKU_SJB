#ifndef TABLERO_H
#define TABLERO_H

// Declaracion de la variable global del tablero
extern int tablero[9][9];

//declaraciones de funciones 
void imprimirTablero();
void inicializarTableroVacio();
void llenarTableroNivelFacil();

//verificaciones
int esMovimientoValido(int fila, int columna, int numero);

// funciones para jugar
void hacerMovimientoUsuario();
int esJuegoCompleto();

#endif

