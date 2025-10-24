#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tablero.h"

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
                // Iniciar nuevo juego
                llenarTableroNivelFacil();
                int jugando = 1;
                
                do {
                    imprimirTablero();
                    
                    printf("--- OPCIONES ---\n");
                    printf("1. Hacer movimiento\n");
                    printf("2. Volver al menú principal\n");
                    printf("Seleccione: ");
                    
                    int opcionJuego;
                    scanf("%d", &opcionJuego);
                    
                    switch (opcionJuego) {
                        case 1:
                            hacerMovimientoUsuario();
                            
                            if (esJuegoCompleto()) {
                                imprimirTablero();
                                printf("🎉 ¡FELICIDADES! Ganaste!\n");
                                jugando = 0;
                            }
                            break;
                            
                        case 2:
                            jugando = 0;
                            break;
                            
                        default:
                            printf("Opción inválida.\n");
                    }
                    
                    if (jugando) {
                        printf("Presione Enter para continuar...");
                        getchar();
                        getchar();
                    }
                    
                } while (jugando);
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

