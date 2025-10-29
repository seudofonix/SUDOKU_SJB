#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tablero.h"

// Incluir Windows.h solo para Windows
#ifdef _WIN32
#include <windows.h>
#endif

//------------- ---   CREACION TABLERO-------- 

// Cambiamos a puntero doble para gestión dinámica
int **tablero = NULL;

// NUEVA FUNCIÓN: Crear tablero en memoria dinámica
void crearTablero() {
    // Asignar memoria para las filas
    tablero = (int **)malloc(9 * sizeof(int *));
    if (tablero == NULL) {
        printf("Error: No se pudo asignar memoria para el tablero\n");
        exit(1);
    }
    
    // Asignar memoria para cada columna
    for (int i = 0; i < 9; i++) {
        tablero[i] = (int *)malloc(9 * sizeof(int));
        if (tablero[i] == NULL) {
            printf("Error: No se pudo asignar memoria para la fila %d\n", i);
            // Liberar memoria ya asignada antes de salir
            for (int j = 0; j < i; j++) {
                free(tablero[j]);
            }
            free(tablero);
            exit(1);
        }
    }
    
    // Inicializar todas las celdas a 0
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tablero[i][j] = 0;
        }
    }
}

// NUEVA FUNCIÓN: Destruir tablero y liberar memoria
void destruirTablero() {
    if (tablero != NULL) {
        // Liberar cada fila
        for (int i = 0; i < 9; i++) {
            free(tablero[i]);
        }
        // Liberar el array principal
        free(tablero);
        tablero = NULL;
    }
}

void imprimirTablero() {
    // Verificar que el tablero existe
    if (tablero == NULL) {
        printf("Error: El tablero no ha sido creado\n");
        return;
    }

    // Limpiar la pantalla de la terminal
    #ifdef _WIN32
    system("cls");
    #else
        system("clear"); // Para Linux/Mac
    #endif
    
    
    // Espacio superior para mejor presentación
    printf("\n");
    // Título del juego
    printf("    SUDOKU - TABLERO\n");
    printf("\n");
    
    // Imprimir números de columnas (1-9) en la parte superior
    printf("     ");  // 5 espacios para alinear números de columnas con letras de filas

    for (int col = 1; col <= 9; col++) { //Bucle para las 9 columnas (1 a 9)
        printf("%d   ", col);  // Imprime el número de columna seguido de 3 espacios
        // AGREGAR ESPACIO EXTRA ENTRE BLOQUES DE 3 COLUMNAS
        if (col % 3 == 0 && col != 9) { //Si es múltiplo de 3 y no es la última columna
            printf(" "); 
        }
    }
    printf("\n");  // Nueva línea después de los números de columnas
    
    // Línea horizontal superior del tablero (borde grueso)
    printf("   ╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗\n");
    
    // RECORRER TODAS LAS FILAS DEL TABLERO (0-8 que corresponden a A-I)
    for (int fila = 0; fila < 9; fila++) {

        // Imprimir letra de fila (A-I) y borde izquierdo
        printf(" %c ║", 'A' + fila); // Convierte número a letra: 0→A, 1→B, ..., 8→I
        
        
        // RECORRER TODAS LAS COLUMNAS DE LA FILA ACTUAL
        for (int col = 0; col < 9; col++) {
            // Verificar si la celda está vacía (valor 0)
            if (tablero[fila][col] == 0) {
                printf(" · ");  // Mostrar punto medio para celdas vacías
            } else {
                printf(" %d ", tablero[fila][col]);  // Mostrar número de la celda
            }

            
            // AGREGAR SEPARADORES ENTRE COLUMNAS (excepto después de la última columna)
            if (col < 8) {

                // VERIFICAR SI ESTAMOS EN EL BORDE DE UN BLOQUE 3x3

                if ((col + 1) % 3 == 0) { // Si la siguiente columna es múltiplo de 3
                    printf("║");  // Separador vertical grueso entre bloques
                } else {          // Si estamos dentro de un bloque
                    printf("│");  // Separador vertical fino dentro del bloque
                }
            }
        }
        printf("║\n");  // Borde derecho y nueva línea
        
        // AGREGAR SEPARADORES ENTRE FILAS (excepto después de la última fila)
        if (fila < 8) {

            // Verificar si estamos en el borde de un bloque 3x3 vertical

            if ((fila + 1) % 3 == 0) { // Si la siguiente fila es múltiplo de 3
                // Línea horizontal gruesa entre bloques
                printf("   ╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣\n");
            } else {
                // Línea horizontal fina dentro del bloque
                printf("   ╟───┼───┼───╫───┼───┼───╫───┼───┼───╢\n");
            }
        }
    }
    
    // Línea horizontal inferior del tablero (borde grueso)
    printf("   ╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝\n");
    printf("\n");  // Espacio final para mejor legibilidad
}

void inicializarTableroVacio() {
    // Si el tablero no existe, crearlo
    if (tablero == NULL) {
        crearTablero();
        return;
    }

    // RECORRER TODAS LAS FILAS DEL TABLERO
    for (int i = 0; i < 9; i++) {
        // RECORRER TODAS LAS COLUMNAS DE CADA FILA
        for (int j = 0; j < 9; j++) {
            tablero[i][j] = 0;  // Establecer cada celda como vacía (valor 0)
        }
    }
}



