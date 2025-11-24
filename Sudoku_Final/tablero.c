#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tablero.h"
#include "menu.h"

// Definimos un límite, ya que solo necesitamos saber si tiene 1 o > 1 soluciones
#define MAXIMO_SOLUCIONES 2 

extern int vidasRestantes;
extern int puntuacionActual;
extern char nombreJugador[21];
extern char ultimoJugador[21];
extern int ultimoPuntaje;

//------------- ---   CREACION TABLERO-------- 

//cambiar a memoria dinamica 
int** tablero = NULL;
int** tableroEstado = NULL;
int** tableroSolucion = NULL;

struct valoresPosibles
{
    int numerosBase[9];
    int tamanoArreglo;
};

// Randomiza el orden de los elementos que se encuentran dentro de un arreglo
void randomizarArreglo(int* arreglo, int tamanoArreglo)
{
    int i, j, temp;
    
    for (i = tamanoArreglo - 1; i > 0; i--)
    {
        j = rand() % (i + 1);  // índice aleatorio entre 0 e i
        temp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = temp;
    }
}

// Borra el elemento en el indice y desfasa todos los numeros subsiguientes en el arreglo para rellenar el espacio. 
void borrarElemento(int* arreglo, int indice, int tamanoArreglo)  
{
    int i; 
    
    for (i = indice; i < tamanoArreglo-1; i++)
    {
        arreglo[i] = arreglo[i+1];
    }
}

void inicializarTableroVacio() {
    int i, j;
    
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            tablero[i][j] = 0;
            tableroEstado[i][j] = 0;
            if (tableroSolucion != NULL) {
                tableroSolucion[i][j] = 0;
            }
        }
    }
}

//----------- GENERADOR DE NUM ALEATORIOS------

// Función para generar un número aleatorio entre min y max
int generarNumeroAleatorio(int min, int max){
    return rand() % (max - min + 1) + min;
}

//-------- LLENA TABLERO CON NUMEROS VALIDOS LISTO PARA JUGAR-----

// FUNCION PARA VERIFICAR SI UN MOVIMIENTO ES VALIDO (REGLAS SUDOKU)
int esMovimientoValido(int fila, int columna, int numero){
    int c, f, i, j;
    int inicioFila, inicioColumna;

    // verificar fila
    for (c = 0; c < 9; c++){
        if (c != columna && tablero[fila][c] == numero) 
		return 0;
    }

    // verificar columna
    for (f = 0; f < 9; f++){
        if (f != fila && tablero[f][columna] == numero) 
        return 0;
    }

    // verificar bloque 3x3
    inicioFila = (fila/3)*3;
    inicioColumna = (columna/3) *3;

    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            // Comprobar que no sea la celda que estamos intentando llenar/verificar
            if ((inicioFila + i) != fila || (inicioColumna + j) != columna) {
                 if (tablero[inicioFila + i][inicioColumna + j] == numero) 
                 return 0;
            }
        }
    }

    return 1;
}

// Intenta llenar la casilla con un numero aleatorio valido para su posicion
// Devuelve 0 cuando no hay movimientos validos para la casilla dada. 
int llenarCasilla(int fila, int columna)
{
    if (fila == 9)  // Caso base: tablero completo
        return 1;

    int siguienteFila = (columna == 8) ? fila + 1 : fila;
    int siguienteColumna = (columna + 1) % 9;

    struct valoresPosibles v = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        9
    };

    randomizarArreglo(v.numerosBase, v.tamanoArreglo);

    int i, num;

    for (i = 0; i < v.tamanoArreglo; i++)
    {
        num = v.numerosBase[i];

        if (esMovimientoValido(fila, columna, num))
        {
            tablero[fila][columna] = num;

            // Intentar llenar la siguiente casilla
            if (llenarCasilla(siguienteFila, siguienteColumna))
                return 1;

            // Si no funcionó, retrocede
            tablero[fila][columna] = 0;
        }
    }

    // Si no se puede colocar ningún número válido aquí, vuelve atrás
    return 0;
}

//  -----------------------ÚNICA SOLUCION--------------------------

