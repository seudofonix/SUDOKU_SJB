# SUDOKU



<img width="780" height="572" alt="Sudokku" src="https://github.com/user-attachments/assets/d9497d52-c4b3-4cba-8c27-e95c081f91f7" />



## Integrantes 
- Nicol Montaño
- Evelyn Orellana  
- Ignacio Bullón
- Evelyn Fernandez
  
# SUDOKU_SJB
Implementacion del Sudoku para Algoritmica y Programacion I. Universidad Nacional de la Patagonia San Juan Bosco (UNPSJB) 2025.

# COMANDOS DE COMPILACION
gcc -Wall -o sudoku main.c tablero.c graficos.c archivos.c menu.c tiempo.c -I/usr/include/SDL2 -L/usr/lib -lSDL2main -lSDL2 -lSDL2_ttf 

"./sudoku.exe"

## DESCRIPCIÓN
Sudoku Master es un juego completo de Sudoku desarrollado en C con interfaz gráfica usando SDL2. Incluye generación automática de tableros, sistema de puntuación, ranking de jugadores y gestión de vidas.

## CARACTERÍSTICAS
- Interfaz gráfica completa con SDL2
- Generación automática de tableros con solución única
- Sistema de puntuación basado en tiempo
- Gestión de vidas (3 vidas iniciales)
- Ranking persistente de jugadores
- Sistema de guardado de puntuaciones
- Control completamente por mouse

## ESTRUCTURA DE ARCHIVOS
- `main.c` - Punto de entrada principal del programa
- `tablero.c/h` - Lógica del juego y generación de tableros
- `graficos.c/h` - Interfaz gráfica y renderizado
- `menu.c/h` - Sistema de menús y estados del juego
- `archivos.c/h` - Gestión de rankings y persistencia
- `tiempo.c/h` - Sistema de temporizador

## COMPILACIÓN
### En Dev-C++:
1. Crear un proyecto vacío en C
2. Agregar todos los archivos .c
3. Configurar los parámetros del linker: `-lSDL2main -lSDL2 -lSDL2_ttf -lm`
4. Compilar el proyecto

## CONTROLES
- **Clic izquierdo**: Seleccionar celdas y números
- **Números 1-9**: Insertar números en celdas vacías
- **Borrar**: Eliminar número de celda seleccionada
- **Enter**: Confirmar nombre de jugador

## SISTEMA DE PUNTUACIÓN
- Puntuación base: 1500 puntos
- Tiempo límite: 2 minutos para puntuación perfecta
- Penalización: -500 puntos por error
- Vidas perdidas: -100 puntos por vida
- Puntuación mínima: 0 puntos

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
    Tarea Principal:  Verificación de solución única + jugabilidad del usuario
    Descripción:
    Asegurar que el tablero generado tenga solución única (LISTO)
    implementacion de victoria del jugador (LISTO)
    colaborar con Evelyn M. para implementar diferentes niveles de dificuldad 
    implementacion para el nombre del jugador
    

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

# PRACTICAS DE CODIGO 
Todas las funciones que tengan valores de retorno deben devolver 0 (cero) en caso de fallo y 1 (uno) en caso de exito. 
