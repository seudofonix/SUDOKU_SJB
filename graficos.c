/*
*/
#include <windows.h>

void leerMovimiento()
{
	char casillero[2];
	int movimiento;
	
	printf("Escriba un movimiento. \nej: (A0 5): ");
	scanf("%s", &casillero);
	// Esto hay que reescribirlo con otra funcion mas adelante porque una cadena de mas de dos caracteres va a romper el programa. 
	scanf("%d", &movimiento);
	
	editarTablero(&casillero, movimiento);
	imprimirTablero(); // esto no va aca
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