// Cuenta cuántas soluciones puede tener el tablero actual
	int contarSoluciones(int fila, int columna)
	{
    // Caso base (si llegamos al final encontramos una solución)
    if (fila == 9) {
        return 1;
    }

    int siguienteFila = (columna == 8) ? fila + 1 : fila;
    int siguienteColumna = (columna + 1) % 9;

    // Si la celda está llena (es un número fijo), la saltamos
    if (tablero[fila][columna] != 0) {
        return contarSoluciones(siguienteFila, siguienteColumna);
    }

    // Si la celda está vacía, probamos todos los números (1-9)
    int num, totalSoluciones = 0;
    
    for (num = 1; num <= 9; num++) {
        if (esMovimientoValido(fila, columna, num)) {
            
            tablero[fila][columna] = num;
            
            // Llama recursivamente y suma las soluciones encontradas
            totalSoluciones += contarSoluciones(siguienteFila, siguienteColumna);
            
            //Si ya encontramos más de una solución >= 2, paramos no es necesario seguir.
            if (totalSoluciones >= MAXIMO_SOLUCIONES) {
                tablero[fila][columna] = 0;
                return totalSoluciones;
            }
        }
    }
    
    tablero[fila][columna] = 0;
    return totalSoluciones;
}

	void llenarTablero(int celdasMostradas)
	{
    inicializarTableroVacio();
    printf("Generando Sudoku (%d CASILLAS)...\n", celdasMostradas);
    
    int i, fila, columna;
    int indiceCeldas[81]; 
    
    //Se llena el tablero completo con números válidos
    if (!llenarCasilla(0, 0)) {
        printf("ERROR: No se pudo generar un tablero valido.\n");
        return;
    }

    // guardamos la solución completa
    for (fila = 0; fila < 9; fila++) {
        for (columna = 0; columna < 9; columna++) {
            tableroSolucion[fila][columna] = tablero[fila][columna];
        }
    }
    
    // Eliminación con Verificación de Solución Única
    // Generar un orden aleatorio de celdas a intentar borrar
    for(i = 0; i < 81; i++)  
    {
        indiceCeldas[i] = i;
    }
    randomizarArreglo(indiceCeldas, 81);
    
    int celdasRestantes = 81;
    
    // Iteramos sobre las celdas en orden aleatorio
    for(i = 0; i < 81; i++)
    {
        // Detener la eliminación si ya alcanzamos la cantidad de
        // celdas visibles en el sudoku (ejemplo en el nivel facil 38 celdas visibles)
        if (celdasRestantes <= celdasMostradas) {
            break; 
        }
        
        int idx = indiceCeldas[i];
        fila = idx / 9;
        columna = idx % 9;
        
        int valorGuardado = tablero[fila][columna];
        tablero[fila][columna] = 0;
        
        // Contamos cuántas soluciones tiene sin este número
        int numSoluciones = contarSoluciones(0, 0); 
        
         // Solución única Mantenemos el numero borrado
        if (numSoluciones == 1) {
            celdasRestantes--;
        } else {
            // si No es única o es (imposible no tiene solucion) Restauramos el número.
            tablero[fila][columna] = valorGuardado; 
        }
    }
    
    return;
}

//-------- FUNCION PARA VERIFICAR SI EL JUEGO ESTÁ COMPLETO --------
int esJuegoCompleto(){
    int fila, columna;
    
    for (fila = 0; fila < 9; fila++){
        for (columna = 0; columna < 9; columna++){
            // tiene que estar lleno
            if (tablero[fila][columna] == 0){
                return 0; 
            }
            // tiene que coincidir con la solución
            if (tableroSolucion != NULL && tablero[fila][columna] != tableroSolucion[fila][columna]) {
                return 0;
            }
        }
    }
    return 1; //TODAS las celdas llenas y correctas
}

// ================= NUEVAS FUNCIONES PARA LA INTERFAZ GRÁFICA =================

// antes usabamos  esMovimientoValido y daba “error” aunque el número fuera el de la solución.
// ahora se compara directamente contra tableroSolucion.
void actualizarEstadoCelda(int fila, int columna) {
    if (tableroEstado[fila][columna] == 1) return; // No modificar celdas fijas
    
    int valor = tablero[fila][columna];

    // Si está vacía después de borrar, estado vacío
    if (valor == 0) {
        tableroEstado[fila][columna] = 0;
        return;
    }

    // es correcto si coincide con la solución
    if (tableroSolucion != NULL && valor == tableroSolucion[fila][columna]) {
        tableroEstado[fila][columna] = 2; // Verde - correcto
    } else {
        tableroEstado[fila][columna] = 3; // Rojo - incorrecto
    }
}

