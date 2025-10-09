// Definicion de typedef para el preprocesador
#ifndef TABLERO_H
#define TABLERO_H

	void imprimirTablero();
	void editarTablero(char* casillero, int movimiento);

	int tablero[9][9] = 
	{ {0, 1, 2, 3, 4, 5, 6, 7, 8},
	  {1, 1, 0, 0, 0, 0, 0, 0, 0},
	  {2, 0, 2, 0, 0, 0, 0, 0, 0},
	  {3, 0, 0, 3, 0, 0, 0, 0, 0},   // la definicion de tablero_prueba no se
	  {4, 0, 0, 0, 4, 0, 0, 0, 0},   // tendria que hacer aca pero eso implica
	  {5, 0, 0, 0, 0, 5, 0, 0, 0},   // crear otro archivo mas
	  {6, 0, 0, 0, 0, 0, 6, 0, 0},
	  {7, 0, 0, 0, 0, 0, 0, 7, 0},
	  {8, 0, 0, 0, 0, 0, 0, 0, 8} };
	
/*	
    { {0, 1, 2, 3, 4, 5, 6, 7, 8},
	  {1, 1, 0, 0, 0, 0, 0, 0, 0},
	  {2, 0, 2, 0, 0, 0, 0, 0, 0},
	  {3, 0, 0, 3, 0, 0, 0, 0, 0},
	  {4, 0, 0, 0, 4, 0, 0, 0, 0},
	  {5, 0, 0, 0, 0, 5, 0, 0, 0},
	  {6, 0, 0, 0, 0, 0, 6, 0, 0},
	  {7, 0, 0, 0, 0, 0, 0, 7, 0},
	  {8, 0, 0, 0, 0, 0, 0, 0, 8} }; */
	
#endif

// LAS VARIABLES EN ARCHIVOS HEADER SE DECLARAN PERO NO SE DEBEN DEFINIR.
