#ifndef GRAFICOS_H
#define GRAFICOS_H

    // Lee un movimiento del usuario. (Llama a la funcion de editar tablero)
    void leerMovimiento();

    // Mueve el cursor de la consola a X, Y.
    void gotoxy(int x, int y);
    
    // Nueva función para navegación con teclado
    void navegarConTeclado();
    // Función auxiliar para imprimir en color
    void imprimirColor(const char* mensaje, int colorWindows, const char* colorANSI);

    #endif // GRAFICOS_H