// Función para obtener número de una celda
int obtenerNumeroCelda(int fila, int columna) {
    return tablero[fila][columna];
}

// Función para colocar número
void colocarNumero(int fila, int columna, int numero) {
    if (tableroEstado[fila][columna] == 1) { //celda fija no se puede cambiar
        return;
    }

    tablero[fila][columna] = numero;

    if (numero == 0) {
        // Si se borra la celda, vuelve a vacía
        tableroEstado[fila][columna] = 0; 
    } else {
        // Actualizar a correcto/incorrecto según la solución
        actualizarEstadoCelda(fila, columna);
        
        // NUEVO: Restar vida si el número es incorrecto
        if (tableroEstado[fila][columna] == 3) { // 3 = incorrecto
            if (vidasRestantes > 0) {
                vidasRestantes--;
                puntuacionActual -= 500; // Restar 500 puntos por error
                
                printf("¡Número incorrecto! Vidas restantes: %d\n", vidasRestantes);
                
                // Si se quedó sin vidas, guardar puntuación y cambiar estado
                if (vidasRestantes == 0) {
                    printf("¡Game Over! Puntuación final: %d\n", puntuacionActual);
                    
                    // Guardar puntuación actual (aunque sea 0)
                    guardarPuntaje(nombreJugador, puntuacionActual);
                    
                    // Actualizar variables para mostrar en el menú después
                    strcpy(ultimoJugador, nombreJugador);
                    ultimoPuntaje = puntuacionActual;
                }
            }
        }
    }
}

// Función para verificar si una celda es fija
int esCeldaFija(int fila, int columna) {
    return tableroEstado[fila][columna] == 1;
}

// ================= FUNCIONES PARA CREAR Y DESTRUIR TABLERO CON MEMORIA DINÁMICA =================

// Función para crear el tablero con memoria dinámica
void crearTablero() {
    int i, j;
    
    printf("Creando tablero de Sudoku con memoria dinámica...\n");
    
    // Asignar memoria para las filas
    tablero = (int**)malloc(9 * sizeof(int*));
    tableroEstado = (int**)malloc(9 * sizeof(int*));
    tableroSolucion = (int**)malloc(9 * sizeof(int*));
    
    // Asignar memoria para las columnas
    for (i = 0; i < 9; i++) {
        tablero[i] = (int*)malloc(9 * sizeof(int));
        tableroEstado[i] = (int*)malloc(9 * sizeof(int));
        tableroSolucion[i] = (int*)malloc(9 * sizeof(int));
    }
    
    // Inicializar semilla para números aleatorios
    srand(time(NULL));
    
    // Inicializar el tablero vacío
    inicializarTableroVacio();
    
    // Llenar el tablero con números válidos (ahora con solución única)
    llenarTablero(38); // 38 celdas mostradas (FACIL, por ejemplo)
    
    // Marcar las celdas no vacías como fijas
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (tablero[i][j] != 0) {
                tableroEstado[i][j] = 1; // Celda fija
            }
        }
    }
    
    printf("Tablero creado exitosamente con memoria dinámica!\n");
}

// Función para destruir el tablero y liberar memoria
void destruirTablero() {
    int i;
    
    printf("Destruyendo tablero y liberando memoria...\n");
    
    if (tablero != NULL) {
        for (i = 0; i < 9; i++) {
            free(tablero[i]);
        }
        free(tablero);
    }
    
    if (tableroEstado != NULL) {
        for (i = 0; i < 9; i++) {
            free(tableroEstado[i]);
        }
        free(tableroEstado);
    }

    // funcion para liberar la solución
    if (tableroSolucion != NULL) {
        for (i = 0; i < 9; i++) {
            free(tableroSolucion[i]);
        }
        free(tableroSolucion);
    }
    
    printf("Memoria del tablero liberada exitosamente!\n");
}
