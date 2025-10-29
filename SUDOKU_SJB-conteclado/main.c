#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "tablero.h"
#include "graficos.h"

int main() {

    srand(time(NULL));
    
    int opcion;
    
    do {
        printf("=== SUDOKU - JUEGO ===\n\n");
        printf("1. Nuevo juego (Nivel Fácil)\n");
        printf("2. Salir\n");
        printf("Seleccione una opción: ");
        
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1: {
                // Crear tablero antes de iniciar juego
                crearTablero();
                
                // Iniciar nuevo juego
                llenarTableroNivelFacil();
                int jugando = 1;
                
                do {
                    imprimirTablero();
                    
                    printf("--- OPCIONES ---\n");
                    printf("1. Hacer movimiento (entrada tradicional)\n");
                    printf("2. Navegación con teclado (WASD)\n");
                    printf("3. Volver al menú principal\n");
                    printf("Seleccione: ");
                    
                    int opcionJuego;
                    scanf("%d", &opcionJuego);
                    
                    switch (opcionJuego) {
                        case 1:
                        hacerMovimientoUsuario();
                        break;
                        case 2:
                        navegarConTeclado();
                        break;
                        case 3:
                        jugando = 0;
                        break;
                        default:
                            printf("Opción inválida.\n");
                    }
                    
                     if (esJuegoCompleto()) {
                         imprimirTablero();
                         printf("🎉 ¡FELICIDADES! Ganaste!\n");
                         jugando = 0;
                        }
        
                     if (jugando) {
                    printf("Presione Enter para continuar...");
                    getchar();
                    getchar();
                    }
        
                    } while (jugando);
                    
                    // Destruir tablero al salir del juego
                    destruirTablero();
                    break;
            }
                
            case 2:
                printf("¡Hasta luego!\n");
                break;
                
            default:
                printf("Opción inválida.\n");
        }
        
    } while (opcion != 2);
    
    return 0;
}