#ifndef TABLERO_H
#define TABLERO_H

// Cambiar a punteros para memoria dinámica
extern int** tablero;
extern int** tableroEstado;  // 0=vacío, 1=fijo, 2=usuario correcto, 3=usuario incorrecto

//declaraciones de funciones 

void inicializarTableroVacio();
void llenarTablero(int);

// NUEVAS FUNCIONES PARA CREAR Y DESTRUIR TABLERO
void crearTablero();
void destruirTablero();

//verificaciones
int esMovimientoValido(int fila, int columna, int numero);

// funciones para jugar

int esJuegoCompleto();

// NUEVAS FUNCIONES PARA LA INTERFAZ GRÁFICA
void actualizarEstadoCelda(int fila, int columna);
int obtenerNumeroCelda(int fila, int columna);
void colocarNumero(int fila, int columna, int numero);
int esCeldaFija(int fila, int columna);

#endif