//----------- GENERADOR DE NUM ALEATORIOS------

// Función para generar un número aleatorio entre min y max
int generarNumeroAleatorio(int min, int max){
    return rand() % (max - min + 1) + min;
}



//-------- LLENA TABLERO CON NUMEROS VALIDOS LISTO PARA JUGAR-----

//FUNCION PARA VERIFICAR SI UN MOVIMIENTO ES VALIDO
int esMovimientoValido(int fila, int columna, int numero){
    // Verificar que el tablero existe
    if (tablero == NULL) return 0;

    //verificar fila
    for (int c=0; c <9; c++){
        if (tablero[fila][c]== numero) return 0;
    }

    //verificar columna
    for (int f =0; f < 9; f++){
        if (tablero[f][columna]== numero) return 0;
    }

    //verificar bloque 3x3
    int inicioFila = (fila/3)*3;
    int inicioColumna = (columna/3) *3;

    for (int i=0; i< 3; i++){
        for (int j=0; j<3; j++){
            if (tablero[inicioFila + i][inicioColumna + j] == numero) return 0;
        }
    }

    return 1;

}

// Función para llenar el tablero con un patrón de Sudoku FACIL
void llenarTableroNivelFacil(){
    // Si el tablero no existe, crearlo
    if (tablero == NULL) {
        crearTablero();
    }

    inicializarTableroVacio();

    printf("Generando Sudoku nivel fácil...\n");

    int celdasLlenadas = 0;

    while (celdasLlenadas < 35){
        //Elegir celda al azar
        int fila = generarNumeroAleatorio(0,8);
        int columna = generarNumeroAleatorio(0,8);

    
        //si la celda esta vacia, intentar poner numero

        if (tablero[fila][columna] == 0){
            // Probar numeros del 1 al 9
            for (int numero = 1; numero <= 9; numero++){
                //verificar si el num es valido 
                if (esMovimientoValido(fila, columna, numero)){
                    // Poner el numero y contar
                    tablero[fila][columna]= numero;
                    celdasLlenadas++;
                    break;
                }
            }
        }

    }

    
}
//-------INTERACCION DEL USUARIO PARA JUGAR---------

// FUNCION PARA QUE EL USER COLOQUE UN NUMERO
void hacerMovimientoUsuario(){
    // Verificar que el tablero existe
    if (tablero == NULL) {
        printf("Error: El tablero no ha sido creado\n");
        return;
    }

    char letraFila;
    int columna, numero;

    printf("\n --- HACER MOVIMIENTO----\n");
    printf("Ejemplo: A5 7 (fila A, columna 5, numero 7) \n");
    printf("ingrese movimiento: ");

    //Lee entrada:
    scanf(" %c%d %d", &letraFila, &columna, &numero);

    //Convertir letra a numero (A=0, B=1...)
    int fila = letraFila - 'A';
    columna = columna -1; // convertir 1-9 a 0-8

    //verifica si la posicion es valida
    if (fila <0 || fila >8 || columna <0 || columna > 8) {
        printf("ERROR: Posicion invalida. Use A-I y 1-9. \n");
        return;
    }

    //verifica si la celda está vacia
    if (tablero[fila][columna]!=0){
        printf("ERROR: Esa celda ya tiene número. \n");
        return;
    }

    if (numero < 1 || numero > 9) {
        printf("Error: Numero invalido. Debe ser 1-9. \n");
        return;
    }

    //verifica reglas del sudoku
    if (esMovimientoValido(fila, columna, numero)){
        tablero[fila][columna] = numero;
        
        // Mensaje en VERDE para movimiento válido
        #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10); // 10 = Verde claro en Windows
        printf("✓ Movimiento válido! Numero %d colocado en %c%d\n", numero, letraFila, columna+1);
        SetConsoleTextAttribute(hConsole, 7); // Volver al color normal (gris)
        #else
        printf("\033[1;32m✓ Movimiento válido! Numero %d colocado en %c%d\033[0m\n", numero, letraFila, columna+1);
        #endif
    } else {
        // Mensaje en ROJO para movimiento inválido
        #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12); // 12 = Rojo claro en Windows
        printf("✗ Movimiento inválido! El número %d se repite.\n", numero);
        SetConsoleTextAttribute(hConsole, 7); // Volver al color normal (gris)
        #else
        printf("\033[1;31m✗ Movimiento inválido! El número %d se repite.\033[0m\n", numero);
        #endif
    }
}

//-------- FUNCION PARA VERIFICAR SI EL JUEGO ESTÁ COMPLETO( SIN VALIDACION DE SOL. UNICA)-----
int esJuegoCompleto(){
    // Verificar que el tablero existe
    if (tablero == NULL) return 0;
    
    for (int fila =0; fila < 9; fila++){
        for (int columna=0; columna < 9; columna++){
            if (tablero[fila][columna] == 0){
                return 0; // // SI  Hay celdas vacías - juego no completo
            }
        }
    }
    return 1; // TODAS las celdas llenas- juego COMPLETO
}


