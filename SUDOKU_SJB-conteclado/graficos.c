#include <stdio.h>
#include <stdlib.h>
#include "tablero.h"

#ifdef __CYGWIN__
#include <termios.h>
#include <unistd.h>

// Función similar a _getch() para Cygwin/Linux
char _getch(void) {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}
#else
#include <conio.h>  // Para _getch() en Windows nativo
#endif

// Variables globales para la posición del cursor
int cursorFila = 0;
int cursorColumna = 0;

// Función auxiliar para imprimir en color (para evitar código repetitivo)
void imprimirColor(const char* mensaje, int colorWindows, const char* colorANSI) {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorWindows);
    printf("%s", mensaje);
    SetConsoleTextAttribute(hConsole, 7); // Volver al color normal
    #else
    printf("%s%s\033[0m", colorANSI, mensaje);
    #endif
}

void navegarConTeclado()
{
     // Verificar que el tablero existe
    if (tablero == NULL) {
        printf("Error: El tablero no ha sido creado\n", 12, "\033[1;31m");
        printf("Presione cualquier tecla para continuar...");
        _getch();
        return;
    }

    int jugando = 1;
    
    printf("\n--- CONTROLES ---\n");
    printf("Flechas: Mover cursor\n");
    printf("1-9: Colocar número\n");
    printf("0: Borrar número\n");
    printf("ESC: Salir de navegación\n");
    printf("\nPresione cualquier tecla para comenzar...");
    _getch();
    
    while(jugando)
    {
        // Limpiar pantalla
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
        
        // Imprimir tablero normal
        imprimirTablero();
        
        // Mostrar información del cursor
        printf("\n| Cursor en: %c%d | ", 'A' + cursorFila, cursorColumna + 1);
        if(tablero[cursorFila][cursorColumna] == 0) {
            printf(" celda: Vacía |\n");
        } else {
            printf("Celda: %d|\n", tablero[cursorFila][cursorColumna]);
        }
        printf("| Controles: Flechas mover, 1-9 numero, 0 borrar, ESC salir\n");
        
        // Obtener entrada del teclado sin esperar Enter
        int input = _getch();
        
        // Detectar flechas (en Cygwin/Linux las flechas envían secuencias ESC)
        if(input == 27) // ESC
        {
            input = _getch();
            if(input == 91) // [
            {
                input = _getch();
                // Mover el cursor según la flecha presionada
                switch(input)
                {
                    case 'A': // Flecha arriba
                        if(cursorFila > 0) cursorFila--;
                        break;
                    case 'B': // Flecha abajo
                        if(cursorFila < 8) cursorFila++;
                        break;
                    case 'D': // Flecha izquierda
                        if(cursorColumna > 0) cursorColumna--;
                        break;
                    case 'C': // Flecha derecha
                        if(cursorColumna < 8) cursorColumna++;
                        break;
                }
            }
            else
            {
                // ESC solo, salir
                jugando = 0;
                printf("Saliendo del modo navegación...\n");
            }
        }
        else
        {
            // Teclas normales
            switch(input)
            {
                case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9':
                    // Colocar número
                    if(tablero[cursorFila][cursorColumna] == 0)
                    {
                        int numero = input - '0';
                        if(esMovimientoValido(cursorFila, cursorColumna, numero))
                        {
                            tablero[cursorFila][cursorColumna] = numero;
                            // VERDE para movimiento válido
                            char mensaje[100];
                            sprintf(mensaje, "✓ Número %d colocado en %c%d\n", numero, 'A' + cursorFila, cursorColumna + 1);
                            imprimirColor(mensaje, 10, "\033[1;32m");
                        }
                        else
                        {
                             // ROJO para movimiento inválido
                            char mensaje[100];
                            sprintf(mensaje, "✗ Movimiento inválido! El número %d se repite\n", numero);
                            imprimirColor(mensaje, 12, "\033[1;31m");
                        }
                    }
                    else
                    {
                        // ROJO para celda ocupada
                        imprimirColor("✗ Celda ocupada! Use 0 para borrar primero\n", 12, "\033[1;31m");
                    }
                    // Pausa para ver el mensaje
                    printf("Presione cualquier tecla para continuar...");
                    _getch();
                    break;
                    
                case '0':
                    // Borrar celda
                    if(tablero[cursorFila][cursorColumna] != 0)
                    {
                        tablero[cursorFila][cursorColumna] = 0;
                        // VERDE para borrado exitoso
                        char mensaje[100];
                        sprintf(mensaje, "✓ Celda %c%d borrada\n", 'A' + cursorFila, cursorColumna + 1);
                        imprimirColor(mensaje, 10, "\033[1;32m");
                    }
                    else
                    {
                        printf("La celda ya está vacía\n");
                    }
                    // Pausa para ver el mensaje
                    printf("Presione cualquier tecla para continuar...");
                    _getch();
                    break;
                    
                // También soporte para WASD
                case 'w':
                case 'W':
                    if(cursorFila > 0) cursorFila--;
                    break;
                case 's':
                case 'S':
                    if(cursorFila < 8) cursorFila++;
                    break;
                case 'a':
                case 'A':
                    if(cursorColumna > 0) cursorColumna--;
                    break;
                case 'd':
                case 'D':
                    if(cursorColumna < 8) cursorColumna++;
                    break;
                    
                case 'q':
                case 'Q':
                    jugando = 0;
                    printf("Saliendo del modo navegación...\n");
                    break;
            }
        }
        
        // Verificar si el juego está completo después de cada movimiento
        if(esJuegoCompleto()) {
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif
            imprimirTablero();
            printf("🎉 ¡FELICIDADES! Ganaste!\n");
            printf("Presione cualquier tecla para continuar...");
            _getch();
            jugando = 0;
        }
    }
}