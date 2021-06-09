#ifndef IO_H
#define IO_H

int validarArchivoEntrada(char* entrada);  

void flag(int band, int filasZ, int columnasZ);

void leerImagen(char* entrada, int filas, int columnas);

void escribirResultados(char* nombre, float** matrizConZoom, int filasZ, int columnasZ);

#endif