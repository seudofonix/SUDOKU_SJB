# ALGORITMO DE GENERACIÓN DE TABLEROS DE SUDOKU

## ENFOQUE GENERAL
Para generar un tablero de Sudoku válido que tenga exactamente una solución única, implementamos un algoritmo que consta de dos fases principales:

### FASE 1: GENERACIÓN DEL TABLERO COMPLETO
1. **Inicialización**: Comenzamos con un tablero 9x9 vacío (lleno de ceros)
2. **Llenado recursivo con backtracking**:
   - Utilizamos un algoritmo de backtracking para llenar el tablero completo
   - En cada celda, probamos números del 1 al 9 en orden aleatorio
   - Verificamos que cada número cumpla las reglas del Sudoku:
     - No se repite en la misma fila
     - No se repite en la misma columna  
     - No se repite en el bloque 3x3 correspondiente
   - Si encontramos un número válido, avanzamos a la siguiente celda
   - Si no hay números válidos, retrocedemos (backtrack)

### FASE 2: CREACIÓN DEL PUZZLE (ELIMINACIÓN ESTRATÉGICA)
1. **Guardar solución completa**: Conservamos una copia del tablero completo como solución
2. **Eliminación aleatoria controlada**:
   - Seleccionamos celdas en orden aleatorio para eliminar números
   - Para cada celda eliminada, verificamos que el tablero resultante mantenga:
     - **Solución única**: Usamos un contador de soluciones
     - **Jugabilidad**: No eliminamos demasiados números
3. **Verificación de solución única**:
   - Implementamos un algoritmo que cuenta cuántas soluciones tiene el tablero
   - Si encuentra más de una solución, restauramos el número eliminado
   - Solo mantenemos la eliminación si el tablero tiene exactamente una solución

## ALGORITMO DE SOLUCIÓN ÚNICA
```c
int contarSoluciones(int fila, int columna) {
    if (fila == 9) return 1; // Solución encontrada
    
    if (tablero[fila][columna] != 0) {
        // Celda fija, avanzar
        return contarSoluciones(siguienteFila, siguienteColumna);
    }
    
    int soluciones = 0;
    for (int num = 1; num <= 9; num++) {
        if (esMovimientoValido(fila, columna, num)) {
            tablero[fila][columna] = num;
            soluciones += contarSoluciones(siguienteFila, siguienteColumna);
            tablero[fila][columna] = 0;
            
            // Optimización: parar si ya encontramos múltiples soluciones
            if (soluciones >= 2) break;
        }
    }
    return soluciones;
}
