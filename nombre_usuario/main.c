#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "tablero.h"
#include "graficos.h"
#include "jugador.h"   // agrega este include para usar nombre_jugador() y consigna()

int main() {

    srand(time(NULL));

    char nombreJugador[50];           //  variable para guardar el nombre
    nombre_jugador(nombreJugador);    //  pide el nombre y muestra la bienvenida
    consigna(nombreJugador);          //  muestra las reglas del juego

    int opcion;
    
    do {
        printf("=== SUDOKU - JUEGO ===\n\n");
        printf("Jugador actual: %s\n\n", nombreJugador);  // muestra el nombre en el menú
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
                        printf("¡FELICIDADES, %s! ¡Ganaste!\n", nombreJugador);  //  usa el nombre del jugador
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
                printf("¡Hasta luego, %s!\n", nombreJugador);  //  se despide por nombre
                break;
                
            default:
                printf("Opción inválida.\n");
        }
        
    } while (opcion != 2);
    
    return 0;
}

