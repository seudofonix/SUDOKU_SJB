# COMANDOS DE COMPILACION
gcc -Wall -o sudoku main.c tablero.c graficos.c archivos.c -I/usr/include/SDL2 -L/usr/lib -lSDL2main -lSDL2 -lSDL2_ttf 

"./sudoku.exe"

# SUDOKU_SJB
Implementacion del Sudoku para Algoritmica y Programacion I. Universidad Nacional de la Patagonia San Juan Bosco 2025.

# TAREAS
__1. Nicol Montaño:__
    Tarea Principal: Algoritmo para generar tablero posible
    Descripción:
    Crear un tablero completo (LISTO)
    Remover números estratégicamente para crear el puzzle (LISTO)
    Crear función que verifique si un tablero cumple las reglas del Sudoku (LISTO)
    Verificar filas, columnas y sub-cuadrículas 3x3 (LISTO)
    Colaborar con Evelyn O. para garantizar solución única
    Implementar diferentes niveles de dificultad//por ahora no es necesario implementarlo (NIVEL FACIL)

__2. Evelyn Orellana__
    Tarea Principal:  Verificación de solución única
    Descripción:
    Asegurar que el tablero generado tenga solución única

__3. Ignacio Bullón__
    Tarea Principal: Temporizador + Sistema de Puntuación Completo
    Descripción:
    Implementar cronómetro para medir tiempo de juego
    Crear sistema de puntuación basado en tiempo
    Diseñar e implementar estructura del Ranking
    Mostrar tiempo y puntuación en tiempo real durante el juego

__4. Evelyn Fernandez__
    Tarea Principal: Lectura de movimiento + Jugabilidad del usuario
    Descripción:
    Implementar lectura de movimientos del usuario (LISTO)
    Validar entradas (rangos permitidos)
    Implementar sistema que muestre números repetidos en otro color
    Detectar y resaltar conflictos en tiempo real
    Crear y destruir tableros (gestión de memoria) (LISTO)

# ARCHIVOS

__MAIN.C__
Archivo base, se encarga de manejar la logica del menu. 

Archivo header, contiene las definiciones de las funciones y las estructuras del juego. 

__GRAFICOS.H y GRAFICOS.C__
Archivo de graficos, todas las funciones que manejen los graficos se encuentran dentro de estos dos archivos. 

# PRACTICAS DE CODIGO 
Todas las funciones que tengan valores de retorno deben devolver 0 (cero) en caso de fallo y 1 (uno) en caso de exito. 
